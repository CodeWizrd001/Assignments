# IPC Using Shared Memory

Interprocess communication using Shared Memory Method

Shared lock variables are used to stop the execution of other processes before valid data is received

## Files : 
```
process_1.c                 # Receive Password and Display the strength of the password
process_2.c                 # Count the characers in password
process_3.c                 # Set Password Strength
```
## Commands to run : 
```
gcc process_1 -o p1 && ./p1       # Compile and run Process 1
gcc process_2 -o p2 && ./p2       # Compile and run Process 2
gcc process_3 -o p3 && ./p3       # Compile and run Process 3
```
## Shared Memory
```
pwd               # Starting of the shared block 10 characters
p1_flag           # Process 1 Lock                      (int)   20 bytes after pwd
p2_flag           # Process 2 Lock                      (int)   1 Integer after p1_flag
p3_flag           # Process 3 Lock                      (int)   1 Integer after p2_flag
alnum             # Number of Alphanumeric Characters   (int)   1 Integer after p3_flag
special           # Number of Special Characters        (int)   1 Integer after alnum
strength          # Strength of Password                (int)   1 Integer after Special
```
