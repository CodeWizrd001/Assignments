# Cursor Control Driver

Driver that moves curson and simulates mouse button clicks

## Commands to run : 
```
sudo mknod -m 666 /dev/mouseController c 240 0        # To Create mouseController Device
make here                                             # To Compile the driver Code
make clean                                            # To Remove the comoiled files 
sudo insmod ./mouseController.ko                      # To Load the module
sudo rmmod mouseController                            # To remove the module 
```
## Makefile: 
```
obj-m := mouseController.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
here:
  make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD)
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```
## TEAM MEMBERS:
##### Basil Varghese
##### Arjun Syam
##### Anshif Moossa K
##### Amal Raj
##### Ajay P Sakthikumar
