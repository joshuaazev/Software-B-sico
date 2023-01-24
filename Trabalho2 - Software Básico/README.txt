Alunos:
Gustavo Joshua de Faria Costa de Azevedo - 19/0014105
Carlos Gustavo Muniz Simões - 19/0042311

Sistema Operacional: Ubuntu 22.04

Passos para executar o programa no terminal do LINUX:

gcc main.c -o tradutor
./tradutor entrada.o

Sendo "entrada.o" o arquivo de entrada contendo o código objeto do programa em Assembly inventado
Isso vai gerar o arquivo entrada.s, que é o arquivo entrada.o traduzido para IA-32
O arquivo funcoes.asm contém todas funções pré-implementadas em IA-32 (Input, Output, S_Input e S_Output)
e ele todo é copiado para o arquivo de saída entrada.s


Para executar o arquivo em IA-32:

nasm -f elf -o saida.o entrada.s
ld -m elf_i386 -o saida saida.o
./saida

Pronto!!
