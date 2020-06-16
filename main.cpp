#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

using namespace std;


void printSolucao(int **matrizFinal, int maximo);
void montaMatrizFinal(int *color, int qtd_vert);

typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,   /* nome das cores */
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;

static int __BACKGROUND = 1;/*BLACK*//*pode ser o numero ou o nome da cor*/
static int __FOREGROUND = LIGHTGRAY;

void textcolor (int letras, int fundo){/*para mudar a cor de fundo mude o background*/
    __FOREGROUND = letras;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letras + (__BACKGROUND << 4));
}

void pausa(){
    cout << "\n\n\n *** ";
    system("PAUSE");
}

int **Alocar_matriz_real (int qtdVert){
    int **matriz = new int*[qtdVert];

    for (int i = 0; i < qtdVert; ++i)
        matriz[i] = new int[qtdVert];

    return (matriz);
}

int *Alocar_vetor_real( int qtd_vert){
    int *color = new int [qtd_vert];
    return (color);
}

void monta_matriz_adj(int **_matrizAdjacencia, int qtd_vert){
    // quantidade de linhas/colunas do sudoku
    int _ordem = sqrt(qtd_vert);

    // quantidade de linhas de um quadrante
    int _ordem0 = sqrt(_ordem);

    for (int i = 0; i < qtd_vert; i++){
        for (int j = 0; j < qtd_vert; j++){
            if (j >= (i / _ordem) * _ordem && j < (i / _ordem) * _ordem + _ordem)
                _matrizAdjacencia[i][j] = 1;
            else if (j % _ordem == i % _ordem)
                _matrizAdjacencia[i][j] = 1;
            else
                _matrizAdjacencia[i][j] = 0;
        }
    }

    for (int i = 0; i < qtd_vert; i++){
        for (int f = 0; f < _ordem0; f++){
            for (int k = 0; k < _ordem0; k++){
                if ((i / _ordem) % _ordem0 == 0)
                    for (int j = 0; j < _ordem0; j++){
                        _matrizAdjacencia[i + _ordem * f][(i / _ordem0) * _ordem0 + j + _ordem * k] = 1;
                    }
            }
        }
    }
}

bool isSafe(int v, int **_matrizAdjacencia, int qtd_vert, int color[], int c)//ve se é seguro
{
    for (int i = 0; i < qtd_vert; i++)
        if (_matrizAdjacencia[v][i] == 1 && c == color[i])//ve se tem adjacencia e se  cor estabelecida ja esta no lugar da adjacencia
            return false;
    return true;
}

bool graphColoringUtil(int **_matrizAdjacencia, int qtd_vert, int m,int *color, int v, int pos_i)
{
    if(v == pos_i){
        color[v] = 1;
        v = 0;
    }
    if(v == qtd_vert)//se a variavel v de interação for igual a quantidade de vertices, termina a recursividade
        return true;

    for (int c = 1; c <= m; c++) {//for para a quantidade de cores
        if (isSafe(v, _matrizAdjacencia, qtd_vert, color, c)) {//se seguro
            color[v] = c;//posição do vetor recebe a cor
            if((v + 1) != pos_i){
                if (graphColoringUtil(_matrizAdjacencia,qtd_vert, m, color, v + 1, pos_i) == true){
                    return true;
                }
                color[v] = 0;
            }else{
                if (graphColoringUtil(_matrizAdjacencia,qtd_vert, m, color, v + 2, pos_i) == true){
                    return true;
                }
                color[v] = 0;
            }
        }
    }
    return false;
}

//zera vetor
void zera_vetor(int *vet, int maximo){
    for (int i = 0; i < maximo; i++)
        vet[i] = 0;
}

//colore grafo
bool graphColoring(int **_matrizAdjacencia, int qtd_vert, int m, int pos, int pos_i)
{
    int *color;//vetor de cores
    color = Alocar_vetor_real(qtd_vert);//aloca vetor
    zera_vetor(color, qtd_vert);//zera o vetor

    // chama função graphColoringUtil
    if (graphColoringUtil(_matrizAdjacencia, qtd_vert, m, color, pos, pos_i) == false) {//se retornar falso
        printf("Solucao nao existe");//printa que nao existe solução
        return false;//retorna falso
    }

    // caso contrario monta solução
    montaMatrizFinal(color, qtd_vert);
    return true;
}

void zeraMatriz(int **mat, int maximo){// zerando matriz
    for (int i = 0; i < maximo; i++)
        for (int j = 0; j < maximo; j++)
            mat[i][j] = 0;
}

void montaMatrizFinal(int *color, int qtd_vert){//tranforma o vetor na matriz final
    int i = 0, j = 0;
    int maximo = sqrt(qtd_vert);//saber o valor da matriz inicial no caso, raiz quadrada
    int contador = 0;//contador pro vetor de cores
    int **matrizFinal;
    matrizFinal = Alocar_matriz_real(maximo);//aloca matriz final
    zeraMatriz(matrizFinal, maximo);//zera matriz

    for(i = 0; i < maximo; i ++){//trnscreve valor do vetor de cores pra matriz final
        for(j = 0; j < maximo; j ++){
            matrizFinal[i][j] = color[contador];
            contador++;
        }
    }
    printSolucao(matrizFinal, maximo);
}

