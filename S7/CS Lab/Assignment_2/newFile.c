void foo()
{
asm("jmp line\n\t"
    "address: popl %esi\n\t"
    "movl %esi, 0x08(%esi)\n\t"
    "xorl %eax, %eax\n\t"
    "movl %eax, 0xc(%esi)\n\t"
    "movb %al, 0x7(%esi)\n\t"
    "movb $0xb, %al\n\t"
    "movl %esi, %ebx\n\t"
    "leal 0x8(%esi), %ecx\n\t"
    "leal 0xc(%esi), %edx\n\t"
    "int $0x80\n\t"
    "xorl %ebx, %ebx\n\t"
    "movl %ebx, %eax\n\t"
    "inc %eax\n\t"
    "int $0x80\n\t"
    "line: call address\n\t"
    ".string \"/bin/sh\"\n\t"
    );
}

int main()
{
    foo();
}