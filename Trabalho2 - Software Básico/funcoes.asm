section .data

pula_linha db 0dH, 0ah
foram_escritos db "Foram escritos "
tam_esc EQU $-foram_escritos
esc_bytes db " bytes", 0dh, 0ah
tam_bytes EQU $-esc_bytes
foram_lidos db "Foram lidos "
tam_lid EQU $-foram_lidos
over_mult db "Houve overflow na multiplicação", 0dh,0ah
tam_overflow EQU $-over_mult

section .bss

ponteiro resd 10
ponteiro2 resb 20

teste2 resd 1

section .text

func_input:enter 0,0
push eax
mov esi, ponteiro2
mov eax,3
mov ebx, 0
mov ecx, ponteiro2
mov edx, 13; valor máximo é -2bi - 11 digitos 
int 80h
mov ecx, eax; quantidade de bytes lidos
push ecx
push esi
mov eax, 0
cmp byte[esi], 45; saber se o primeiro dígito é um sinal de -
mov edi, 1
jnz loop_input
add esi, 1
mov edi, 0; quando edi == 0; quer dizer que o número é negativo e deve ser multiplicado por -1 no final

loop_input:
mov ebx, 0
mov bl, [esi]
sub bl, 0x30
cmp ecx, 1; se for o último digito, pula pro final
jz final_input
add esi, 1
cmp byte[esi], 0ah;  se o prox caracter for LF, já pula pro final
jz final_input
add eax, ebx
mov edx, eax;  multiplicando por 10
shl eax, 3
shl edx, 1
add eax, edx
loop loop_input

final_input:
add eax, ebx
cmp edi, 1; se edi == 1, quer dizer q o número é negativo
jz positivo
mov edi, -1
imul edi; multiplicando por -1
positivo:
pop esi
mov [esi], eax
mov edi, [ebp+8]
mov [edi], eax
mov eax, 4
mov ebx, 1
mov ecx, foram_lidos
mov edx, tam_lid
int 80h
pop ecx
add ecx, 47; 48 - 1 do LF
cmp ecx, 58
jl printa_1_digito; se não saltar é pq tem q printar mais de um dígito
mov esi, ecx
mov byte[ponteiro], 49; printar o número 1
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h
mov ecx, esi
sub ecx, 10
printa_1_digito:
mov [ponteiro], ecx
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h
mov eax, 4
mov ebx, 1
mov ecx, esc_bytes
mov edx, tam_bytes
int 80h
pop eax
leave
ret 4




func_output: enter 0,0
push eax
mov esi, [ebp+8]; o ponteiro utilizado
mov edi,[esi]; o número a ser imprimido
mov eax, edi
mov ebx, 0
push ebx
cmp eax, 0
jge loop_output; Se o número é positivo, pular direto pro loop, caso contrário, multiplicar por -1 e printar um -
neg edi
neg eax
push eax
mov byte[ponteiro2], 45
mov eax, 4
mov ebx, 1
mov ecx, ponteiro2
mov edx, 1
int 80h
pop eax
pop ebx
inc ebx; ebx conta a quantidade de bits escrita, nesse caso é adicionado 1
push ebx

loop_output:
mov ecx, 0
mov ebx, 10
mov edx, 0

cmp eax, 10; Pula pro final se o número for menor que 10 -> ou seja, é o útimo digito
jl final_output

div_dez: 
inc ecx
mov edx, 0
div ebx
cmp eax, 10
jge div_dez

mov [ponteiro], eax
add byte[ponteiro], 0x30 
pusha
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 4
int 80h
popa

pop ebx
inc ebx
push ebx

mov eax, 1
mov ebx, 10
eleva: ;função que eleva 10 a n-ésima potência, sendo n o único parâmetro da função -> retorna em eax
mul ebx
loop eleva

