%pragma macho64 prefix _
         global   main
         extern   printf

         section  .data
msg:     db       "The value is %d!", 10, 0
         section  .bss
num:     resb     80                        ; reserve 20 * 4 bytes

         section  .text
init:    push     rbp
         mov      rbp, rsp
         mov      r12, 0
startloop_1:
         cmp      r12, 20
         jge      endloop_1
         lea      r13, [rel num]
         mov      [r13,r12*4], r12
         inc      r12
         jmp      startloop_1
endloop_1:
         xor      rax, rax
         mov      rsp, rbp
         pop      rbp
         ret
main:    push     rbp
         mov      rbp, rsp
         call     init
         xor      rax, rax
         mov      rdi, msg
         lea      r13, [rel num]
         mov      rsi, [r13+76]
         call     printf
         xor      rax, rax
         mov      rsp, rbp
         pop      rbp
         ret