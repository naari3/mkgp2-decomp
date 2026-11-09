import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.CreateFunctionCmd;
import java.io.*;
public class DecAt extends GhidraScript {
  public void run() throws Exception {
    String[] a = getScriptArgs();
    PrintWriter pw = new PrintWriter(new FileWriter(a[0]));
    DecompInterface d = new DecompInterface();
    d.openProgram(currentProgram);
    for (int i = 1; i < a.length; i++) {
      Address ad = toAddr(a[i]);
      Function f = getFunctionAt(ad);
      if (f == null) {
        new DisassembleCommand(ad, null, true).applyTo(currentProgram);
        new CreateFunctionCmd(ad).applyTo(currentProgram);
        f = getFunctionAt(ad);
      }
      if (f == null) { pw.println("//==== nofunc " + a[i]); continue; }
      DecompileResults r = d.decompileFunction(f, 60, monitor);
      pw.println("//==== " + f.getName() + " @ " + f.getEntryPoint());
      if (r != null && r.decompileCompleted()) pw.println(r.getDecompiledFunction().getC());
    }
    pw.close();
  }
}
