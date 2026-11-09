import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Data;
import ghidra.program.model.symbol.Symbol;

String[] addrs = new String[] { __ADDRS__ };
StringBuilder sb = new StringBuilder();
for (String aStr : addrs) {
    Address a = toAddr(aStr);
    sb.append(aStr).append("\t");
    if (a == null) { sb.append("invalid\n"); continue; }
    Function fn = currentProgram.getFunctionManager().getFunctionAt(a);
    if (fn != null) {
        long sz = fn.getBody().getNumAddresses();
        sb.append("function\t0x").append(Long.toHexString(sz)).append("\t").append(fn.getName());
    } else {
        Data d = currentProgram.getListing().getDataAt(a);
        if (d != null) {
            sb.append("data\t0x").append(Long.toHexString(d.getLength())).append("\t");
            String dtName = d.getDataType() != null ? d.getDataType().getName() : "";
            String lbl = d.getLabel();
            sb.append(dtName).append("|").append(lbl != null ? lbl : "");
        } else {
            Symbol s = currentProgram.getSymbolTable().getPrimarySymbol(a);
            sb.append("symbol\t\t").append(s != null ? s.getName() : "(none)");
        }
    }
    sb.append("\n");
}
println(sb.toString());
