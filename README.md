# System_Monitor
A middleware which can monitor the living status of applications.
This software still in a debug stage, and have some issue.

## Structure
	\IPC_Code\src is the source code folder.
	\IPC_Code\exec will generate the exec and will be cleaned by the make clean command.
	\IPC_Code\obj will save the corresponding .o file, and will be cleabed by tge make clean command.

## Makefile
	Command: 
	1. make clean:  clean the exec or elf which generated by the GCC or G++
	2. make: compiler the source code files in the src folder.

