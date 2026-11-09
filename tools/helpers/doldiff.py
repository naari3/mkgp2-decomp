import struct
a=open('/home/claude/mkgp2-decomp/orig/GNLJ82/sys/main.dol','rb').read();b=open('/home/claude/mkgp2-decomp/build/GNLJ82/main.dol','rb').read()
print(len(a),len(b))
h=a[:0x100];offs=struct.unpack('>18I',h[:72]);addrs=struct.unpack('>18I',h[72:144]);sz=struct.unpack('>18I',h[144:216])
n=0
for i in range(min(len(a),len(b))):
    if a[i]!=b[i]:
        va=None
        for o,ad,s in zip(offs,addrs,sz):
            if o<=i<o+s: va=ad+i-o
        print(hex(i),hex(va or 0),a[i],b[i]); n+=1
        if n>8: break
