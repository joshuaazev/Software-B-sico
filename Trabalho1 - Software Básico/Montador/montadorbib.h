
#define TAM1 250
#define TAM2 150

typedef struct instrucao_struct{
    int opcode, linha, endereco, tamanho, dado;  //Se dado == 1, a instrução se refere a dado SPACE ou CONST, dado = 0 public extern and begin
    char rotulo[TAM2], inst[TAM2], operando_1[TAM2], operando_2[TAM2],trash[TAM2], erro[TAM2];
    struct instrucao_struct *proximo;
}instrucao_struct;

typedef struct{
    instrucao_struct *primeiro, *ultimo;
    } lista_instrucao;

typedef struct tabsim{
    char simbolo[TAM2];
    int endereco, linha, tipo;  //tipo = 0 -> Extern and tipo = 1 -> Public
    struct tabsim *proxima;
}tabsim;

typedef struct{
    tabsim *primeira, *ultima;
    } lista_simb;

char vetor_arquivo[TAM1][TAM2], palavra[TAM2*5] = "", lista_equ[TAM2][TAM2];
lista_instrucao lista[TAM1];
lista_simb lista_simbolos[TAM1];
lista_simb tab_uso[TAM1];
int sec_texto = 0, sec_dados = 0, lig = 0, uso = 1, endf = 0, beginf = 0;


void le_arquivo(char* nome_arquivo){
    FILE * arq;
    char str[TAM2];
    int contador_linha = 0;
    arq = fopen(nome_arquivo, "rt");
    if (arq == NULL){
        printf("Arquivo nao encontrado\n");
    }
    else{
        while(!feof(arq)){
    fgets(str,100, arq);
    strtok(str,"\n");
    strcpy(vetor_arquivo[contador_linha], str);
    strupr(vetor_arquivo[contador_linha]);
    //printf("%s\n", strupr(vetor_arquivo[contador_linha]));
    contador_linha+=1;
        }
        //printf("%d\n",contador_linha);
    }
    if(strcmp(vetor_arquivo[contador_linha-2], vetor_arquivo[contador_linha-1])==0){
        contador_linha--;
    }
    strcpy(vetor_arquivo[contador_linha], "FIM DO PROGRAMA");

    fclose(arq);
}



void escreve_struct(){
    int i = 0, contador;
    char instrucao_aux[TAM2], *instrucao_aux2, *instrucao_aux3, c;
    instrucao_struct *aux = (instrucao_struct*)malloc(sizeof(instrucao_struct)), *aux2;
    lista->primeiro = aux;
    while (strcmp(vetor_arquivo[i],"FIM DO PROGRAMA")!= 0){
        contador = 0;

        aux2 = (instrucao_struct*)malloc(sizeof(instrucao_struct));
        aux -> proximo = aux2;
        strcpy(aux ->rotulo," NULL ");
        strcpy(aux ->inst," NULL ");
        strcpy(aux ->operando_1," NULL ");
        strcpy(aux ->operando_2," NULL ");
        strcpy(aux ->trash," NULL ");
        strcpy(aux ->erro," NULL ");
        aux->linha = i+1;

        strcpy(instrucao_aux,vetor_arquivo[i]);
        instrucao_aux2 = strtok(instrucao_aux, ";");  // Retirar comentários
        c = instrucao_aux2[strlen(instrucao_aux2)-1];
        //printf("%c ",c);
        instrucao_aux2 = strtok(instrucao_aux, ":");
        //printf("%s ",instrucao_aux2);
        while (instrucao_aux2 != NULL){
        instrucao_aux2 = strtok(NULL, ":");
        //printf("%s ",instrucao_aux2);
        contador ++;
        }
        //printf("%d\n", contador);
        if (contador == 1 && c != ':'){  // Não possui rótulos

        contador = 0;
        instrucao_aux2 = strtok(instrucao_aux, " ");
        //printf("%sxoie\n", instrucao_aux2);
        while (instrucao_aux2 != NULL){
            if (contador == 0){
                strcpy(aux->inst, instrucao_aux2); // Primeiro adicionar o mnemonico da inst
                instrucao_aux2 = strtok(NULL, " ");
                }
            else if (contador == 1){
                strcpy(aux->operando_1, instrucao_aux2);
                instrucao_aux2 = strtok(NULL, " ");
            }
            else if (contador == 2){
                strcpy(aux->operando_2, instrucao_aux2);
                instrucao_aux2 = strtok(NULL, " ");;
            }
            else if (contador >= 3){
                //printf("Erro sintatico");
                strcpy(aux->trash, instrucao_aux2);
                instrucao_aux2 = strtok(NULL, " ");;
            }
            contador ++;
            //printf("%sxoi\n", instrucao_aux2);
        }
    }

        else if (contador == 2 || (c == ':' && contador == 1)){ // Possui um rotulo (inclui o caso T:\n)
            strcpy(instrucao_aux, vetor_arquivo[i]);
            instrucao_aux2 = strtok(instrucao_aux, ";"); // Retirar comentários
            instrucao_aux3 = strtok(instrucao_aux2, ":");   // Para pegar o rótulo

            contador = 0;
            instrucao_aux2 = strtok(NULL, " ");
        //printf("%sxoie\n", instrucao_aux2);
            while (instrucao_aux2 != NULL){
                if (contador == 0){
                    strcpy(aux->inst, instrucao_aux2); // Primeiro adicionar o mnemonico da inst
                    instrucao_aux2 = strtok(NULL, " ");
                    }
                else if (contador == 1){
                    strcpy(aux->operando_1, instrucao_aux2);
                    instrucao_aux2 = strtok(NULL, " ");
                }
                else if (contador == 2){
                    strcpy(aux->operando_2, instrucao_aux2);
                    instrucao_aux2 = strtok(NULL, " ");;
                }
                else if (contador >= 3){
                    //printf("Erro sintatico");
                    strcpy(aux->trash, instrucao_aux2);
                    instrucao_aux2 = strtok(NULL, " ");;
                }
                contador ++;
                //printf("%sxoi\n", instrucao_aux2);
        }



            instrucao_aux3 = strtok(instrucao_aux3, " ");
            //printf("%s-\n", instrucao_aux3);
            strcpy(aux->rotulo, instrucao_aux3);


        }
        else if (contador >= 3){     //Dois rotulos ou mais
            printf("Erro Sintatico, mais de um rotulo, Linha %d\n",aux->linha);
            strcpy(aux->erro, "+1rot");
        }
    i++;
    //printf("Linha %d, %s - %s - %s - %s - %s\n",aux->linha, aux->rotulo, aux->inst, aux->operando_1, aux->operando_2, aux->trash);
    if (strcmp("\n",aux->inst) == 0){
        //printf("Pulou linha\n");
    }
    aux = aux -> proximo;
}
lista->ultimo = aux;

}


