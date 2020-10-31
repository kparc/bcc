BITS 64
    org     0x10000
e:                                                  ; Elf64_Ehdr
            db      0x7F, "ELF", 2, 1, 1, 0         ;   e_ident
    times 8 db      0
            dw      2                               ;   e_type       ET_EXEC    =  2
            dw      62                              ;   e_machine    EM_X86_64  = 62
            dd      1                               ;   e_version    EV_CURRENT =  1
            dq      a                               ;   e_entry
            dq      p-$$                            ;   e_phoff
            dq      0                               ;   e_shoff
            dd      0                               ;   e_flags
            dw      en                              ;   e_ehsize
            dw      pn                              ;   e_phentsize
            dw      1                               ;   e_phnum
            dw      0                               ;   e_shentsize
            dw      0                               ;   e_shnum
            dw      0                               ;   e_shstrndx
en equ $-e
p:                                                  ; Elf64_Phdr
            dd      1                               ;   p_type
            dd      5                               ;   p_flags
            dq      0                               ;   p_offset
            dq      $$                              ;   p_vaddr
            dq      $$                              ;   p_paddr
            dq      n                               ;   p_filesz
            dq      n                               ;   p_memsz
            dq      0                               ;   p_align
pn equ $-p
a:
            mov     dil, 1
            mov     al,  60
            syscall
n equ $-$$