/* printa o sudoku final */
void printSolucao(int **matrizFinal, int maximo)
{
    //numero:cor
    //1 : preto
    //2 : azul
    //3 : verde
    //4 : azul esverdeado
    //5 : vermelho
    //6 : roxinho
    //7 : marrom
    //8 : cinza claro
    //9 : cinza escuro
    //10 : azul claro
    //11: verde luz
    //12: azul esverdeado claro
    //13; vermelho claro
    //14: roxinho claro
    //15: amarelo
    //16: branco

    printf("Matriz final do SUDOKU \n \n");
    for (int i = 0; i < maximo; i++){
        for(int j = 0; j < maximo; j ++){
            if(matrizFinal[i][j] == 1)
                textcolor(15,0);
            else if(matrizFinal[i][j] == 2)
                textcolor(15,1);
            else if(matrizFinal[i][j] == 3)
                textcolor(15,2);
            else if(matrizFinal[i][j] == 4)
                textcolor(15,3);
            else if(matrizFinal[i][j] == 5)
                textcolor(15,4);
            else if(matrizFinal[i][j] == 6)
                textcolor(15,5);
            else if(matrizFinal[i][j] == 7)
                textcolor(15,6);
            else if(matrizFinal[i][j] == 8)
                textcolor(15,7);
            else if(matrizFinal[i][j] == 9)
                textcolor(15,8);
            else if(matrizFinal[i][j] == 10)
                textcolor(15,9);
            else if(matrizFinal[i][j] == 11)
                textcolor(15,10);
            else if(matrizFinal[i][j] == 12)
                textcolor(15,11);
            else if(matrizFinal[i][j] == 13)
                textcolor(15,12);
            else if(matrizFinal[i][j] == 14)
                textcolor(15,13);
            else if(matrizFinal[i][j] == 15)
                textcolor(15,14);
            else
                textcolor(0,15);

            printf(" %d  ", matrizFinal[i][j]);
        }
        printf("\n");
    }
    textcolor(15,0);
    pausa();
}

void menu(){
    int op;
    int pos;
    int **_matrizAdjacencia; // matriz adjacencia
    do{

        cout << "\n ------------ MENU ------------ \n\n";
        cout << "1 - Informar o tamanho do sudoku: \n";
        cout << "2 - Desenvolvedores: \n";      // TODO
        cout << "0 - Finalizar o programa \n\n";
        cout << "Informe a opcao desejada: ";

        cin >> op;
        system("CLS");

		switch (op) {

        case 0:{
            cout << "\nPrograma finalizado!\n\n\n";
            pausa();
            break;
        }
        case 1:{
            int opcao;
            system("CLS");
            cout << "Selecione o tamanho da matriz desejada: " << endl;
            cout << "1 - Matriz 4x4." << endl;
            cout << "2 - Matriz 9x9." << endl;
            cout << "3 - Matriz 16x16." << endl;
            cout << "4 - Voltar;" << endl;
            cin >> opcao;
            switch(opcao){
            case 1:{//se for 4x4
                system("CLS");
                cout << "DIGITE A POSICAO INICIAL;" << endl;
                cin >> pos;
                int qtd_vert = 4*4, m = 4;

                _matrizAdjacencia = Alocar_matriz_real(qtd_vert);//aloca matriz

                zeraMatriz(_matrizAdjacencia, qtd_vert);//zera matriz

                monta_matriz_adj(_matrizAdjacencia, qtd_vert);//monta matriz adjacencia
                graphColoring(_matrizAdjacencia, qtd_vert, m, pos, pos);//começa colorir
                break;
                }
            case 2:{
                system("CLS");
                cout << "DIGITE A POSICAO INICIAL;" << endl;
                cin >> pos;
                int qtd_vert = 9*9, m = 9;
                _matrizAdjacencia = Alocar_matriz_real(qtd_vert);//aloca matriz

                zeraMatriz(_matrizAdjacencia, qtd_vert);//zera matriz

                monta_matriz_adj(_matrizAdjacencia, qtd_vert);//monta matriz adjacencia
                graphColoring(_matrizAdjacencia, qtd_vert, m, pos, pos);//começa colorir
                break;
                }
            case 3:{
                system("CLS");
                cout << "DIGITE A POSICAO INICIAL;" << endl;
                cin >> pos;
                int qtd_vert = 16*16, m = 16;
                _matrizAdjacencia = Alocar_matriz_real(qtd_vert);//aloca matriz

                zeraMatriz(_matrizAdjacencia, qtd_vert);//zera matriz

                monta_matriz_adj(_matrizAdjacencia, qtd_vert);//monta matriz adjacencia
                graphColoring(_matrizAdjacencia, qtd_vert, m, pos, pos);//começa colorir
                break;
                }
            case 4:{
                system("CLS");
                menu();
                break;
                }
            default:{

                }
            }
            system("CLS");
            break;

        }
        case 2:{
            system("CLS");
            cout << "-------Desenvolvedores------\n" <<endl;
            cout << "Diogo Marchi" << endl;
            cout << "George de Borba" << endl;
            cout << "Leonardo Grando";
            pausa();
            break;
        }
        default: {

			}
        }
		system("CLS");

	}while(op!=0);

}


int main()
{
    menu();
    return 0;
}