void pre_processamento(){
    instrucao_struct *aux, *aux2, *aux3;
    aux = lista->primeiro;
    char aux_rot[TAM2], aux_op[TAM2], buffer1[TAM2*2], buffer2[TAM2*2];
    int i = 0, contador = 0;
    while(aux != lista->ultimo){
        //printf("Linha %d,%s-%s-%s-%s-%s\n",aux->linha, aux->rotulo, aux->inst, aux->operando_1, aux->operando_2, aux->trash);
        if(strcmp((aux->inst), "EQU")==0){               // Encontrou um EQU
            i = aux->linha - 1;
            strcpy(vetor_arquivo[i]," NULL ");   // Mudando a linha do código do EQU para apagar ele do texto
            strcpy(aux->erro, "LINHA APAGADA");
            strcpy(lista_equ[i+1], aux->rotulo); // Argumento i+1 é a linha do equ

            strcpy(aux_rot, aux->rotulo);
            strcpy(aux_op, aux->operando_1);
            aux2 = aux;
            while(aux != lista->ultimo){
                if(strcmp((aux->inst), "IF")==0){          // Encontrou o IF com valor de EQU
                    if (strcmp(aux_rot,aux->operando_1)==0)
                    {
                        i = aux->linha - 1;
                        strcpy(vetor_arquivo[i]," NULL ");   // Mudando a linha do código do IF para apagar ele do texto
                        strcpy(aux->erro, "LINHA APAGADA");
                        if(strcmp(aux_op,"0")==0){
                            aux3 = aux;
                            contador = 0;
                            while(strcmp(aux->proximo->inst,"\n")== 0){ // Enquanto a prox linha dps do IF for branca
                                    aux = aux->proximo;
                                    contador ++;
                                    }
                                strcpy(vetor_arquivo[i+1+contador]," NULL ");        // Apagar a linha posterior ao IF se EQU 0 (Essa linha não pode ser branca);
                                strcpy(aux->proximo->erro, "LINHA APAGADA");
                                aux = aux3;

                        //printf("eh igual %d\n", aux->linha);
                    }
                    }
                }
                else if(strcmp((aux->inst), "CONST")==0){  // Encontrou um Const com valor de EQU
                    if (strcmp(aux_rot,aux->operando_1)==0){
                        //printf("eh igual %d\n", aux->linha);
                        i = aux->linha - 1;
                        strcpy(buffer1,aux->rotulo);          //Reescrevendo a linha do código agora com o valor certo dps de connst
                        strcpy(buffer2,aux->inst);
                        strcat(buffer1,": ");
                        strcat(buffer1,buffer2);
                        strcat(buffer1, " ");
                        strcpy(buffer2,aux_op);
                        strcat(buffer1,buffer2);
                        //printf("%s\n", buffer1);
                        strcpy(vetor_arquivo[i],buffer1);
                        strcpy(aux->operando_1 ,aux_op);  // Corrigindo o Struct
                    }
                }
            aux = aux->proximo;
            }
        aux = aux2;
        }
        aux = aux->proximo;
    }

strcpy(lista_equ[i+1],"FIM DA LISTA");
}

