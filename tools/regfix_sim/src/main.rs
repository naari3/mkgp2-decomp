//! Hot path of tools/regfix.py: MWCC's Chaitin register allocator (simplify +
//! select) and the declaration-order solver. Plain-text protocol on stdin/stdout
//! (no dependencies), written and read by regfix.py:
//!
//!   task decl|colour         maxn N   tlimit SECONDS
//!   class gpr|fpr            (one block per register class)
//!   node IDX KEY PERMN FIXEDMASK WANT NB...   (WANT = target reg or -1)
//!   local IDX NAMEID         (named function local; NAMEID shared across classes)
//!   end
//!
//! colour -> per class `colour IDX REG ...` in colouring order.
//! decl   -> `decl NAMEID NAMEID ...` (first declared first) or `decl none`.
use std::io::{self, Read, Write};
use std::time::Instant;

struct Class {
    gpr: bool,
    key: Vec<f64>,
    permn: Vec<i32>,
    fixed: Vec<u32>,
    want: Vec<i32>,
    nb: Vec<Vec<usize>>,
    locals: Vec<(usize, usize)>, // (node, nameid)
    cost: Vec<f64>,              // spill cost (dump `cost:`), for the stuck-simplify pick
}

const K_GPR: i32 = 29;
const K_FPR: i32 = 32;

impl Class {
    fn simplify(&self, key: &[f64], order: &mut Vec<usize>, sorted: &mut Vec<usize>, deg: &mut Vec<i32>, removed: &mut Vec<bool>) {
        let n = key.len();
        sorted.clear();
        sorted.extend(0..n);
        sorted.sort_by(|&a, &b| key[a].partial_cmp(&key[b]).unwrap());
        let k = if self.gpr { K_GPR } else { K_FPR };
        for v in 0..n {
            deg[v] = self.permn[v] + self.nb[v].len() as i32;
            removed[v] = false;
        }
        order.clear();
        while order.len() < n {
            let mut prog = false;
            for &v in sorted.iter() {
                if removed[v] || deg[v] >= k {
                    continue;
                }
                removed[v] = true;
                order.push(v);
                prog = true;
                for &x in &self.nb[v] {
                    deg[x] -= 1;
                }
            }
            if !prog {
                // MWCC pushes the cheapest spill candidate: lowest cost/degree, ties -> lowest key
                let mut v = usize::MAX;
                let mut best = f64::INFINITY;
                for &u in sorted.iter() {
                    if removed[u] {
                        continue;
                    }
                    let c = self.cost.get(u).copied().unwrap_or(0.0) / (deg[u].max(1) as f64);
                    if c < best {
                        best = c;
                        v = u;
                    }
                }
                removed[v] = true;
                order.push(v);
                for &x in &self.nb[v] {
                    deg[x] -= 1;
                }
            }
        }
        order.reverse();
    }

    /// Colour in `order`; with `check`, stop at the first register that differs
    /// from the target (returns false).
    fn colour(&self, order: &[usize], phys: &mut Vec<i32>, check: bool) -> bool {
        let vol: &[i32] = if self.gpr { &[0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12] } else { &[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13] };
        for p in phys.iter_mut() {
            *p = -1;
        }
        let mut used: u32 = 0;
        for &v in order {
            let mut forb = self.fixed[v];
            for &x in &self.nb[v] {
                if phys[x] >= 0 {
                    forb |= 1 << phys[x];
                }
            }
            let mut r = -1;
            for &c in vol {
                if forb & (1 << c) == 0 {
                    r = c;
                    break;
                }
            }
            if r < 0 {
                for c in 14..32 {
                    if used & (1 << c) != 0 && forb & (1 << c) == 0 {
                        r = c;
                        break;
                    }
                }
            }
            if r < 0 {
                for c in (14..32).rev() {
                    if used & (1 << c) == 0 && forb & (1 << c) == 0 {
                        r = c;
                        used |= 1 << c;
                        break;
                    }
                }
            }
            if r < 0 {
                r = 99; // spill
            }
            phys[v] = r;
            if check && self.want[v] >= 0 && self.want[v] != r {
                return false;
            }
        }
        true
    }
}

fn next_perm(a: &mut [usize]) -> bool {
    let n = a.len();
    if n < 2 {
        return false;
    }
    let mut i = n - 1;
    while i > 0 && a[i - 1] >= a[i] {
        i -= 1;
    }
    if i == 0 {
        return false;
    }
    let mut j = n - 1;
    while a[j] <= a[i - 1] {
        j -= 1;
    }
    a.swap(i - 1, j);
    a[i..].reverse();
    true
}

