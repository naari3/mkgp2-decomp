import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;
public class DumpAll extends GhidraScript {
  public void run() throws Exception {
    String out = getScriptArgs()[0];
    PrintWriter pw = new PrintWriter(new FileWriter(out));
    DecompInterface d = new DecompInterface();
    d.openProgram(currentProgram);
    for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
      if (monitor.isCancelled()) break;
      DecompileResults r = d.decompileFunction(f, 60, monitor);
      pw.println("//==== " + f.getName() + " @ " + f.getEntryPoint());
      if (r != null && r.decompileCompleted()) pw.println(r.getDecompiledFunction().getC());
      else pw.println("// decompile failed");
    }
    pw.close();
  }
}