void apagar_linha(){
    instrucao_struct *aux;
    aux = lista->primeiro;
    while(strcmp(aux->erro,"LINHA APAGADA")==0){   //Caso a primeira linha deva ser apagada
        lista->primeiro = aux->proximo;
        aux = aux->proximo;
    }
    while(aux->proximo != lista->ultimo){
        if(strcmp(aux->proximo->erro,"LINHA APAGADA")==0){
            aux->proximo = aux->proximo->proximo;
        }
        else{
        aux = aux->proximo;
        }
    }
}
void escreve_arquivo(char* nome_arquivo){
    int i = 0;
    char buffer1[TAM2];
    FILE *pont_arq;
    /*strcpy(buffer1, "saida");
    strcpy(buffer2, nome_arquivo);
    strcat(buffer1, "_");
    strcat(buffer1, buffer2);
    */
    pont_arq = fopen(nome_arquivo, "w");
    while (strcmp(vetor_arquivo[i],"FIM DO PROGRAMA")!= 0){
            if(strcmp(vetor_arquivo[i], " NULL ") && strcmp(vetor_arquivo[i], "\n")){                // Se a linha for diferente de NULL, printar ela
                strcpy(buffer1, vetor_arquivo[i]);
                strcat(buffer1, "\n");
                fputs(buffer1, pont_arq);
                }
            else if (strcmp(vetor_arquivo[i], "\n")==0)    //Pular a linha se for /n
                fputs("\n", pont_arq);
            i++;
            }
    fclose(pont_arq);
}


void preenche_struct(){
    instrucao_struct *aux;
    aux = lista->primeiro;
    while(aux != lista->ultimo){
        if (strcmp(aux->erro, " NULL ")==0){
            if(strcmp(aux->inst, "ADD")==0){
                aux->tamanho = 2;
                aux->opcode = 1;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "SUB")==0){
                aux->tamanho = 2;
                aux->opcode = 2;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "MULT")==0 || strcmp(aux->inst, "MUL")==0){
                aux->tamanho = 2;
                aux->opcode = 3;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "DIV")==0){
                aux->tamanho = 2;
                aux->opcode = 4;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "JMP")==0){
                aux->tamanho = 2;
                aux->opcode = 5;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "JMPN")==0){
                aux->tamanho = 2;
                aux->opcode = 6;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "JMPP")==0){
                aux->tamanho = 2;
                aux->opcode = 7;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "JMPZ")==0){
                aux->tamanho = 2;
                aux->opcode = 8;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "COPY")==0){
                aux->tamanho = 3;
                aux->opcode = 9;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "LOAD")==0){
                aux->tamanho = 2;
                aux->opcode = 10;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "STORE")==0){
                aux->tamanho = 2;
                aux->opcode = 11;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "INPUT")==0){
                aux->tamanho = 2;
                aux->opcode = 12;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "OUTPUT")==0){
                aux->tamanho = 2;
                aux->opcode = 13;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "STOP")==0){
                aux->tamanho = 1;
                aux->opcode = 14;
                aux->dado = 2;
            }
            else if(strcmp(aux->inst, "SECAO")==0 && strcmp(aux->operando_1, "TEXTO")==0){
                aux->tamanho = 0;
                aux->opcode = 88;
                aux->dado = 4;
            }
            else if(strcmp(aux->inst, "SECAO")==0 && strcmp(aux->operando_1, "DADOS")==0){
                aux->tamanho = 0;
                aux->opcode = 89;
                aux->dado = 4;
            }
            else if(strcmp(aux->inst, "SPACE")==0){
                aux->tamanho = 1;
                aux->opcode = 0;
                aux->dado = 1;
            }
            else if(strcmp(aux->inst, "CONST")==0){
                aux->tamanho = 1;
                if(aux->operando_1[0] <= 47 || aux->operando_1[0] >= 58){
                    printf("Erro sintatico operando incorreto para const - linha %d\n", aux->linha);
                    aux->opcode = 0;
                }
                else if(aux->operando_1[1]=='X'){
                aux->opcode = (int)strtol(aux->operando_1, NULL, 0);
                }
                else{
                aux->opcode = atoi(aux->operando_1);
                }
                aux->dado = 1;
            }
            else if(strcmp(aux->inst, "BEGIN")==0){
                aux->tamanho = 0;
                aux->opcode = -333;
                aux->dado = 0;
            }
            else if(strcmp(aux->inst, "PUBLIC")==0){
                aux->tamanho = 0;
                aux->opcode = -111;
                aux->dado = 0;
            }
            else if(strcmp(aux->inst, "EXTERN")==0){
                aux->tamanho = 0;
                aux->opcode = -222;
                aux->dado = 0;
            }
            else if(strcmp(aux->inst, "END")==0){
                aux->tamanho = 0;
                aux->opcode = 0;
                aux->dado = 6;
            }
           else if(strcmp(aux->inst, "\n")==0 || strcmp(aux->inst, " NULL ")==0){
                aux->tamanho = 0;
                aux->opcode = 0;
                aux->dado = 5;
           }
            else if(aux->inst[0] == ';'&& strcmp(aux->rotulo, " NULL ")==0){ //linha q comeca com comentÁRIO
                aux->tamanho = 0;
                aux->opcode = 0;
                aux->dado = 5;
            }
            else{
                aux->opcode = 777;
                aux->tamanho = 0;
                //printf("ERRO\n");
            }
        }
        aux = aux->proximo;
    }
}


