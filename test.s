.intel_syntax noprefix
.globl main
.data
g_memo_fib:
  .zero 400
.section .rodata
.LC53:
  .string "\343\202\263\343\203\241\343\203\263\343\203\210"
.LC52:
  .string "hello"
.LC51:
  .string "\346\226\207\345\255\227\345\210\227\343\203\252\343\203\206\343\203\251\343\203\253"
.LC50:
  .string "char\345\236\213\343\201\256\346\274\224\347\256\227"
.LC49:
  .string "char\345\236\213\345\244\211\346\225\260\343\201\256\345\256\232\347\276\251"
.LC48:
  .string "\343\202\260\343\203\255\343\203\274\343\203\220\343\203\253\345\244\211\346\225\260\343\202\222\345\210\251\347\224\250\343\201\227\343\201\237\345\206\215\345\270\260\351\226\242\346\225\260\343\201\256\343\203\241\343\203\242\345\214\226"
.LC47:
  .string "\351\205\215\345\210\227\343\201\253\346\267\273\345\255\227\346\274\224\347\256\227\343\201\247\343\202\242\343\202\257\343\202\273\343\202\271"
.LC46:
  .string "\351\205\215\345\210\227\343\201\253\343\203\235\343\202\244\343\203\263\343\202\277\346\274\224\347\256\227\343\201\247\343\202\242\343\202\257\343\202\273\343\202\271"
.LC45:
  .string "\351\205\215\345\210\227\343\201\256\345\256\232\347\276\251"
.LC44:
  .string "sizeof ptr"
.LC43:
  .string "sizeof int"
.LC42:
  .string "..."
.LC41:
  .string "..."
.LC40:
  .string "..."
.LC39:
  .string "..."
.LC38:
  .string "\343\202\242\343\203\211\343\203\254\343\202\271 + \346\225\264\346\225\260"
.LC37:
  .string "..."
.LC36:
  .string "..."
.LC35:
  .string "..."
.LC34:
  .string "..."
.LC33:
  .string "\343\202\242\343\203\211\343\203\254\343\202\271 + \346\225\264\346\225\260"
.LC32:
  .string "2\351\207\215\343\203\207\343\203\252\343\203\225\343\202\241\343\203\254\343\203\263\343\202\271"
.LC31:
  .string "\343\202\242\343\203\211\343\203\254\343\202\271\346\274\224\347\256\227\345\255\220 & \343\203\207\343\203\252\343\203\225\343\202\241\343\203\254\343\203\263\343\202\271\346\274\224\347\256\227\345\255\220"
.LC30:
  .string "fib(\343\203\241\343\203\242\345\214\226\343\201\252\343\201\227)"
.LC29:
  .string "\345\206\215\345\270\260\351\226\242\346\225\260(factorial)"
.LC28:
  .string "\351\226\242\346\225\260\345\221\274\343\201\263\345\207\272\343\201\227(\345\274\225\346\225\2606\343\201\244)"
.LC27:
  .string "\351\226\242\346\225\260\345\221\274\343\201\263\345\207\272\343\201\227(\345\274\225\346\225\2601\343\201\244)"
.LC26:
  .string "\351\226\242\346\225\260\345\221\274\343\201\263\345\207\272\343\201\227(\345\211\257\344\275\234\347\224\250\343\201\202\343\202\212)"
.LC25:
  .string "\351\226\242\346\225\260\345\221\274\343\201\263\345\207\272\343\201\227"
.LC24:
  .string "block\346\226\207"
.LC23:
  .string "for\346\226\207"
.LC22:
  .string "while\346\226\207"
.LC21:
  .string "if-else\346\226\207(false\343\201\256\346\231\202)"
.LC20:
  .string "if-else\346\226\207(true\343\201\256\346\231\202)"
.LC19:
  .string "if\346\226\207(false\343\201\256\346\231\202)"
.LC18:
  .string "if\346\226\207(true\343\201\256\346\231\202)"
.LC17:
  .string "\345\244\232\351\207\215\343\201\256\344\270\270\346\213\254\345\274\247"
.LC16:
  .string "\344\270\215\347\255\211\345\217\267 <="
.LC15:
  .string "\344\270\215\347\255\211\345\217\267 >="
