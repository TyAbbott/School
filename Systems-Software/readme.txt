Assignment 4 - Ty Abbott
Fall 2017

To run and compile:
gcc compiler.c -o compiler -lm
./compiler [-l] [-a] [-v]

Included in this file:
compiler.c
pmachine.h
scanner.h
parsercodgen.h
Inputs-Outputs


scanner.h takes "scannerinput.txt" as input and writes to "parsercodgeninput.txt".
pmachine.h takes "pmachineinput.txt" as input and writes to "pmachineoutput.txt".
parsercodgen.h takes "parsercodgeninput.txt" as input and writes to "pmachineinput.txt"

input chain:
scannerinput.txt > parsercodgeninput.txt > pmachineinput.txt > pmachineoutput.txt 

----------------------------------------------------------------------------------------------
To test your own input files, change your input file name to: "scannerinput.txt"