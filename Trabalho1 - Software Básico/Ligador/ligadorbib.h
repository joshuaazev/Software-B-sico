#define TAM1 250
#define TAM2 150

typedef struct tab{
    char simbolo[TAM2];
    int valor;
    struct tab *proxima;
}tab;

typedef struct{
    int tamanho;
    tab *primeira, *ultima;
    } lista_tab;


char vetor1[TAM1][TAM2],vetor2[TAM1][TAM2];
lista_tab tab_uso1[TAM1], tab_uso2[TAM1], tab_def1[TAM1], tab_def2[TAM1];
int lista1[TAM1], lista2[TAM2], tl1, tl2, fator, div2, lista_ligada[TAM2*2], printa = 0; // div2 é onde começa a seção de dados do mod_2


void le_arquivo2(char* n1, char* n2){
    FILE *a1, *a2;
    a1 = fopen(n1, "rt");
    a2 = fopen(n2, "rt");
    int contador_linha = 0;
    char str[TAM2*10];
    if (a1 == NULL){
        printf("Arquivo nao encontrado\n");
    }
    else{
        while(!feof(a1)){
    fgets(str,100, a1);
    strtok(str,"\n");
    strcpy(vetor1[contador_linha], str);
    if(printa)
    printf("%s\n", strupr(vetor1[contador_linha]));
    contador_linha+=1;
        }
        //printf("%d\n",contador_linha);
    }
    contador_linha = 0;
    if (a2 == NULL){
        printf("Arquivo nao encontrado\n");
    }
    else{
        while(!feof(a2)){
    fgets(str,100, a2);
    strtok(str,"\n");
    strcpy(vetor2[contador_linha], str);
    if (printa)
    printf("%s\n", strupr(vetor2[contador_linha]));
    contador_linha+=1;
        }
        //printf("%d\n",contador_linha);
    }
}

void preenche_tab(){


    int i = 0, i2;
    tab *aux = (tab*)malloc(sizeof(tab)), *aux2;
    char str[TAM2], *buffer;

    tab_uso1->primeira = aux;

    while (strcmp(vetor1[i],"TABELA USO")) //Ate encontrar tab uso
        i++;
    i++;
    i2 = i;
    while(strcmp(vetor1[i],"\n")){
        //printf("Nao eh\n");
        strcpy(str, vetor1[i]);
        strtok(str, " ");
        buffer = strtok(NULL, " ");
        strcpy(aux->simbolo, str);
        aux->valor = atoi(buffer);
        aux2 = (tab*)malloc(sizeof(tab));
        aux->proxima = aux2;
        aux = aux->proxima;
        i++;
    }
    tab_uso1->tamanho = i - i2;

    //
    aux = (tab*)malloc(sizeof(tab));
    tab_def1->primeira = aux;

    while (strcmp(vetor1[i],"TABELA DEF")) //Ate encontrar tab uso
        i++;
    i++;
    i2 = i;
    while(strcmp(vetor1[i],"\n")){
        //printf("Nao eh 2\n");
        strcpy(str, vetor1[i]);
        strtok(str, " ");
        buffer = strtok(NULL, " ");
        strcpy(aux->simbolo, str);
        aux->valor = atoi(buffer);
        aux2 = (tab*)malloc(sizeof(tab));
        aux->proxima = aux2;
        aux = aux->proxima;
        i++;
    }
    tab_def1->tamanho = i - i2;
    i++;
    i2 = 0;
    strcpy(str, vetor1[i]);
    //printf("%s\n", str);
    // Separar os numeros do codigo---------------//
    buffer = strtok(str, " ");
    lista1[i2] = atoi(buffer);
    while(buffer != NULL){
            i2++;
            buffer = strtok(NULL, " ");
            lista1[i2] = atoi(buffer);

    }
    tl1 = i2;
   // printf("%d\n", tl1);
    for(i2 = 0; i2 < tl1; i2++){
        //printf("%d ", lista1[i2]);
    }
    //printf("\n");
    //--------------------------------//


// tab 2 //---------------------------------------------------------------------------------------------------------------
    i = 0;
    aux = (tab*)malloc(sizeof(tab));
    tab_uso2->primeira = aux;

    while (strcmp(vetor2[i],"TABELA USO")) //Ate encontrar tab uso
        i++;
    i++;
    i2 = i;
    while(strcmp(vetor2[i],"\n")){
        //printf("Nao eh\n");
        strcpy(str, vetor2[i]);
        strtok(str, " ");
        buffer = strtok(NULL, " ");
        strcpy(aux->simbolo, str);
        //printf("%s buf\n", buffer);
        aux->valor = atoi(buffer);
        //printf("%d kkk\n", aux->valor);
        aux2 = (tab*)malloc(sizeof(tab));
        aux->proxima = aux2;
        aux = aux->proxima;
        i++;
    }
    tab_uso2->tamanho = i - i2;

    //
    aux = (tab*)malloc(sizeof(tab));
    tab_def2->primeira = aux;

    while (strcmp(vetor2[i],"TABELA DEF")) //Ate encontrar tab uso
        i++;
    i++;
    i2 = i;
    while(strcmp(vetor2[i],"\n")){
        //printf("Nao eh 2\n");
        strcpy(str, vetor2[i]);
        strtok(str, " ");
        buffer = strtok(NULL, " ");
        strcpy(aux->simbolo, str);
        aux->valor = atoi(buffer);
        aux2 = (tab*)malloc(sizeof(tab));
        aux->proxima = aux2;
        aux = aux->proxima;
        i++;
    }
    tab_def2->tamanho = i - i2;
    i++;
    i2 = 0;
    strcpy(str, vetor2[i]);
    //printf("%s\n", str);
    // Separar os numeros do codigo---------------//
    buffer = strtok(str, " ");
    lista2[i2] = atoi(buffer);
    while(buffer != NULL){
            i2++;
            buffer = strtok(NULL, " ");
            lista2[i2] = atoi(buffer);

    }
    tl2 = i2;
    //printf("%d\n", tl2);
    for(i2 = 0; i2 < tl2; i2++){
        //printf("%d ", lista2[i2]);
    }
    //printf("\n");
    //--------------------------------//
   // printf("%d %d %d %d", tab_uso1->tamanho,tab_def1->tamanho,tab_uso2->tamanho,tab_def2->tamanho);
   fator = tl1;
}