void primeira_passagem(){
    instrucao_struct *aux;
    tabsim *aux_simb2 = (tabsim*)malloc(sizeof(tabsim)), *aux_simb;
    aux = lista->primeiro;
    int contador_endereco = 0, simb = 1;   //Simb serve pra preencher o primeiro símbolo da tabela
    while(aux != lista->ultimo){
        while (strcmp(aux->inst, "\n")==0){aux = aux->proximo;}   //  Procurar a primeira linha não vazia

        if (aux->opcode==777){                                   // Instrução não definifa
            printf("Erro sintatico instrucao ou diretiva nao definida, linha %d\n", aux->linha);
        }
        //else{
        if (strcmp(aux->rotulo, " NULL ")&& strcmp(aux->erro, "+1rot")){      //Se tem rótulo correto
            //printf("%s\n", aux->rotulo);
            aux_simb = aux_simb2;
            if (simb){                      //Preecher o primeiro símbolo da lista
                simb = 0;
                lista_simbolos->primeira = aux_simb;
            }
            aux_simb2 = (tabsim*)malloc(sizeof(tabsim));
            aux_simb->proxima = aux_simb2;
            aux_simb->endereco = contador_endereco;
            aux_simb->linha = aux->linha;
            strcpy(aux_simb->simbolo,aux->rotulo);
            if(aux->opcode == -222 && aux->dado == 0){   //se for um extern
                aux_simb->tipo = 0;
            }
            else{
                aux_simb->tipo = -1;
            }

        }
        aux->endereco = contador_endereco;
        contador_endereco += aux->tamanho;
        //}




        aux = aux->proximo;
    }
    lista_simbolos->ultima = aux_simb2;
}


