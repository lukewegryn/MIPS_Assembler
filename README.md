# MIPS_Assembler
Assembler for the MIPS Architecture

WARNING: For this program to work correctly, your processor must use 32-bit integers. Since the output must be 32-bits (because that's how MIPS works), anything smaller will not give you the correct results.

Pull this repositiory and put all of the files in a single folder named "myAssembler".
You must have the QT framework to compile this project.

0. Open a terminal and navigate (cd) to your "myAssembler" folder.
1. Run "qmake -project". Some files will be made.
2. Run "qmake". Some more files will be made.
3. Open the "Makefile" that QT created.
4. Add "-std=c++11" to the CFLAGS and CXXFlags line.
5. Run "make".
6. Run "myAssembler assemblyInstructions.asm" where assemblyInstructions.asm is the MIPS assembly file you wish to assemble.
7. Look in your "myAssembler" folder to find an assembled file named "assemblyInstructions.txt" with the assembled data in hex.

