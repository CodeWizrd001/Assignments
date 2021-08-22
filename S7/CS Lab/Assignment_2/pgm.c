char shellcode[] = "\xeb\x1f...";

int main(int argc, char *argv[])
{
    void (*shell)() = (void *) shellcode;
    shell();
    return 0;
}