mod_do_numero:
mov ebx, eax
mov eax, edi
mov edx, 0
div ebx
mov eax, edx; eax é o mod da divisao 
push eax
mov edx, 0
mov eax, ebx
mov ecx, 10
div ecx
mov ebx, eax
pop eax
cmp eax, ebx
jge loop_output; se eax for maior que a potência de dez menor
cmp ebx, 1
jz loop_output; salta se é o último dígito

ciclo_printa_compara: 

pusha
mov byte[ponteiro], 48 ;->printar o 0
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 4
int 80h
popa

mov ecx, ebx
pop ebx
inc ebx
push ebx
mov ebx, ecx

push eax
push ecx
mov edx, 0
mov eax, ebx
mov ecx, 10
div ecx
mov ebx, eax
pop ecx
pop eax
cmp ebx, 1  ; Se é o último dígito do número
jz loop_output
cmp eax, ebx
jl ciclo_printa_compara

jmp loop_output

final_output: ;printa o último número e finaliza
mov [ponteiro], eax
add dword[ponteiro], 0x30 
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 4
int 80h

mov eax, 4
mov ebx, 1
mov ecx, pula_linha
mov edx, 2
int 80h

mov eax, 4
mov ebx, 1
mov ecx, foram_escritos
mov edx, tam_esc
int 80h
pop ebx
add ebx, 49; 48 + 1 que não foi contado do último print
cmp ebx, 58
jl printa_1_digito2; se não saltar é pq tem q printar mais de um dígito
mov esi, ebx
mov byte[ponteiro2], 49; printar o número 1
mov eax, 4
mov ebx, 1
mov ecx, ponteiro2
mov edx, 1
int 80h
mov ebx, esi
sub ebx, 10
printa_1_digito2:
mov [ponteiro], ebx
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h
mov eax, 4
mov ebx, 1
mov ecx, esc_bytes
mov edx, tam_bytes
int 80h
pop eax
leave
ret 4

func_s_input:
enter 0,0
push eax
mov eax, 3
mov ebx, 0
mov ecx, [EBP + 12]
mov edx, [EBP + 8]
int 80h

mov esi, eax ; quantos bytes realmente foram lidos

mov eax, 4
mov ebx, 1
mov ecx, foram_lidos
mov edx, tam_lid
int 80h

add esi, 48;
mov ecx, esi
cmp esi, 58
jl printa_1_digito3; se não saltar é pq tem q printar mais de um dígito
mov byte[ponteiro], 49; printar o número 1
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h

mov ecx, esi
sub ecx, 10

printa_1_digito3:
mov [ponteiro], ecx
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h
mov eax, 4
mov ebx, 1
mov ecx, esc_bytes
mov edx, tam_bytes
int 80h
pop eax
leave 
ret 8

func_s_output:
enter 0,0
push eax
mov eax, 4
mov ebx, 1
mov ecx, [EBP + 12]
mov edx, [EBP + 8]
int 80h

mov edi, eax; número de bytes mostrados

mov eax, 4
mov ebx, 1
mov ecx, pula_linha
mov edx, 2
int 80h

mov eax, 4
mov ebx, 1
mov ecx, foram_escritos
mov edx, tam_esc
int 80h

add edi, 48
mov ebx, edi
cmp ebx, 58
mov esi, ebx
jl printa_1_digito4; se não saltar é pq tem q printar mais de um dígito
mov byte[ponteiro], 49; printar o número 1
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h
mov ebx, esi
sub ebx, 10
printa_1_digito4:
mov [ponteiro], ebx
mov eax, 4
mov ebx, 1
mov ecx, ponteiro
mov edx, 1
int 80h
mov eax, 4
mov ebx, 1
mov ecx, esc_bytes
mov edx, tam_bytes
int 80h

pop eax
leave
ret 8


overflow_multiplica:
mov eax, 4
mov ebx, 1
mov ecx, over_mult
mov edx, tam_overflow
int 80h
mov eax,1 
mov ebx, 0
int 80h
