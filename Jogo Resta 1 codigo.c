#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>

#define N 9

char setasTeclado(){
    char ch = 0;
    printf("\nQual direção voce deseja ir(esc para sair):\n");

    while(ch != 27){
        ch = getch();

        if (ch == 72){
            system("cls");
            printf("\nMovendo para cima...\n\n");
            return ch;
        }
        if (ch == 80){
            system("cls");
            printf("\nMovendo para baixo...\n\n");
            return ch;
        }
        if (ch == 75){
            system("cls");
            printf("\nMovendo para a esquerda...\n\n");
            return ch;
        }
        if (ch == 77){
            system("cls");
            printf("\nMovendo para a direita...\n\n");
            return ch;
        }
    }
    return 0;
}

int posicaoPermitidaInicial(char *mat[N][N], int *linhaInicial, int *colunaInicial){
    int x,y;
    printf("\nDigite a coordenada que voce deseja mover:(Ex: 1 1, 2 5)\n");
    scanf("%d %d", &x, &y);

    x--; //faz x e y -- para que converta a posição digitada pelo usuario para a posição correspondente na matriz
    y--;
    *linhaInicial = x; // atribui a variavel apontada por linha inicial com o valor da posição x e y
    *colunaInicial = y;

    while(1){
        if((x < 0 || x > 7) || (y < 0 || y > 7))  // verifica se o usuario escolheu uma posição valida
        {
            printf("\nPosicao invalida!Tente novamente!\n");
        }
        else if(strcmp(mat[*linhaInicial][*colunaInicial], "\u25CF") == 0)   //Verifica se na coordenada tem bolinha
        {
            return 1;
        }
        else
        {
            printf("\nPosicao invalida!Tente novamente!\n");
        }

        printf("\nDigite a coordenada que voce deseja mover:(Ex: 1 1, 2 5)\n");
        scanf("%d %d", &x,&y);

        x--;
        y--;
        *linhaInicial = x;
        *colunaInicial = y;
    }
}

//Essa funcao vai varrer o vetor para contar a quantidade de bolinhas
int vitoria(char *mat[N][N]){
    int cont = 0;

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (strcmp(mat[i][j], "\u25CF") == 0)
            {
                cont++;
            }
        }
    }

    // Se sobrar apenas uma bolinha, o jogador venceu
    if (cont == 1){
        printf("Você ganhou!!!!!!\n");
        return 1;
    }
    return 0;
}

int movimentoPermitido(char *mat[N][N], int x, int y, char tecla){
    if (x < 0 || x >= 7 || y < 0 || y >= 7) //Não sair do tabuleiro
        return 0;

    if(tecla == 72){
        if((strcmp(mat[x][y], " ") == 0) && (strcmp(mat[x+1][y], "\u25CF") == 0)) //Verifica se no movimento para cima a primeira casa é uma bolinha e a segunda esta vazia.
            return 1;
        else
        {
            return 0;
        }
    }
    else if(tecla == 80){
        if((strcmp(mat[x][y], " ") == 0) && (strcmp(mat[x-1][y], "\u25CF") == 0)) //Verifica se no movimento para baixo a primeira casa é uma bolinha e a segunda esta vazia.
            return 1;
        else
        {
            return 0;
        }
    }
    else if(tecla == 75){
        if((strcmp(mat[x][y], " ") == 0) && (strcmp(mat[x][y+1], "\u25CF") == 0)) //Verifica se no movimento para esquerda a primeira casa é uma bolinha e a segunda esta vazia.
            return 1;
        else
            return 0;

    }
    else if(tecla == 77){
        if((strcmp(mat[x][y], " ") == 0) && (strcmp(mat[x][y-1], "\u25CF") == 0)) //Verifica se no movimento para direita a primeira casa é uma bolinha e a segunda esta vazia.
            return 1;
        else
        {
            return 0;
        }
    }
    return 0;
}

