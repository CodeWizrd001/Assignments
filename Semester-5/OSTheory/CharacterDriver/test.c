#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char buffer[100] ;
    char rBuff[100] ;
    int fd;
    fd=open("/dev/mouseController", O_RDWR);
    while(1) 
    {
        scanf("%s",buffer) ;
        write(fd,buffer,strlen(buffer));
        read(fd,rBuff,5);
    }
    close(fd);
}