int checa(int i, int l[TAM1], int t){   //Checa se i está nos t primeirps elementos da lista l
    int x;
    for(x = 0; x < t; x++){
        if (i == l[x])
            return 1;
    }
    return 0;

}
void separamod2(){ //tenta separar a secao de dados da secao de texto do módulo 2
    int list_uso[TAM1], /*list_def[TAM1],*/ tamuso, /*tamdef,*/ x,i, achou = 0, i2;
    tab* aux;
    aux = tab_uso2->primeira;
    //printf("%d\n",tab_uso2->tamanho);
    for(i = 0; i < tab_uso2->tamanho; i++){
            list_uso[i] = aux->valor;
            //printf("%d\n", aux->valor);
            aux = aux->proxima;

    }
    tamuso = tab_uso2->tamanho;
    //printf("\n\n");
    aux = tab_def2->primeira;
   /* for(i = 0; i < tab_def2->tamanho; i++){
            list_def[i] = aux->valor;
            //printf("%d\n", aux->valor);
            aux = aux->proxima;

    }
    tamdef = tab_def2->tamanho;
    */

    for(i = list_uso[tamuso-1]+1; i < tl2; i++){     // i começa dps da ultima ocorrencia da tab_uso
        x = lista2[i];
        //printf("Entrei, x = %d\n", x);
        if (x <= 0 || x >= 15 || x >= tl2 ){
            achou = 1;
            break;
        }
        else if (x == 14){
            achou = 1;
            i++;
            break;
        }
        //cond = 1;

    }
    if (achou){
        div2 = i;
        //printf("i == %d\n",i);
    }
    else
        //printf("Nao achei\n");

    i2 = 0;


    while(1){
        x = lista2[i2];
        if (x<= 0 || x >= 14){
            //printf("wtff x= %d, i2 = %d\n", x, i2);
        }
        else if (x == 9){
            i2 += 3;
            if (i2 == i)
                break;
            else if (i2 == i+1){
                i -= 2;
                break;
            }
            else if(i2 == i+2){
                i-=1;
                break;
            }
        }
        else{
            i2 += 2;
            if (i2 == i)
                break;
            else if (i2 == i+1){
                i -= 1;
                break;
            }
        }
    }
    //printf("i = %d\n",i);
    div2 = i;
}

void liga(){
    int i, i2, x, t;
    tab*aux, *aux2;
    aux = tab_uso1->primeira;
    for (i = tab_uso1->tamanho; i>0; i--){
        aux2 = tab_def2->primeira;
        for (i2 = tab_def2->tamanho; i2>0; i2--){
            if(strcmp(aux->simbolo, aux2->simbolo)==0){
                lista1[aux->valor] = aux2->valor+fator;
                break;
            }
            aux2 = aux2->proxima;
        }
    aux = aux->proxima;
    }
    //printf("Ai credo 1 = %d    2= %d\n", tl1, tl2);

    t = 0;
    for(i2 = 0; i2 < tl1; i2++){
        lista_ligada[t] = lista1[i2];
        //printf("%d ", lista1[i2]);
    t++;
    }

    // --------------------------------- Corrigindo os endereços do mod 2 ------------ //

    i2 = 0;
    //printf("%d\n", div2);

    while(i2 < div2){
        x = lista2[i2];
        if (x<= 0 || x >= 14){
            //printf("wtff x= %d, i2 = %d\n", x, i2);
        }
        else if (x == 9){
            lista2[i2+1]+=fator;
            lista2[i2+2]+=fator;
            i2 += 3;

        }
        else{
            lista2[i2+1]+=fator;
            i2 += 2;
        }
    }

    for(i2 = 0; i2 < tl2; i2++){
        //printf("%d ", lista2[i2]);
    }

     // ---------------------------------- Agora ligando a lista 2 -------------------------------//

    aux = tab_uso2->primeira;
    for (i = tab_uso2->tamanho; i>0; i--){
        aux2 = tab_def1->primeira;
        for (i2 = tab_def1->tamanho; i2>0; i2--){
            if(strcmp(aux->simbolo, aux2->simbolo)==0){
                lista2[aux->valor] = aux2->valor;
                break;
            }
            aux2 = aux2->proxima;
        }
    aux = aux->proxima;
    }
    //printf("Ai credo\n");

    for(i2 = 0; i2 < tl2; i2++){
        lista_ligada[t] = lista2[i2];
        //printf("%d ", lista2[i2]);
    t++;
    }

    if (printa)
    printf("\n\n");

    for(i2 = 0; i2 < tl2+tl1; i2++){
            if (printa)
        printf("%d ", lista_ligada[i2]);
    }

    return;
}

void escreve_arquivolig(){
    char str [100] = "saida_ligador.o";
    int i2;
    FILE* arq;
    arq = fopen(str, "w");
    for(i2 = 0; i2 < tl2+tl1; i2++){
        fprintf(arq,"%d ", lista_ligada[i2]);
    }
    fclose(arq);
}


void ligador(char* n1, char* n2){
    printa = 0; //Se printa = 1, printa as tabelas
    le_arquivo2(n1, n2);
    preenche_tab();
    separamod2();
    liga();
    escreve_arquivolig();

}
