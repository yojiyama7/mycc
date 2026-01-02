.intel_syntax noprefix
.globl main
.data
.section .rodata
.LC1:
  .string "hi"
.LC0:
  .string "aaa %s %d\n"
.text
main:
  push rbp
  mov rbp, rsp
  # vvv
  lea rax, [rip + .LC0]
  push rax
  lea rax, [rip + .LC1]
  push rax
  push 1
  push 1
  pop rdi
  pop rax
  add rax, rdi
  push rax
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call printf
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call end_test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