void segunda_passagem(){
    instrucao_struct *aux;
    aux = lista->primeiro;
    tabsim *aux_simb,*aux_uso, *aux_uso2 = (tabsim*)malloc(sizeof(tabsim));
    char buffer[TAM2], b,b2, buffer1[TAM2], buffer2[TAM2], buffer3[TAM2];
    //FILE *arq;
    strcpy(buffer1, "saida");
    //strcpy(buffer2, nome_arquivo);
    strcat(buffer1, "_");
    strcat(buffer1, buffer2);
    //arq = fopen(buffer1, "w");

    while (aux->opcode != 88 && aux != lista->ultimo){ // Loop para ler antes da seçao texto (begin extern e public)
       if(aux->dado != 0 && aux->dado != 5){
        if(strcmp(aux->erro, "+1rot") && aux->opcode != 777){
            printf("Erro semantico instrucao na secao errada, Linha %d\n", aux->linha);
            //printf("&d\n",aux->opcode);
        }
        if(aux->opcode==88){
            sec_texto = 1;
        }
        if(aux->opcode==89){
            sec_dados = 1;
        }
        if(aux->dado==6){
            endf = 1;
        }
       }
       else{
        if (aux->opcode == -111 && aux->dado == 0){ // Se for PUBLIC
                aux_simb = lista_simbolos->primeira;
                while(strcmp(aux_simb->simbolo, aux->operando_1) && aux_simb != lista_simbolos->ultima){
                    aux_simb = aux_simb->proxima;
                    }
                if (aux_simb == lista_simbolos->ultima){
                    printf("Erro semantico simbolo nao definido -- Linha %d\n", aux->linha);
                }
                else{
                    aux_simb->tipo = 1;
                }

       }
       if (lig == 0 && aux->opcode != -333 && aux->dado != 5){   //Se a primeira coisa do programa não for begin
            printf("Erro Semantico, linha %d\n",aux->linha);
       }
        else{beginf = 1;}
       if (aux->dado == 0){lig = 1;}
       }
    aux = aux->proximo;
    }

     if (aux == lista->ultimo){
        printf("Erro Semantico, Secao de Texto nao declarada\n");
    }
    else{
    aux = aux-> proximo;   // Saindo do secao texto
    }

    while(aux->opcode != 89 && aux != lista->ultimo){    // Loop para preencher seção texto
        aux_simb = lista_simbolos->primeira;
        if (aux->dado == 2 || aux->dado == 5){
        if (aux->tamanho == 1){//STOP
            //printf("%d ",aux->opcode);
            //fprintf(arq,"%d ",aux->opcode);
            sprintf(buffer3, "%d ", aux->opcode);
            strcat(palavra, buffer3);
            }
        else if (aux->tamanho == 2){
            while (strcmp(aux->operando_1, aux_simb->simbolo) && aux_simb != lista_simbolos->ultima ){    // Enquanto o símbolo não for encontrado na tabela de símbolos
                aux_simb = aux_simb->proxima;
            }
            if(strcmp(aux->operando_1, aux_simb->simbolo)==0){
                if(aux_simb->tipo == 0){
                        aux_uso = aux_uso2;
                        aux_uso2 = (tabsim*)malloc(sizeof(tabsim));
                        aux_uso->proxima = aux_uso2;
                        strcpy(aux_uso->simbolo, aux_simb->simbolo);
                        aux_uso->endereco = aux->endereco + 1;
                        if (uso){
                            tab_uso->primeira = aux_uso;
                            uso = 0;
                        }

                }
                //printf("%d %d ", aux->opcode, aux_simb->endereco);
                //fprintf(arq, "%d %d ", aux->opcode, aux_simb->endereco);
                sprintf(buffer3, "%d %d ", aux->opcode, aux_simb->endereco);
                strcat(palavra, buffer3);
            }
            else{ // Tirar a vírgula
                strcpy(buffer3, aux->operando_1);
                b2 = buffer3[strlen(buffer3)-1];
                buffer3[strlen(buffer3)-1] = '\0';
                aux_simb = lista_simbolos->primeira;
                while (strcmp(buffer3, aux_simb->simbolo) && aux_simb != lista_simbolos->ultima ){    // Enquanto o símbolo não for encontrado na tabela de símbolos
                aux_simb = aux_simb->proxima;
              }
                if(strcmp(buffer3, aux_simb->simbolo)==0){
                        if (strcmp(aux->operando_2, " NULL ")==0 && b2 == ',')
                                printf("Erro sintatico, Linha %d\n", aux->linha);
                        else if (b2 !=','){
                            printf("Erro Semantico simbolo nao definido , Linha %d\n", aux->linha);
                        }
                }
                else{
                        if(strcmp(aux->operando_1," NULL ")){
                    printf("Erro Semantico simbolo nao definido , Linha %d\n", aux->linha);
                        }
                }

            }
        }
        else if (aux->tamanho == 3){
            //printf("%d ", aux->opcode);
            //fprintf(arq, "%d ", aux->opcode);
            sprintf(buffer3, "%d ", aux->opcode);
            strcat(palavra, buffer3);
            strcpy(buffer, aux->operando_1);
            b = buffer[strlen(buffer)-1];
            if (b == ','){
            buffer[strlen(buffer)-1]='\0';
            strcpy(aux->operando_1, buffer);
            while (strcmp(aux->operando_1, aux_simb->simbolo) && aux_simb != lista_simbolos->ultima ){    // Enquanto o símbolo não for encontrado na tabela de símbolos
                aux_simb = aux_simb->proxima;
            }
            if(strcmp(aux->operando_1, aux_simb->simbolo)==0){
                if(aux_simb->tipo == 0){   // Se for EXTERN
                        aux_uso = aux_uso2;
                        aux_uso2 = (tabsim*)malloc(sizeof(tabsim));
                        aux_uso->proxima = aux_uso2;
                        strcpy(aux_uso->simbolo, aux_simb->simbolo);
                        aux_uso->endereco = aux->endereco + 1;
                        if (uso){
                            tab_uso->primeira = aux_uso;
                            uso = 0;
                        }

                }
                //printf("%d ", aux_simb->endereco);
                //fprintf(arq, "%d ", aux_simb->endereco);
                sprintf(buffer3, "%d ", aux_simb->endereco);
                strcat(palavra, buffer3);
            }
            else{
                strcpy(buffer3, aux->operando_1);
                b2 = buffer3[strlen(buffer3)-1];
                if(b2 != ','){
                printf("Erro Semantico simbolo nao definido - Linha %d\n", aux->linha);
                }
            }
            aux_simb = lista_simbolos->primeira;
            while (strcmp(aux->operando_2, aux_simb->simbolo) && aux_simb != lista_simbolos->ultima ){    // Enquanto o símbolo 2 não for encontrado na tabela de símbolos
                aux_simb = aux_simb->proxima;
            }
            if(strcmp(aux->operando_2, aux_simb->simbolo)==0){
                if(aux_simb->tipo == 0){  //Se for EXTERN
                        aux_uso = aux_uso2;
                        aux_uso2 = (tabsim*)malloc(sizeof(tabsim));
                        aux_uso->proxima = aux_uso2;
                        strcpy(aux_uso->simbolo, aux_simb->simbolo);
                        aux_uso->endereco = aux->endereco + 2;
                        if (uso){
                            tab_uso->primeira = aux_uso;
                            uso = 0;
                        }

                }
                //printf("%d ", aux_simb->endereco);
                //fprintf(arq,"%d ", aux_simb->endereco);
                sprintf(buffer3,"%d ", aux_simb->endereco);
                strcat(palavra, buffer3);
            }
            else{
                strcpy(buffer3, aux->operando_2);
                b2 = buffer3[strlen(buffer3)-1];
                if(b2 != ','  || strcmp(aux->trash," NULL ")== 0){
                printf("Erro Semantico simbolo nao definido -- Linha %d\n", aux->linha);
                }

            }}
            else{
                printf("Erro sintatico falta ',' - Linha %d\n", aux->linha);
            }
        }
    }
    else{
        if(strcmp(aux->erro, "+1rot")&& aux->opcode != 777){
            printf("Erro semantico instrucao na secao errada, Linha %d\n", aux->linha);
        }
        if(aux->opcode==89){
            sec_dados = 1;
        }
        if(aux->dado==6){
            endf = 1;
        }
    }
    aux = aux->proximo;
    }
    tab_uso->ultima = aux_uso2;

    if (aux == lista->ultimo && sec_dados == 0){
        printf("Erro Semantico, Secao de dados nao declarada\n");
    }
    else if(aux != lista->ultimo){
    aux = aux-> proximo;   // Saindo do secao dados
    }

    while (aux != lista->ultimo && aux->dado != 6){ // Loop para ler secao de dados
       if(aux->dado != 1 && aux->dado != 5){
        if(strcmp(aux->erro, "+1rot")&& aux->opcode != 777){
            printf("Erro semantico instrucao na secao errada, Linha %d\n", aux->linha);
        }
        if(aux->dado==6){
            endf = 1;
        }
       }
        else if (aux->tamanho == 1){
            //printf("%d ",aux->opcode);
            //fprintf(arq,"%d ",aux->opcode);
            sprintf(buffer3, "%d ",aux->opcode);
            strcat(palavra, buffer3);
            }
    aux = aux->proximo;
    }
    if ((aux->proximo != lista->ultimo && aux->dado==6) || (lig == 0 && aux->dado == 6)){            // Erros provenientes do mal uso do end
        printf("Erro Semantico, linha %d\n", aux->linha);
    }
    if (lig && aux->dado != 6 && endf == 0 && beginf){
        printf("Erro Semantico, falta END\n");
    }
    //fclose(arq);
}


