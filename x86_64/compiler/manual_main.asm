section .data
    str_lit_0: db "Hello World", 0h

section .bss

section .text
global main

main:                               ; FUNC ID OPEN_PAREN CLOSE_PAREN ARROW TYPE
    push rbp                        ; OPEN_BRACE
    mov rbp, rsp                    ;
    
                                    ; OPEN_PAREN
    push 0x94                       ; HLITERAL COMMA
    push 10110101b                  ; BLITERAL
                                    ; CLOSE_PAREN
    call add_byte_byte__word        ; SEMI

    mov rax, str_lit_0              ; OPEN_PAREN
    push rax                        ; 
    call print_byteptr__void        

    mov rsp, rbp                    ; CLOSE_BRACE
    pop rbp                         ;

add_byte_byte__word:                ; FUNC ID OPEN_PAREN TYPE ID COMMA TYPE ID CLOSE_PAREN ARROW TYPE (Note: this is reworked a little to match the declaration)
    push rbp                        ; OPEN_BRACE
    mov rbp, rsp                    ;

    sub rbp, 2                      ; TYPE ID
    mov [rbp - 2], word [rbp + 8]   ; ASSIGN ID
    add [rbp - 2], word [rbp + 16]  ; PLUS ID SEMI
    inc byte [rbp + 8]              ; ID PLUS PLUS SEMI

    mov rax, 0
    mov ax, word [rbp - 2]          ; RET ID SEMI

    mov rsp, rbp                    ; CLOSE_BRACE
    pop rbp                         ;
    ret 8                           ; free 8 bytes pushed

print_byteptr__void:                ; FUNC ID OPEN_PAREN TYPE OPEN_BRACKET CLOSE_BRACKET ID CLOSE_PAREN ARROW TYPE OPEN_BRACE
    push rbp                        ; OPEN_BRACE
    mov rbp, rsp                    ;

    mov rsp, rbp                    ; CLOSE_BRACE
    pop rbp                         ;
    ret 4                           ; free 4 bytes pushed (pointer)

sub_byte_byte__qword:               ; FUNC ID OPEN_PAREN TYPE ID COMMA TYPE ID CLOSE_PAREN ARROW TYPE OPEN_BRACE
    push rbp                        ; OPEN_BRACE
    mov rbp, rsp                    ;

    mov rsp, rbp                    ; CLOSE_BRACE
    pop rbp                         ;
    ret 8                           ; free 8 bytes pushed