.LC14:
  .string "\344\270\215\347\255\211\345\217\267 >"
.LC13:
  .string "\344\270\215\347\255\211\345\217\267 <"
.LC12:
  .string "not equal"
.LC11:
  .string "\347\255\211\345\217\267"
.LC10:
  .string "+x, -x"
.LC9:
  .string "\345\211\262\343\202\212\347\256\227"
.LC8:
  .string "\346\216\233\343\201\221\347\256\227"
.LC7:
  .string "\350\266\263\343\201\227\347\256\227 2"
.LC6:
  .string "\350\266\263\343\201\227\347\256\227 1"
.LC5:
  .string "\346\225\264\346\225\260\343\203\252\343\203\206\343\203\251\343\203\253 2"
.LC4:
  .string "\346\225\264\346\225\260\343\203\252\343\203\206\343\203\251\343\203\253"
.LC3:
  .string "\350\244\207\346\225\260\343\201\256return"
.LC2:
  .string "return"
.LC1:
  .string "\350\244\207\346\225\260\346\226\207\345\255\227\343\201\256\345\244\211\346\225\260"
.LC0:
  .string "1\346\226\207\345\255\227\343\201\256\345\244\211\346\225\260"
.text
test_variables:
  push rbp
  mov rbp, rsp
  sub rsp, 24
  # ローカル変数名: xxx
  # ローカル変数名: baz
  # ローカル変数名: bar
  # ローカル変数名: foo
  # ローカル変数名: b
  # ローカル変数名: a
  # vvv
  mov rax, rbp
  sub rax, 4
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 8
  push rax
  push 5
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  lea rax, [rip + .LC0]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 3
  pop rdi
  pop rax
  add rax, rdi
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  push 30
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 12
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 16
  push rax
  push 2
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 20
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 24
  push rax
  push 4
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  lea rax, [rip + .LC1]
  push rax
  mov rax, rbp
  sub rax, 20
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 24
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  mov rax, rbp
  sub rax, 12
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 14
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
test_return_1:
  push rbp
  mov rbp, rsp
  # vvv
# >>> ND_RETURN
  push 8
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
test_return_2:
  push rbp
  mov rbp, rsp
  # vvv
# >>> ND_RETURN
  push 4
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
# >>> ND_RETURN
  push 8
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
test_return:
  push rbp
  mov rbp, rsp
  # vvv
  lea rax, [rip + .LC2]
  push rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test_return_1
  mov rsp, rbp
  pop rbp
  push rax
  push 8
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC3]
  push rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test_return_2
  mov rsp, rbp
  pop rbp
  push rax
  push 4
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
fact:
  push rbp
  mov rbp, rsp
  sub rsp, 4
  # ローカル変数名: a
  mov rax, rbp
  sub rax, 4
  mov [rax], edi
  # vvv
# <<< ND_IF0
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 0
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend0
# >>> ND_RETURN
  push 1
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
.Lend0: # <<< ND_IF0
# >>> ND_RETURN
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  sub rax, rdi
  push rax
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fact
  mov rsp, rbp
  pop rbp
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
fib:
  push rbp
  mov rbp, rsp
  sub rsp, 4
  # ローカル変数名: a
  mov rax, rbp
  sub rax, 4
  mov [rax], edi
  # vvv
# <<< ND_IF1
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 0
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend1
# >>> ND_RETURN
  push 0
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
.Lend1: # <<< ND_IF1
# <<< ND_IF2
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend2
# >>> ND_RETURN
  push 1
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
.Lend2: # <<< ND_IF2
# >>> ND_RETURN
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  sub rax, rdi
  push rax
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fib
  mov rsp, rbp
  pop rbp
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
  pop rdi
  pop rax
  sub rax, rdi
  push rax
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fib
  mov rsp, rbp
  pop rbp
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
fib_2:
  push rbp
  mov rbp, rsp
  sub rsp, 4
  # ローカル変数名: a
  mov rax, rbp
  sub rax, 4
  mov [rax], edi
  # vvv