int destinoFinal(char *mat[N][N], int linhaInicial, int colunaInicial, char tecla)
{

    if (tecla == 72 && movimentoPermitido(mat, linhaInicial - 2, colunaInicial, tecla)){
        mat[linhaInicial][colunaInicial] = " "; //troca a posição de partida para vazio
        mat[linhaInicial - 1][colunaInicial] = " "; // troca a posição pulada para vazio
        mat[linhaInicial - 2][colunaInicial] = "\u25CF";//adiciona a bolinha na posição de destino

        // Chama a função de vitória após o movimento
        if (vitoria(mat))
        {
            return 0;  // Jogador ganhou
        }
        return 1;

    }
    else if (tecla == 80 && movimentoPermitido(mat, linhaInicial + 2, colunaInicial, tecla)){
        mat[linhaInicial][colunaInicial] = " ";
        mat[linhaInicial + 1][colunaInicial] = " ";
        mat[linhaInicial + 2][colunaInicial] = "\u25CF";

        if (vitoria(mat))
        {
            return 0;
        }
        return 1;

    }
    else if (tecla == 75 && movimentoPermitido(mat, linhaInicial, colunaInicial - 2, tecla)){
        mat[linhaInicial][colunaInicial] = " ";
        mat[linhaInicial][colunaInicial - 1] = " ";
        mat[linhaInicial][colunaInicial - 2] = "\u25CF";

        if (vitoria(mat))
        {
            return 0;
        }
        return 1;

    }
    else if (tecla == 77 && movimentoPermitido(mat, linhaInicial, colunaInicial + 2, tecla)){
        mat[linhaInicial][colunaInicial] = " ";
        mat[linhaInicial][colunaInicial + 1] = " ";
        mat[linhaInicial][colunaInicial + 2] = "\u25CF";

        if (vitoria(mat))
        {
            return 0;
        }
        return 1;

    }
    else
    {
        printf("Movimento nao permitido! Tente novamente!\n\n");
        return 1;
    }
}

int derrota(char *mat[N][N]){
    for(int i=0; i<7; i++)
    {
        for(int j=0; j<7; j++)
        {
            if(strcmp(mat[i][j], "\u25cf") == 0)
            {
                if(movimentoPermitido(mat, i-2, j, 72)) return 1;
                else if(movimentoPermitido(mat, i+2, j, 80)) return 1;
                else if(movimentoPermitido(mat, i, j-2, 75)) return 1;
                else if(movimentoPermitido(mat, i, j+2, 77)) return 1;
            }
        }
    }
    printf("Voce perdeu!! Tente novamente!\n");
    return 0;
}

void preencherTabuleiro(char *mat[N][N]){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if((i == 2 || i == 3 || i == 4) || (j == 2 || j == 3 || j == 4 )){
                mat[i][j] = "\u25CF";   //Preenche a matriz com a bolinha
            }else{
                mat[i][j] = "*";    //Preenche as extremidades com espaços branco
            }
        }
    }

    mat[3][3] = " "; // Preenche o meio com espaço vazio

}

void mostrarTabuleiro(char *mat[N][N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i < 7 && j < 7){
                if(strcmp(mat[i][j], "*") == 0)
                    printf("  ");
                if(strcmp(mat[i][j], "\u25CF") == 0)
                    printf("\u25CF ");
                if(strcmp(mat[i][j], " ") == 0)
                    printf("  ");
            }

            if(i == N-1 && j < 7)   // Imprime os numeros de auxilio na linha final
                printf("%d ", j+1);
            if(i == N-2 && j < 7) // Imprime a penultima linha de ━━
                printf("━━");


            if(j == 7 && i < 7) // Imprime "┃" na penultima coluna
                printf("┃");
            if(j == 8 && i < 7) // Imprime os numeros de auxilio na coluna final
                printf("%d", i + 1);

        }
        printf("\n"); // \n para quebrar cada linha da matriz
    }
}

int moverPeca(char *mat[N][N]){
    int linhaInicial, colunaInicial;

    while(1)  // chama a função para ler a posição que o jogador deseja selecionar
    {
        posicaoPermitidaInicial(mat,&linhaInicial, &colunaInicial);
        char tecla = setasTeclado();

        if(tecla == 27)
            return 0;

        if(destinoFinal(mat, linhaInicial, colunaInicial, tecla))  // chama a função para realizar o movimento
        {
            return 1;
        }
        else
        {
            break;
        }
    }
    mostrarTabuleiro(mat);
    return 0;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    char *mat[N][N];
    char opc = 's';

    printf("Bem vindo ao jogo Resta 1:\n\n");

    while(opc == 's' || opc == 'S')
    {
        preencherTabuleiro(mat);
        mostrarTabuleiro(mat);

        while(derrota(mat) && moverPeca(mat)){
            mostrarTabuleiro(mat);
        }

            printf("Deseja jogar de novo ?(s ou n)\n\n");
            getchar();
            opc = getchar();
    }

    if(vitoria(mat))
        printf("Parabens você acaba de zerar o jogo!\n\n");
}
