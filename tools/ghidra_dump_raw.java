// mkgp2-decomp: /mkgp2_main.dol から raw symbol dump を書き出す。
// Ghidra MCP の run_script_inline に body をそのまま渡して実行する
// (inline script は GhidraScript context の Java として実行される)。
// 出力:
//   tools/_ghidra_dump_functions.json  ... {"functions":[{name,address,isThunk,isExternal}]}
//   tools/_ghidra_dump_globals.txt     ... "name @ addr [Kind] (DataType)" 行 (list_globals 互換)
// 後段: python tools/_build_ghidra_dump.py -> tools/ghidra_symbol_dump.json

String outDir = "C:/Users/naari/src/github.com/naari3/mkgp2-decomp/tools";

java.io.PrintWriter fw = new java.io.PrintWriter(new java.io.OutputStreamWriter(
        new java.io.FileOutputStream(outDir + "/_ghidra_dump_functions.json"),
        java.nio.charset.StandardCharsets.UTF_8));
fw.print("{\"functions\":[");
ghidra.program.model.listing.FunctionIterator fit =
        currentProgram.getFunctionManager().getFunctions(true);
boolean first = true;
int nf = 0;
while (fit.hasNext()) {
    ghidra.program.model.listing.Function fn = fit.next();
    if (!first) fw.print(",");
    first = false;
    String nm = fn.getName().replace("\\", "\\\\").replace("\"", "\\\"");
    fw.print("{\"name\":\"" + nm + "\",\"address\":\"" + fn.getEntryPoint() + "\"");
    if (fn.isThunk()) fw.print(",\"isThunk\":true");
    if (fn.isExternal()) fw.print(",\"isExternal\":true");
    fw.print("}");
    nf++;
}
fw.print("]}");
fw.close();

java.io.PrintWriter gw = new java.io.PrintWriter(new java.io.OutputStreamWriter(
        new java.io.FileOutputStream(outDir + "/_ghidra_dump_globals.txt"),
        java.nio.charset.StandardCharsets.UTF_8));
ghidra.program.model.symbol.SymbolIterator sit =
        currentProgram.getSymbolTable().getAllSymbols(false);
int ng = 0;
while (sit.hasNext()) {
    ghidra.program.model.symbol.Symbol s = sit.next();
    if (s.getSymbolType() != ghidra.program.model.symbol.SymbolType.LABEL) continue;
    if (!s.getAddress().isMemoryAddress()) continue;
    // function 内 label (switchD 等) を除外: global namespace 直下のみ
    if (!s.getParentNamespace().isGlobal()) continue;
    ghidra.program.model.listing.Data d =
            currentProgram.getListing().getDefinedDataAt(s.getAddress());
    String kind = (d != null) ? "Data" : "Label";
    String dtype = (d != null) ? d.getDataType().getName() : null;
    gw.println(s.getName() + " @ " + s.getAddress() + " [" + kind + "]"
            + (dtype != null ? " (" + dtype + ")" : ""));
    ng++;
}
gw.close();
println("functions=" + nf + " globals=" + ng);
