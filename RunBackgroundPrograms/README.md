Please run the MAKEFILE using the command "make" or run the command: "gcc PMan.c -o output" to compile the C program.
To run the program use "./output"

I have included a 2 additional helper files that will compile when the MAKEFILE is run to use as helper programs they can be used in the PMan program to run as background programs. They will complie as ./output2 and ./output 3. ./output2 will have a short time before completion, and ./output3 has a long time before completion


To run programs while in the PMan program please use the command "bg ./program name" this will run programs in the background

Other commands that work include:
bglist
bgstart [pid]
bgstop [pid]
bgkill [pid]
pstat [pid]


To end the program please type in "end"


