# IPC Using Unnamed Pipe

Interprocess communication between related processes

The pipe command is used to make pipes and is used for inter process communication using read and write commands

## Files : 
```
parentChild.c
```
## Commands to run : 
```
gcc parentChild.c && ./a.out       # Compile and runs Program
```
## Processes
```
Parent Process        # Used to control the child processes
Process 1             # Gets User Input and displays final output
Process 2             # Calculates Average and Standard Deviation
Process 3             # Assigns Categories based on Average and Standard Deviation
```



# IPC Using Named Pipe

Interprocess communication between unrelated processes

The mkfifo command is used to make pipes and their file descriptors are used for inter process communication using read and write commands

## Files : 
```
process_1.c       # Process 1 Program
process_2.c       # Process 2 Program
process_3.c       # Process 3 program
```
## Commands to run : 
```
gcc process_1.c -o p1 && ./p1             # Compile and runs Program of process 1
gcc process_2.c -o p2 -lm && ./p2         # Compile and runs Program of process 2
gcc process_3.c -o p3 && ./p3             # Compile and runs Program of process 3
```
## Processes
```
Process 1             # Gets User Input and displays final output
Process 2             # Calculates Average and Standard Deviation
Process 3             # Assigns Categories based on Average and Standard Deviation
```