# <<< ND_IF3
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 0
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend3
# >>> ND_RETURN
  push 0
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
.Lend3: # <<< ND_IF3
# <<< ND_IF4
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend4
# >>> ND_RETURN
  push 1
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
.Lend4: # <<< ND_IF4
# <<< ND_IF5
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 100
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  lea rax, g_memo_fib[rip]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rax
  cmp rax, 0
  je .Lend5
# >>> ND_RETURN
  lea rax, g_memo_fib[rip]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
.Lend5: # <<< ND_IF5
# >>> ND_RETURN
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  sub rax, rdi
  push rax
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fib_2
  mov rsp, rbp
  pop rbp
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
  pop rdi
  pop rax
  sub rax, rdi
  push rax
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fib_2
  mov rsp, rbp
  pop rbp
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov rsp, rbp
  pop rbp
  ret # <<< ND_RETURN
  # ^^^
  mov rsp, rbp
  pop rbp
  mov rax, 0
  ret
main:
  push rbp
  mov rbp, rsp
  sub rsp, 188
  # ローカル変数名: chars
  # ローカル変数名: c
  # ローカル変数名: arr
  # ローカル変数名: arr_ptr_ptr_int
  # ローカル変数名: arr_int
  # ローカル変数名: pp
  # ローカル変数名: p
  # ローカル変数名: b
  # ローカル変数名: a
  # vvv
  lea rax, [rip + .LC4]
  push rax
  push 0
  push 0
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC5]
  push rax
  push 42
  push 42
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC6]
  push rax
  push 5
  push 20
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 4
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  push 21
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC7]
  push rax
  push 40
  push 13
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  push 5
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 32
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC8]
  push rax
  push 5
  push 6
  push 7
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 47
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC9]
  push rax
  push 10
  push 3
  pop rdi
  pop rax
  cqo
  idiv rdi
  push rax
  push 3
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC10]
  push rax
  push 2
  push 0
  push 2
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 10
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 10
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC11]
  push rax
  push 1
  push 1
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC12]
  push rax
  push 10
  push 42
  pop rdi
  pop rax
  cmp rax, rdi
  setne al
  movzx rax, al
  push rax
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC13]
  push rax
  push 5
  push 3
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  push 0
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC14]
  push rax
  push 3
  push 5
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC15]
  push rax
  push 3
  push 5
  pop rdi
  pop rax
  cmp rax, rdi
  setle al
  movzx rax, al
  push rax
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC16]
  push rax
  push 5
  push 3
  pop rdi
  pop rax
  cmp rax, rdi
  setle al
  movzx rax, al
  push rax
  push 0
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC17]
  push rax
  push 0
  push 0
  push 3
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  push 0
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test_variables
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test_return
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
# <<< ND_IF6
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend6
  mov rax, rbp
  sub rax, 4
  push rax
  push 2
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
.Lend6: # <<< ND_IF6
  lea rax, [rip + .LC18]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
# <<< ND_IF7
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 10
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lend7
  mov rax, rbp
  sub rax, 4
  push rax
  push 2
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
.Lend7: # <<< ND_IF7
  lea rax, [rip + .LC19]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lelse8
  mov rax, rbp
  sub rax, 4
  push rax
  push 2
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  jmp .Lend8
.Lelse8:
  mov rax, rbp
  sub rax, 4
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
.Lend8:
  lea rax, [rip + .LC20]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 10
  pop rdi
  pop rax
  cmp rax, rdi
  sete al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je .Lelse9
  mov rax, rbp
  sub rax, 4
  push rax
  push 2
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  jmp .Lend9
.Lelse9:
  mov rax, rbp
  sub rax, 4
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
.Lend9:
  lea rax, [rip + .LC21]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 3
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 8
  push rax
  push 0
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
.Lbegin10:
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 10
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je  .Lend10
  mov rax, rbp
  sub rax, 8
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  jmp .Lbegin10
.Lend10:
  lea rax, [rip + .LC22]
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 45
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 8
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
.Lbegin11:
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 5
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je  .Lend11
  mov rax, rbp
  sub rax, 8
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  jmp .Lbegin11
.Lend11:
  lea rax, [rip + .LC23]
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 24
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 8
  push rax
  push 1
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  lea rax, [rip + .LC24]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC25]
  push rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call foo
  mov rsp, rbp
  pop rbp
  push rax
  push 42
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC26]
  push rax
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call bar
  mov rsp, rbp
  pop rbp
  push rax
  push 0
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC27]
  push rax
  push 7
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call mod4
  mov rsp, rbp
  pop rbp
  push rax
  push 3
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC28]
  push rax
  push 1
  push 2
  push 3
  push 4
  push 5
  push 6
