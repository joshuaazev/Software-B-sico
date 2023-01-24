Alunos:
Gustavo Joshua de Faria Costa de Azevedo - 19/0014105
Carlos Gustavo Muniz Simões - 19/0042311

Editor: CodeBlocks
Sistema Operacional: Windows 10
Compilador: MinGW gcc 4.9.2

Para executar o programa, deve ser utilizado o CodeBlocks

A pasta Montador contém os arquivos necessários para executar o montador
É necessário abrir o arquivo do projeto no CodeBlocks (.cdp) e para passar os argumentos do programa
basta clicar na aba Project->Set Programs´ arguments, e digitar o argumento que deve ser no formato:

-p arquivo1.asm arquivo2.obj

em que -p é o modo, o arquivo1.asm é o arquivo de entrada e o arquivo2.obj é o arquivo de saída.
O arquivo de entrada deve estar dentro da pasta Montador para a execução.
Após passar os argumentos, basta compilar o arquivo main.c para a execução do programa


A pasta Ligador contém os arquivos necessários para executar o ligador
É necessário abrir o arquivo do projeto no CodeBlocks (.cdp) e para passar os argumentos do programa
basta clicar na aba Project->Set Programs´ arguments, e digitar o argumento que deve ser no formato:

arquivo1.o arquivo2.o

em que arquivo1.o e arquivo2.o são os arquivos de entrada do ligador.
Os arquivos de entrada devem estar dentro da pasta Ligador para a execução.
Após passar os argumentos, basta compilar o arquivo main.c para a execução do programa
A saída do ligador sempre será o arquivo "saida_ligador.o"

