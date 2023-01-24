#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define TAM1 250
#define TAM2 150


int vetor[200], tamanho_total, final_enderecos, comeco_secdados;
char saida[TAM2][150];

int verifica_label(char * aux){    //Retorna 1 se sting possui : (label) ou 0 se não possui
    int i;
    for (i = 0; i < strlen(aux); i++){
            if (aux[i] == ':')
                return 1;
    }
    return 0;
}
void le_arquivo(char* nome_arquivo){   //Função que abre o arquivo, lê ele e separa os números lidos no vetor
    FILE * arq;
    char str[1000], *aux;
    int i = 0;
    arq = fopen(nome_arquivo, "rt");
    if (arq == NULL){
        printf("Arquivo nao encontrado\n");
    }
    else{
        while(!feof(arq)){
                fgets(str,1000,arq);
}
    }
    aux = strtok(str, " ");
    while (aux){
        vetor[i] = atoi(aux);
        i++;
        aux = strtok(NULL, " ");

    }
    tamanho_total = i;
    fclose(arq);

}

void escreve_saida(){
    int i = 0, num;

    while (i < tamanho_total){
        num = vetor[i];
        if (num == 1){
            strcpy(saida[i], "add eax, label\n");
            i+= 2;}
        else if (num == 2){
            strcpy(saida[i], "sub eax, label\n");
            i+=2;}
        else if (num == 3){
            strcpy(saida[i], "mul eax, label\n");
            i+=2;}
        else if (num == 4){
            strcpy(saida[i], "div eax, label\n");
            i+=2;}
        else if (num == 5){
            strcpy(saida[i], "jmp eax, label\n");
            i+=2;}
        else if (num == 6){ //jmpn
            strcpy(saida[i], "cmp eax, 0\njl label");
            i+=2;}
        else if (num == 7){ //jmpp
            strcpy(saida[i], "cmp eax, 0\njg label\n");
            i+=2;}
        else if (num == 8){ //jmpz
            strcpy(saida[i], "cmp eax, 0\nje, label\n");
            i+=2;}
        else if (num == 9){ //copy
            strcpy(saida[i], "copy\n");
            i+=3;}
        else if (num == 10){ //load
            strcpy(saida[i], "load\n");
            i+=2;}
        else if (num == 11){ // store
            strcpy(saida[i], "store\n");
            i+=2;}
        else if (num == 12){ // input
            strcpy(saida[i], "input\n");
            i+=2;}
        else if (num == 13){ //output
            strcpy(saida[i], "output\n");
            i+=2;}
        else if (num == 14){
            strcpy(saida[i], "stop\n");
            i+=1;
            break;}
        else if (num == 15){
            strcpy(saida[i], "s_input eax, label\n");
            sprintf(saida[i+2], "%d", vetor[i+2]);
            i+=3;}
        else if (num == 16){
            strcpy(saida[i], "s_output eax, label\n");
            sprintf(saida[i+2], "%d", vetor[i+2]);
            i+=3;}
    }
    comeco_secdados = i;
    while(i < tamanho_total){
        sprintf(saida[i], "CONST %d\n", vetor[i]);
        i++;
    }
    final_enderecos = i;

}

void define_labels(){
    char aux[500], aux2[500];
    int i, conta_label = 0;
        for (i = 0; i < final_enderecos; i++){
        if (i == 0){ //Colocar a label _start na primeira linha
            strcpy(aux, saida[i]);
            sprintf(saida[i], "_start: %s", aux);
        }
        if (strcmp(saida[i], "None!")== 0){
            strcpy(aux,saida[vetor[i]]);
            if (verifica_label(aux)){
                strcpy(saida[i],strtok(aux, ":"));
                strcat(saida[i], "");
            }
            else {
                sprintf(aux, "label_%d: ", conta_label);
                strcpy(saida[i], aux);
                strcpy(aux2, saida[vetor[i]]);;
                strcat(aux, aux2);
                strcpy(saida[vetor[i]], aux);

                sprintf(aux, "label_%d", conta_label);
                strcpy(saida[i], aux);
                conta_label++;

        }

        }
}
        for (i = comeco_secdados; i < final_enderecos; i++){  // Coloca label nas variáveis que n foram utilizadas
            strcpy(aux, saida[i]);
            if (verifica_label(aux) == 0){
                sprintf(saida[i], "label_%d: %s", conta_label, aux);
                conta_label++;
            }
        }
}

