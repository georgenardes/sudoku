#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

using namespace std;


void printSolucao(int **matrizFinal, int ordem);
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


/**
    Artigo de referência com o código abaixo
    http://ceur-ws.org/Vol-1754/EPoGames_2016_AC_paper_2.pdf
*/
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

bool disponivel(int v, int **_matrizAdjacencia, int qtd_vert, int vertices[], int cor)//ve se a cor é disponivel
{
    for (int i = 0; i < qtd_vert; i++)
        if (_matrizAdjacencia[v][i] == 1 && cor == vertices[i])//ve se tem adjacencia e se  cor estabelecida ja esta no lugar da adjacencia
            return false;
    return true;
}

//colore grafo
bool coloreGrafo(int **_matrizAdjacencia, int qtd_vert, int qtd_cores,int *vertices, int v)
{
    if(v == qtd_vert)                                                  //se a variavel v de interação for igual a quantidade de vertices, termina a recursividade
        return true;

    for (int c = 1; c <= qtd_cores; c++) {                             //for para a quantidade de cores
        if (disponivel(v, _matrizAdjacencia, qtd_vert, vertices, c)) {     //se seguro
            if(vertices[v] == 0)
                vertices[v] = c;                                       //posição do vetor recebe a cor

            if (coloreGrafo(_matrizAdjacencia,qtd_vert, qtd_cores, vertices, v + 1) == true){
                return true;
            }
            vertices[v] = 0;
        }
    }
    return false;
}

//zera vetor
void zera_vetor(int *vertices, int ordem){
    for (int i = 0; i < ordem; i++)
        vertices[i] = 0;
}

bool verificaColoracao(int **_matrizAdjacencia, int qtd_vert, int qtd_cores, int pos)
{
    int *vertices;                                                                         //vetor de cores
    vertices = Alocar_vetor_real(qtd_vert);                                                //aloca vetor
    zera_vetor(vertices, qtd_vert);                                                        //zera o vetor

    vertices[pos] = 1;

    if (coloreGrafo(_matrizAdjacencia, qtd_vert, qtd_cores, vertices, 0) == false) {         //se retornar falso
        printf("Solucao nao existe");                                                   //printa que nao existe solução
        pausa();
        return false;                                                                   //retorna falso
    }

                                                                                        // caso contrario monta solução
    montaMatrizFinal(vertices, qtd_vert);
    return true;
}

void zeraMatriz(int **mat, int ordem){// zerando matriz
    for (int i = 0; i < ordem; i++)
        for (int j = 0; j < ordem; j++)
            mat[i][j] = 0;
}

void montaMatrizFinal(int *color, int qtd_vert){//tranforma o vetor na matriz final
    int ordem = sqrt(qtd_vert);                 //saber o valor da matriz inicial no caso, raiz quadrada
    int contador = 0;                           //contador pro vetor de cores
    int **matrizFinal;
    matrizFinal = Alocar_matriz_real(ordem);    //aloca matriz final
    zeraMatriz(matrizFinal, ordem);             //zera matriz

    for(int i = 0; i < ordem; i ++){            //transcreve valor do vetor de cores pra matriz final
        for(int j = 0; j < ordem; j ++){
            matrizFinal[i][j] = color[contador];
            contador++;
        }
    }
    printSolucao(matrizFinal, ordem);
}

/* printa o sudoku final */
void printSolucao(int **matrizFinal, int ordem)
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

    int tam_quadrante = (int)sqrt(ordem);
    int qtd_pontilhado = 0;

    if(ordem == 4) qtd_pontilhado = 30;
    else if(ordem == 9) qtd_pontilhado = 70;
    else if(ordem == 16) qtd_pontilhado = 130;


    cout << "Matriz final do SUDOKU" << endl << endl;
    for (int i = 0; i < ordem; i++){
        if(i%tam_quadrante == 0 && i > 0){
            textcolor(15,0);
            for(int j = 0; j < qtd_pontilhado; j++)
                cout << "-";
            cout << endl;
        }
        for(int j = 0; j < ordem; j ++){
            if(j%tam_quadrante == 0 && j > 0){
                textcolor(15,0);
                cout << "|";
            }
            textcolor(15,matrizFinal[i][j]-1);
            cout << "  " << matrizFinal[i][j] << "  ";
            textcolor(15,0);
            cout << "\t";
        }
        printf("\n");
    }
    textcolor(15,0);
    pausa();
}

void menu(){
    int op;
    int **matrizAdjacencia; // matriz adjacencia
    do{

        cout << "\n ------------ MENU ------------ \n\n";
        cout << "1 - Informar o tamanho do sudoku: \n";
        cout << "2 - Desenvolvedores: \n";
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
                int opcao = 0;
                int qtd_vert = 0;
                int ordem = 0;
                int pos = 0;

                system("CLS");
                cout << "Selecione o tamanho da matriz desejada: " << endl;
                cout << "1 - Matriz 4x4." << endl;
                cout << "2 - Matriz 9x9." << endl;
                cout << "3 - Matriz 16x16." << endl;
                cout << "4 - Voltar;" << endl;
                cin >> opcao;
                system("CLS");

                cout << "DIGITE O NUMERO DO VERTICE INICIAL: " << endl;
                cin >> pos;

                if(opcao == 1){
                    qtd_vert = 4*4; ordem = 4;
                }else if(opcao == 2){
                    qtd_vert = 9*9; ordem = 9;
                }else if(opcao == 3){
                    qtd_vert = 16*16; ordem = 16;
                }else if(opcao == 4){
                    system("CLS");
                    break;
                }

                matrizAdjacencia = Alocar_matriz_real(qtd_vert);           //aloca matriz
                zeraMatriz(matrizAdjacencia, qtd_vert);                    //zera matriz
                monta_matriz_adj(matrizAdjacencia, qtd_vert);              //monta matriz adjacencia
                verificaColoracao(matrizAdjacencia, qtd_vert, ordem, pos);     //começa colorir

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
