.intel_syntax noprefix
.globl main

.section .text
main:
  push rbp
  mov rbp, rsp
  sub rsp, 8
  # a: rbp-4, b: rbp-8
  mov rax, 0x0011223344556677
  mov [rbp-8], rax
  mov rax, [rbp-4]
  mov rdi, [rbp-8]
  add rax, rdi
  # ret
  push 0
  pop rax
  mov rsp, rbp
  pop rbp
  ret