void escreve_saida_final(){
    char aux[350], auxlabel[200];
    int i = 0, num;
    while (i < final_enderecos){
       strcpy(auxlabel, saida[i]);
       num = vetor[i];
        if (num == 1){
            sprintf(aux, "add eax, [%s]\n", saida[i+1]);
            }
        else if (num == 2){
            sprintf(aux, "sub eax, [%s]\n", saida[i+1]);
            }
        else if (num == 3){
            sprintf(aux, "imul dword[%s]\njo overflow_multiplica\n", saida[i+1]);
            }
        else if (num == 4){
            sprintf(aux, "cdq\nidiv dword[%s]\n", saida[i+1]);
            }
        else if (num == 5){
            sprintf(aux, "jmp %s\n", saida[i+1]);
            }
        else if (num == 6){ //jmpn
            sprintf(aux, "cmp eax, 0\njl %s\n", saida[i+1]);
            }
        else if (num == 7){ //jmpp
            sprintf(aux, "cmp eax, 0\njg %s\n", saida[i+1]);
            }
        else if (num == 8){ //jmpz
            sprintf(aux, "cmp eax, 0\njz %s\n", saida[i+1]);
            }
        else if (num == 9){ //copy
            sprintf(aux, "mov ebx, [%s]\nmov [%s], ebx\n", saida[i+1],saida[i+2]);
            //sprintf(saida[vetor[i+1]], "%s: SPACE %d\n",saida[i+1], vetor[vetor[i+1]]);
            sprintf(saida[vetor[i+2]], "%s: SPACE %d\n",saida[i+2], vetor[vetor[i+2]]);
            }
        else if (num == 10){ //load
            sprintf(aux, "mov eax, [%s]\n", saida[i+1]);
            }
        else if (num == 11){ // store
            sprintf(aux, "mov [%s], eax\n", saida[i+1]);
            sprintf(saida[vetor[i+1]], "%s: SPACE %d\n",saida[i+1], vetor[vetor[i+1]]);
            }
        else if (num == 12){ // input
            //sprintf(aux, "push eax\nmov eax, 3\nmov ebx, 0\nmov ecx, %s\nmov edx, 4\nint 80h\npop eax\n", saida[i+1]);
            sprintf(aux, "push %s\ncall func_input\n",saida[i+1]);
            sprintf(saida[vetor[i+1]], "%s: SPACE %d\n",saida[i+1], vetor[vetor[i+1]]);
            }
        else if (num == 13){ //output
            //sprintf(aux, "push eax\nmov eax, 4\nmov ebx, 1\nmov ecx, %s\nmov edx, 4\nint 80h\npop eax\n", saida[i+1]);
            sprintf(aux, "push %s\ncall func_output\n", saida[i+1]);
            sprintf(saida[vetor[i+1]], "%s: SPACE %d\n",saida[i+1], vetor[vetor[i+1]]);
            }
        else if (num == 14){
            sprintf(aux, "mov eax, 1\nmov ebx,0\nint 80h\n");}
        else if (num == 15){  //Na contagem de bytes lidos/escritos dessas funções, o byte de enter também é contado caso seja lido
            sprintf(aux, "push %s\nmov ebx, %s\npush ebx\ncall func_s_input\n", saida[i+1], saida[i+2]);
            }
        else if (num == 16){
            sprintf(aux, "push %s\nmov ebx, %s\npush ebx\ncall func_s_output\n", saida[i+1], saida[i+2]);
            }

    if (verifica_label(auxlabel)){
        strtok(auxlabel, ":");
        strcat(auxlabel, ":");
        strcat(auxlabel, aux);
        strcpy(aux, auxlabel);
    }
    strcpy(saida[i], aux);

    if (num == 14){
        break;}
    else if (num == 9 || num == 16 || num == 15){
        i+=3;}
    else{
        i+=2;}
    }
}

