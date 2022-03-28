# IPC Using Message Queues

Interprocess communication between unrelated processes

The ftok , msgget , msgget and msgrevc commands are used to create and use the message queues

## Files : 
```
q1_CI.c         # CI Program
q1_ST.c         # Student Program
q1_TA.c         # TA program
```
## Commands to run : 
```
gcc q1_CI.c -o ci && ./ci             # Compile and runs Program of process 1
gcc q1_ST.c -o st && ./st             # Compile and runs Program of process 2
gcc q1_TA.c -o ta && ./ta             # Compile and runs Program of process 3
```
## Processes
```
CI                    # Gets User Input and displays grades
TA                    # Calculates Average and Assigns Grades
Students              # Receives Marks
```
