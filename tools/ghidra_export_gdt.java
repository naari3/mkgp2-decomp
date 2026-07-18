// mkgp2-decomp: /mkgp2_main.dol の data type (struct 定義等) を
// Data Type Archive (tools/mkgp2_types.gdt) に export する。
// Ghidra MCP の run_script_inline に body をそのまま渡して実行する。
// .gdt は型定義のみでゲームバイナリを含まないため repo に commit できる。
// 取り込み側: Ghidra の Data Type Manager で "Open File Archive" して
// 対象 program に Copy / apply する。

java.io.File f = new java.io.File(
        "C:/Users/naari/src/github.com/naari3/mkgp2-decomp/tools/mkgp2_types.gdt");
if (f.exists()) f.delete();
ghidra.program.model.data.FileDataTypeManager arch =
        ghidra.program.model.data.FileDataTypeManager.createFileArchive(f);
int tx = arch.startTransaction("copy types from mkgp2_main.dol");
java.util.Iterator<ghidra.program.model.data.DataType> it =
        currentProgram.getDataTypeManager().getAllDataTypes();
int n = 0;
while (it.hasNext()) {
    arch.resolve(it.next(),
            ghidra.program.model.data.DataTypeConflictHandler.REPLACE_HANDLER);
    n++;
}
arch.endTransaction(tx, true);
arch.save();
arch.close();
println("resolved " + n + " types -> " + f.getAbsolutePath());