void const_para_space5(){ // Inicialmente todas as linhas da seção de dados foram consideradas como Const - portanto essa função serve para identificar quais destes devem ser Space
    int i = 0, num, i2, num2;
    char aux[200];
    while (i<final_enderecos){
        num = vetor[i];
        if((num == 15 || num == 16) && (strcmp(saida[vetor[i+1]+1], "NULL!"))){ // Se for s input ou s output e já n tiver alterado
            num2 = num;
            num = 0;
            i2 = vetor[i+1];
            while (vetor[i2] == 0 && i2 < final_enderecos){
                num++;
                i2++;
            }
            strcpy(aux,saida[vetor[i+1]]);
            strtok(aux, ":");
            sprintf(saida[vetor[i+1]], "%s: SPACE %d\n", aux, num);
            vetor[vetor[i+1]] = num;
            num --;
            while (num){
                sprintf(saida[vetor[i+1]+num], "NULL!");
                num --;}
            num = num2;
        }
        if (num == 9 || num == 16 || num == 15)
            i+=3;
        else if (num == 14)
            break;

        else if (1 <= num && num <= 13)
            i+=2;
}
}


void escreve_sec_dados_arq(FILE* arq){
    int i = comeco_secdados, inicio = 1;
    char aux[200], *aux2, *aux3;
    fprintf(arq, "\n");
    while (i < final_enderecos){
            strcpy(aux, saida[i]);
            if (strcmp(aux, "NULL!")){
            aux3 = strtok(aux, ":");
            aux2 = strtok(NULL, " ");
            if (strcmp(aux2, "CONST")==0){
                    if (inicio){
                        fprintf(arq,"section .data\n\n");
                        inicio --;
                    }
                    fprintf(arq,"%s dd %d\n", aux3, vetor[i]);
            }
    }i++;}
    inicio = 1;
    fprintf(arq,"\n");
    i = comeco_secdados;
    while (i < final_enderecos){
            strcpy(aux, saida[i]);
            if (strcmp(aux, "NULL!")){
            aux3 = strtok(aux, ":");
            aux2 = strtok(NULL, " ");
            if (strcmp(aux2, "SPACE")==0){
                    if (inicio){
                        fprintf(arq,"section .bss\n\n");
                        inicio --;
                    }
                    if (vetor[i] == 0){
                        vetor[i]++;
                        fprintf(arq,"%s resd %d\n", aux3, vetor[i]);}
                    else {//Se for um space com mais de um espaço, reservar byte e não dwords
                       fprintf(arq,"%s resb %d\n", aux3, vetor[i]);}
            }

    }i++;
    }
    fprintf(arq,"\n");
}

void escreve_sec_texto_arq(FILE *arq){
    int i = 0;
    fprintf(arq,"section .text\nglobal _start\n");
    while (i < final_enderecos){
        fprintf(arq,"%s", saida[i]);
    if (vetor[i] == 14){
        break;}
    else if (vetor[i] == 9 || vetor[i] == 15|| vetor[i] == 16){
        i+=3;}
    else{
        i+=2;}
    }
}

void escreve_arquivo_saida(char *nome_arquivo_entrada){
    FILE * arq_saida, *arq_funcoes;
    char aux[200], aux2[205];
    arq_funcoes = fopen("funcoes.asm","rt");
    strcpy(aux, nome_arquivo_entrada);
    strtok(aux, ".");
    sprintf(aux2, "%s.s", aux);
    arq_saida = fopen(aux2, "wt");
    while(!feof(arq_funcoes)){             // Lê linha por linha do arquivo das funções e escreve do arquivo de saída
        fgets(aux, 200, arq_funcoes);
        fputs(aux, arq_saida);
    }
    fclose(arq_funcoes);
    escreve_sec_dados_arq(arq_saida);
    escreve_sec_texto_arq(arq_saida);
}

int main(int argc, char** argv){
    char * nome_arquivo;
    int i = 0;
    nome_arquivo = argv[1];
    le_arquivo(nome_arquivo);
    for (i = 0; i < TAM2; i++)
        strcpy(saida[i],"None!");
    escreve_saida();
    define_labels();
    escreve_saida_final();
    const_para_space5();
    escreve_arquivo_saida(nome_arquivo);
}


