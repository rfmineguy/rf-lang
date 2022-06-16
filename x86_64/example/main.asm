%include "math.asm"
%include "string.asm"

section .data
    c_array_0:  db "Hello World", 0ah, 0h           ;string literal
    c_array_1:  db "Boogers are good", 0ah, 0h      ;string literal 

section .bss
 
section .text
global _start
_start:                                                                                                       
    push rbp                                                                                                    
    mov rbp, rsp 
    sub rsp, 64                         ;make room for local variables
    
    mov byte  [rbp - 1],    4           ;byte b = 4
    mov word  [rbp - 3],    9842        ;word w = 9842
    mov dword [rbp - 7],    5213424     ;dword d = 5213424
    mov qword [rbp - 15],   0x8642786   ;qword q = 0x8642786
    mov qword [rbp - 23],   c_array_0   ;byte str[] = "Hello World\n";
    mov byte  [c_array_0],      'x'     ;str[0] = 'x';
    mov byte  [c_array_0 + 1],  'o'     ;str[1] = 'o';
    
    mov rax, qword c_array_0            ;word len = strlen(str);
    push rax                            ;
    call fun_strlen_str__word           ;
    mov word [rbp - 25], ax             ;
    
    mov qword [rbp - 33], c_array_1     ;byte str2[] = "Boogers are good\n"; 8byte pointer
    mov rax, qword c_array_1            ;len = strlen(str2);
    push rax
    call fun_strlen_str__word           ;
    mov word [rbp - 25], ax             ;
    
    mov rax, c_array_1                  ;printStr(str2);
    push rax                            ;
    call fun_printString_str__void      ;

    mov word [rbp - 35], 0              ;word arr[6] = [0, 3, 2, 5, 7, 8];
    mov word [rbp - 37], 3              ;
    mov word [rbp - 39], 2              ;
    mov word [rbp - 41], 5              ;
    mov word [rbp - 43], 7              ;
    mov word [rbp - 45], 8              ;

if_0:
    cmp word [rbp - 25], 4              ; if (len > 4)
    jl else_0                           ;
    push rbp                            ; start stackframe
    mov rbp, rsp                        ;  -
    sub rsp, 2                          ; 2 bytes local stackspace
    push 9                              ; word result = add(9, 4); 
    push 4                              ;  -
    call fun_add_a_b__word              ;  -
    mov word [rbp - 2], ax              ;  -
    mov rsp, rbp                        ; end stackframe
    pop rbp                             ;  -
    jmp endif_0                         ; continue passed else
else_0:                                 ; else
    push rbp                            ; start stackframe
    mov rbp, rsp                        ;  -
    sub rsp, 2                          ; 2 bytes local stackspace
    push 8                              ; word result = mul(8, 0x42)
    push 0x42                           ;  -
    call fun_mul_a_b__word              ;  -
    mov word [rbp - 2], ax              ;  -
    mov rsp, rbp                        ; end stackframe
    pop rbp                             ;  -
endif_0:
    
    movsx rax, byte [rbp - 1]           ;word result = add(b, b)
    push rax                            ;
    push rax                            ;
    call fun_add_a_b__word              ;
    mov word [rbp - 35], ax             ;

    movsx rax, byte [rbp - 1]           ;result = mul(b, b);
    push rax                            ;
    push rax                            ;
    call fun_mul_a_b__word              ;
    mov word [rbp - 47], ax             ;

    ;exit proc
    mov rax, 60                         ;ret q;                                                  
    mov rdi, [rbp - 15]                 ;
    syscall                             ;
    
    add rsp, 64
    mov rsp, rbp
    pop rbp
                                
    ret