void erro_simbolo(){  //Detecta erros léxicos na declaração dos simbolos e detecta simbolos repetidos

 tabsim *aux, *aux2;
 instrucao_struct *aux3;
 char c,simb[TAM2];
 int i, t;
 aux = lista_simbolos->primeira;
 aux3 = lista->primeiro;
 while (aux != lista_simbolos->ultima){
    aux2 = aux->proxima;
    while (aux2!= lista_simbolos->ultima){  //Rotulos Repetidos
    if (aux != aux2){
        if (strcmp(aux->simbolo, aux2->simbolo)==0){
            printf("Erro semantico - rotulos repetidos, linhas %d e %d\n",aux->linha, aux2->linha);
        }
    }


    aux2 = aux2->proxima;
    }
    //Encontrar erros léxicos
    /*strcpy(simb, aux->simbolo);
    for(i = 0; i <strlen(simb); i++){
        c = simb[i];
            if (i == 0 && c >= 48 && c <= 57) {//Verifica números no primeiro caracter do símbolo
                printf("Erro lexico na declaracao do simbolo, linha %d\n", aux->linha);
            }
            if ((c>=0 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123){
                printf("Erro lexico na declaracao do simbolo; linha %d caracter: %c \n", aux->linha, c);
            }
    }
*/
    t = 0;
    while(strcmp(lista_equ[t],"FIM DA LISTA")){
        if (strcmp(lista_equ[t],aux->simbolo) == 0){
                printf("Erro semantico - rotulos repetidos, linhas %d e %d\n",t, aux->linha);

        }
        t++;
    }

    aux = aux->proxima;
 }
while (aux3 != lista->ultimo){
    if (aux3->dado!=5){
    strcpy(simb, aux3->rotulo);
    for(i = 0; i <strlen(simb); i++){
        c = simb[i];
            if (i == 0 && c >= 48 && c <= 57) {//Verifica números no primeiro caracter do símbolo
                printf("Erro lexico na declaracao do simbolo, linha %d \n", aux3->linha);
            }
            if ((i == strlen(simb)-1)&&((c>=0 && c <= 31) || ((c>=33 && c <= 47)&& c != 44)|| (c >= 60 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123)){
                printf("Erro lexico na declaracao do simbolo; linha %d caracter:%c\n", aux3->linha, c);
            }
            else if ((i != strlen(simb)-1) && ((c>=0 && c <= 31) || ((c>=33 && c <= 47))|| (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123))
            printf("Erro lexico na declaracao do simbolo; linha %d caracter:%c\n", aux3->linha, c);
    }
    strcpy(simb, aux3->inst);
    for(i = 0; i <strlen(simb); i++){
        c = simb[i];
            if (i == 0 && c >= 48 && c <= 57) {//Verifica números no primeiro caracter do símbolo
                printf("Erro lexico - simbolo, linha %d\n", aux3->linha);
            }
             if ((i == strlen(simb)-1)&&((c>=0 && c <= 31) || ((c>=33 && c <= 47)&& c != 44)|| (c >= 60 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123)){
                printf("Erro lexico na declaracao do simbolo; linha %d caracter:%c\n", aux3->linha, c);
            }
            else if ((i != strlen(simb)-1) && ((c>=0 && c <= 31) || ((c>=33 && c <= 47))|| (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123))
                printf("Erro lexico - simbolo; linha %d caracter:%c\n", aux3->linha, c);
    }
    strcpy(simb, aux3->operando_1);
    if (strcmp(aux3->inst, "CONST")){
    for(i = 0; i <strlen(simb); i++){
        c = simb[i];
            if (i == 0 && c >= 48 && c <= 57) {//Verifica números no primeiro caracter do símbolo
                printf("Erro lexico - simbolo, linha %d\n", aux3->linha);
            }
            if ((i == strlen(simb)-1)&&((c>=0 && c <= 31) || ((c>=33 && c <= 47)&& c != 44)|| (c >= 60 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123)){
                printf("Erro lexico - simbolo; linha %d caracter:%c\n", aux3->linha, c);
            }
            else if ((i != strlen(simb)-1) && ((c>=0 && c <= 31) || ((c>=33 && c <= 47))|| (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123))
                printf("Erro lexico - simbolo; linha %d caracter:%c\n", aux3->linha, c);
            }

    }
    strcpy(simb, aux3->operando_2);
    for(i = 0; i <strlen(simb); i++){
        c = simb[i];
            if (i == 0 && c >= 48 && c <= 57) {//Verifica números no primeiro caracter do símbolo
                printf("Erro lexico - simbolo, linha %d\n", aux3->linha);
            }
             if ((i == strlen(simb)-1)&&((c>=0 && c <= 31) || ((c>=33 && c <= 47)&& c != 44)|| (c >= 60 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123)){
                printf("Erro lexico na declaracao do simbolo; linha %d caracter:%c\n", aux3->linha, c);
            }
            else if ((i != strlen(simb)-1) && ((c>=0 && c <= 31) || ((c>=33 && c <= 47))|| (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123))
                printf("Erro lexico - simbolo; linha %d caracter:%c\n", aux3->linha, c);
    }
    strcpy(simb, aux3->trash);
    for(i = 0; i <strlen(simb); i++){
        c = simb[i];
            if (i == 0 && c >= 48 && c <= 57) {//Verifica números no primeiro caracter do símbolo
                printf("Erro lexico - simbolo, linha %d\n", aux3->linha);
            }
            if ((i == strlen(simb)-1)&&((c>=0 && c <= 31) || ((c>=33 && c <= 47)&& c != 44)|| (c >= 60 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123)){
                printf("Erro lexico na declaracao do simbolo; linha %d caracter:%c\n", aux3->linha, c);
            }
            else if ((i != strlen(simb)-1) && ((c>=0 && c <= 31) || ((c>=33 && c <= 47))|| (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || c>= 123))
                printf("Erro lexico - simbolo; linha %d caracter:%c\n", aux3->linha, c);
    }}
    aux3 = aux3->proximo;

}}

void erro_operando(){ //Detecta erro na quantidade de operando e de rótulos com quebra de linha
    instrucao_struct *aux, *aux2;
    aux = lista->primeiro;
    while(aux != lista->ultimo){
        if(strcmp(aux->rotulo, " NULL ") && strcmp(aux->inst, " NULL ") == 0){    //Se possui rótulo sozinho na linha
                aux2 = aux;
                aux = aux->proximo;
            while(strcmp(aux->inst, "\n")==0){aux = aux->proximo;}       // Pulando todas as linhas brancas ate encontrar algo
            if(strcmp(aux->rotulo, " NULL ")){    // Se houver rótulo, quer dizerq saõ dois rotulos juntos L1:\nL2: stop
                printf("Erro sintatico, dois rotulos na mesma linha - Linhas %d e %d\n", aux2->linha, aux->linha);
            }
            else{  //complementar o rótulo l1:\nstop
                aux2->dado = aux->dado;
                aux2->endereco = aux->endereco;
                strcpy(aux2->erro,aux->erro);
                strcpy(aux2->inst ,aux->inst);
                aux2->linha = aux->linha;
                aux2->opcode = aux->opcode;
                strcpy(aux2->operando_1 , aux->operando_1);
                strcpy(aux2->operando_2 , aux->operando_2);
                aux2->tamanho = aux->tamanho;
                strcpy(aux2->trash ,aux->trash);
                aux2->proximo = aux->proximo;
                aux = aux2;
            }
        }


        if(strcmp(aux->trash, " NULL ")){  //Se a instrucao tem 3 operandos, o que nunca acontece aqui
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }
            else if(strcmp(aux->operando_2, " NULL ") && aux->tamanho < 3){  // Se tem 2 operando mas n precisa de tudo isso
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }
        else if(strcmp(aux->operando_1, " NULL ") && aux->opcode == 14){  // Se tem operandos no stop
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }
        else if(strcmp(aux->inst, "SPACE") == 0 && strcmp(aux->operando_1, " NULL ")){  // Se tem operando no space
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }
        else if(strcmp(aux->operando_1, " NULL ") && (aux->opcode == -333 || aux->opcode == -222)){  // Se tem operandos em EXTERN e BEGIN
                if(strcmp(aux->inst, "CONST")) //se nao é const
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }
        else if (aux->tamanho == 3 && strcmp(aux->operando_2, " NULL ") == 0 ){  // Falta operandos no copy
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }
        else if (aux->tamanho == 2 && strcmp(aux->operando_1, " NULL ") == 0 ){  // Falta operandos em instrucoes de tamanho 2
            printf("Erro Sintatico, quantidade errada de operandos, Linha %d\n", aux->linha);
        }

     aux = aux->proximo;
    }
}
void printa_tudo(){
    instrucao_struct *aux;
    tabsim *aux_simb, *aux_uso;

    aux = lista->primeiro;
    aux_simb = lista_simbolos->primeira;
    aux_uso = tab_uso->primeira;
    while(aux != lista->ultimo){
        printf("Linha %d,%d,%d,%s-%s-%s-%s-%s-%s\n",aux->linha,aux->opcode,aux->endereco, aux->rotulo, aux->inst, aux->operando_1, aux->operando_2, aux->trash, aux->erro);
        aux = aux->proximo;
    }
    while(aux_simb != lista_simbolos->ultima){
        printf("%s - %d - %d\n",aux_simb->simbolo, aux_simb->endereco, aux_simb->tipo);
        aux_simb = aux_simb->proxima;
    }
    if (lig){
            if (uso){
             printf("\n\nTab Uso\n 0 0 \n");
            }
    else{
     printf("\n\nTab Uso\n");
     while(aux_uso != tab_uso->ultima){
        printf("%s - %d\n",aux_uso->simbolo, aux_uso->endereco);
        aux_uso = aux_uso->proxima;
    }
    }
    printf("\n\nTab Def\n\n");
    aux_simb = lista_simbolos->primeira;
    while(aux_simb != lista_simbolos->ultima){
        if (aux_simb->tipo == 1)
        printf("%s - %d\n",aux_simb->simbolo, aux_simb->endereco);
        aux_simb = aux_simb->proxima;
    }
}
        printf("\n%s", palavra);
}

void escreve_arquivo2(char* nome_arquivo){
    //int i = 0, t =0;
    //char buffer1[TAM2], buffer2[TAM2];
    tabsim *aux_simb, *aux_uso;
    FILE *pont_arq;

    aux_simb = lista_simbolos->primeira;
    aux_uso = tab_uso->primeira;
    /*strcpy(buffer1, "saida");
    strcpy(buffer2, nome_arquivo);
    strcat(buffer1, "_");
    strcat(buffer1, buffer2);
    t = strlen(buffer1);
    buffer1[t-1] = '\0';
    buffer1[t-2] = '\0';
    buffer1[t-3] = 'o';
    */
    pont_arq = fopen(nome_arquivo, "w");

    if (lig){
            if (uso){
             fprintf(pont_arq,"TABELA USO\n");
            }
    else{
     fprintf(pont_arq,"TABELA USO\n");
     while(aux_uso != tab_uso->ultima){
        fprintf(pont_arq,"%s %d\n",aux_uso->simbolo, aux_uso->endereco);
        aux_uso = aux_uso->proxima;
    }
    }
    fprintf(pont_arq,"\nTABELA DEF\n");
    aux_simb = lista_simbolos->primeira;
    while(aux_simb != lista_simbolos->ultima){
        if (aux_simb->tipo == 1)
        fprintf(pont_arq,"%s %d\n",aux_simb->simbolo, aux_simb->endereco);
        aux_simb = aux_simb->proxima;
    }
    fprintf(pont_arq, "\n");
    }
    fprintf(pont_arq, "%s", palavra);
    fclose(pont_arq);
}
void montador(char* modo, char* nome_arquivo, char* nome_arquivo2){

    le_arquivo(nome_arquivo);


    if(strcmp(modo, "-o")==0){
        escreve_struct();
        pre_processamento();
        apagar_linha();
        preenche_struct();
        primeira_passagem();
        erro_simbolo();
        erro_operando();
        segunda_passagem();
        //printa_tudo();
        escreve_arquivo2(nome_arquivo2);
    }
    else if(strcmp(modo, "-p")==0){

        escreve_struct();
        pre_processamento();
        escreve_arquivo(nome_arquivo2);
        //printa_tudo();
        //printf("%s", palavra);

}
sec_texto = 0;
sec_dados = 0;
lig = 0;
uso = 1;
endf = 0;
beginf = 0;
palavra[0] = '\0';
        }


