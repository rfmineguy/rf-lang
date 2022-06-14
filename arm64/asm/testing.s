.global _start
 .align 2

 _start:
     sub sp, sp, #16         ; give space for [int8, int8, int16] must be multiple of 16?

     mov     w3, #15
     strb    w3, [sp, #3]      ; store 15 into the first local var
     mov     w3, #56
     strb    w3, [sp, #2]

     ; setup call to add two
     strb    w1, [sp, #-1]
     strb    w2, [sp, #-2]
     bl      add_two            ; branch and link to add_two (similar to call from x86)
     str     w0, [sp, #-3]

     add sp, sp, #16
     ret

 add_two:
     sub sp, sp, #4
     add w0, w1, w2
     add sp, sp, #4
     ret