fn main() {
    let mut s = String::new();
    io::stdin().read_to_string(&mut s).unwrap();
    let mut task = String::from("colour");
    let mut maxn = 9usize;
    let mut tlimit = 60.0f64;
    let mut cls: Vec<Class> = Vec::new();
    let mut names: Vec<usize> = Vec::new(); // current decl order (name ids, first declared first)
    let mut free: Vec<usize> = Vec::new();
    for line in s.lines() {
        let t: Vec<&str> = line.split_whitespace().collect();
        if t.is_empty() {
            continue;
        }
        match t[0] {
            "task" => task = t[1].to_string(),
            "maxn" => maxn = t[1].parse().unwrap(),
            "tlimit" => tlimit = t[1].parse().unwrap(),
            "names" => names = t[1..].iter().map(|x| x.parse().unwrap()).collect(),
            "free" => free = t[1..].iter().map(|x| x.parse().unwrap()).collect(),
            "class" => cls.push(Class { gpr: t[1] == "gpr", key: vec![], permn: vec![], fixed: vec![], want: vec![], nb: vec![], locals: vec![], cost: vec![] }),
            "node" => {
                let c = cls.last_mut().unwrap();
                let i: usize = t[1].parse().unwrap();
                while c.key.len() <= i {
                    c.key.push(0.0);
                    c.permn.push(0);
                    c.fixed.push(0);
                    c.want.push(-1);
                    c.nb.push(vec![]);
                }
                c.key[i] = t[2].parse().unwrap();
                c.permn[i] = t[3].parse().unwrap();
                c.fixed[i] = t[4].parse().unwrap();
                c.want[i] = t[5].parse().unwrap();
                c.nb[i] = t[6..].iter().map(|x| x.parse().unwrap()).collect();
            }
            "cost" => {
                let c = cls.last_mut().unwrap();
                let i: usize = t[1].parse().unwrap();
                while c.cost.len() <= i {
                    c.cost.push(0.0);
                }
                c.cost[i] = t[2].parse().unwrap();
            }
            "local" => {
                let c = cls.last_mut().unwrap();
                c.locals.push((t[1].parse().unwrap(), t[2].parse().unwrap()));
            }
            _ => {}
        }
    }
    let mut out = io::stdout();
    let mut order = Vec::new();
    let mut sorted = Vec::new();
    let mut deg = Vec::new();
    let mut removed = Vec::new();
    let mut phys = Vec::new();
    if task == "colour" {
        for c in &cls {
            let n = c.key.len();
            deg.resize(n, 0);
            removed.resize(n, false);
            phys.resize(n, -1);
            c.simplify(&c.key, &mut order, &mut sorted, &mut deg, &mut removed);
            c.colour(&order, &mut phys, false);
            let mut l = String::from("colour");
            for &v in &order {
                l += &format!(" {} {}", v, phys[v]);
            }
            writeln!(out, "{}", l).unwrap();
        }
        return;
    }
    // decl: permute the names in `free` over their slots in `names`
    let t0 = Instant::now();
    if free.len() > maxn {
        free.truncate(maxn);
    }
    let slots: Vec<usize> = names.iter().enumerate().filter(|(_, n)| free.contains(n)).map(|(i, _)| i).collect();
    let mut perm: Vec<usize> = (0..slots.len()).collect();
    let maxid = names.iter().copied().max().unwrap_or(0) + 1;
    let mut rank = vec![0usize; maxid];
    // per class: sorted local numbers
    let nums: Vec<Vec<f64>> = cls.iter().map(|c| {
        let mut v: Vec<f64> = c.locals.iter().map(|&(i, _)| c.key[i]).collect();
        v.sort_by(|a, b| a.partial_cmp(b).unwrap());
        v
    }).collect();
    let mut keys: Vec<Vec<f64>> = cls.iter().map(|c| c.key.clone()).collect();
    let mut tried: u64 = 0;
    let mut loc: Vec<(usize, usize)> = Vec::new();
    loop {
        let mut cur = names.clone();
        for (k, &si) in slots.iter().enumerate() {
            cur[si] = free[perm[k]];
        }
        for (i, &n) in cur.iter().enumerate() {
            rank[n] = i;
        }
        tried += 1;
        let mut ok = true;
        for (ci, c) in cls.iter().enumerate() {
            loc.clear();
            loc.extend(c.locals.iter().copied());
            loc.sort_by(|a, b| rank[b.1].cmp(&rank[a.1])); // last declared first = lowest number
            for (j, &(v, _)) in loc.iter().enumerate() {
                keys[ci][v] = nums[ci][j];
            }
            let n = c.key.len();
            deg.resize(n, 0);
            removed.resize(n, false);
            phys.resize(n, -1);
            c.simplify(&keys[ci], &mut order, &mut sorted, &mut deg, &mut removed);
            if !c.colour(&order, &mut phys, true) {
                ok = false;
                break;
            }
        }
        if ok && cur != names {
            let l: Vec<String> = cur.iter().map(|x| x.to_string()).collect();
            writeln!(out, "decl {}", l.join(" ")).unwrap();
            writeln!(out, "tried {}", tried).unwrap();
            return;
        }
        if !next_perm(&mut perm) || t0.elapsed().as_secs_f64() > tlimit {
            break;
        }
    }
    writeln!(out, "decl none").unwrap();
    writeln!(out, "tried {}", tried).unwrap();
}