pop r9
pop r8
pop rcx
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call potato
  mov rsp, rbp
  pop rbp
  push rax
  push 321
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC29]
  push rax
  push 5
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fact
  mov rsp, rbp
  pop rbp
  push rax
  push 120
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC30]
  push rax
  push 13
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fib
  mov rsp, rbp
  pop rbp
  push rax
  push 233
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 10
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 16
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  pop rax
  lea rax, [rip + .LC31]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 10
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 42
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 16
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 24
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  pop rax
  lea rax, [rip + .LC32]
  push rax
  mov rax, rbp
  sub rax, 24
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 42
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 16
  push rax
  push 2
  push 4
  push 8
  push 16
  push 32
pop r8
pop rcx
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call alloc5
  mov rsp, rbp
  pop rbp
  push rax
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  pop rax
  lea rax, [rip + .LC33]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC34]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 1
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC35]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 2
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 8
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC36]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 3
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 16
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC37]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 4
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 32
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 16
  push rax
  push 2
  push 4
  push 8
  push 16
  push 32
pop r8
pop rcx
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call alloc5
  mov rsp, rbp
  pop rbp
  push rax
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 16
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 5
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  pop rax
  lea rax, [rip + .LC38]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 1
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 32
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC39]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 2
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 16
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC40]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 3
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 8
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC41]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 4
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC42]
  push rax
  mov rax, rbp
  sub rax, 16
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 5
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 2
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC43]
  push rax
  push 4
  push 4
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC44]
  push rax
  push 8
  push 8
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC45]
  push rax
  push 1
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 0
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
.Lbegin12:
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 10
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je  .Lend12
  mov rax, rbp
  sub rax, 184
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 184
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call putnum
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  jmp .Lbegin12
.Lend12:
  lea rax, [rip + .LC46]
  push rax
  mov rax, rbp
  sub rax, 184
  push rax
  push 3
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 9
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  push 0
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
.Lbegin13:
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 10
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzx rax, al
  push rax
  pop rax
  cmp rax, 0
  je  .Lend13
  mov rax, rbp
  sub rax, 184
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 10
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  push 10
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 4
  push rax
  mov rax, rbp
  sub rax, 4
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  jmp .Lbegin13
.Lend13:
  lea rax, [rip + .LC47]
  push rax
  mov rax, rbp
  sub rax, 184
  push rax
  push 6
  push 4
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  mov eax, [rax]
  push rax
  push 16
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC48]
  push rax
  push 32
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call fib
  mov rsp, rbp
  pop rbp
  push rax
  push 2178309
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC49]
  push rax
  push 1
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  mov rax, rbp
  sub rax, 188
  push rax
  push 0
  push 1
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 0
  push 1
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rdi
  pop rax
  mov [rax], dil
  push rdi
  pop rax
  mov rax, rbp
  sub rax, 8
  push rax
  push 4
  pop rdi
  pop rax
  mov [rax], edi
  push rdi
  pop rax
  lea rax, [rip + .LC50]
  push rax
  mov rax, rbp
  sub rax, 188
  push rax
  push 0
  push 1
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  movsx rax, BYTE PTR [rax]
  push rax
  mov rax, rbp
  sub rax, 8
  push rax
  pop rax
  mov eax, [rax]
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  push 3
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC51]
  push rax
  lea rax, [rip + .LC52]
  push rax
  push 1
  push 1
  pop rdi
  pop rax
  imul rax, rdi
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  movsx rax, BYTE PTR [rax]
  push rax
  push 101
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
  mov rsp, rbp
  pop rbp
  push rax
  pop rax
  lea rax, [rip + .LC53]
  push rax
  push 1
  push 1
pop rdx
pop rsi
pop rdi
  mov al, 0
  push rbp
  mov rbp, rsp
  and rsp, -16
  call test
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
