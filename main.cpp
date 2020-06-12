#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <math.h>


using namespace std;
int TAM = 0; // variavel global do tamanho da matriz


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

int **Alocar_vetor_real( int qtd_Cor){
    int *vet_Cor = new int*[qtd_Cor];
    return (vet_Cor);
}

bool verificaColuna(int **mat, int qtd_vert, int x, int y, int cor){

   for(int i = 0; i < qtd_vert; i ++){
        if(mat[i][y] == cor)
            return false;
   }
   return true;
}

bool verificaLinha(int **mat, int qtd_vert, int x, int y, int cor){

   for(int i = 0; i < qtd_vert; i ++){
        if(mat[x][i] == cor)
            return false;
   }
   return true;
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

void coloreMatriz(int **_matrizAdjacencia, int qtd_vert, int *vetCor, int qtd_Cor, int valor_X, int valor_Y, int vet_Vertices){
    vet_Vertices[valor_Y] = vetCor[0];//coluna especificada pelo usuario recebendo primeira cor do vetor
    int go = 1;//variavel do while
    int x = valor_X;
    while(go = 1){
        x += 1;//continuar a partir da linha que usuario mandou
        for(int i = 0; i < qtd_vert; i ++){//percorre a linha inteira
            if(_matrizAdjacencia[x][i] == 1){//houve adjacencia da linha com a coluna i
                if(vet_Vertices[i] != 0)//verifica se a coluna ja tem cor, se sim, descarta essa cor para essa linha
            }
        }








        if(x == qtd_vert)//se chegou no final, volta ao inicio
            x = 0;
        go = 0;//força saida do while
        for(int i = 0; i < qtd_vert; i ++){//testa se o vetor esta cheio, caso contrario faz while de novo
            if(vet_Vertices[i] == 0){
                go = 1;
            }
        }
    }


}

/*void criaMatriz(){

    int **mat;
    mat = Alocar_matriz_real(TAM);

    for (int i = 0; i < TAM; i++)// zerando matriz
        for (int j = 0; j < TAM; j++)
            mat[i][j] = 0;
    system("cls");

    for(int i = 0; i < TAM; i++){       // print matriz
        cout << "\n";
        for(int j = 0; j < TAM; j++)
            cout << " " << mat[i][j];
    }
    pausa();

}*/

void menu(){
    int op;
    do{

        cout << "\n ------------ MENU ------------ \n\n";
        cout << "1 - Informar posicao inicial da matriz: \n";
        cout << "2 - Solucao todos os casos: \n";  // TODO
        cout << "3 - Desenvolvedores: \n";      // TODO
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
            case 1:{
                TAM = 4;
                //criaMatriz();
                break;
                }
            case 2:{
                TAM = 9;
        //      criaMatriz();
                break;
                }
            case 3:{
                TAM = 16;
          //    criaMatriz();
                break;
                }
            case 4:{
                system("CLS");
                break;
                }
            default:{

                }
            }
            system("CLS");

            /*int linha, coluna;
            // matriz teste zerada
            int matriz[TAM][TAM];

            for(int i = 0; i < TAM; i++)
                for(int j = 0; j < TAM; j++)
                    matriz[i][j] = 0;
        */

            break;

        }
        case 2:{

            srand(time(NULL));
            // matriz teste zerada
            int matriz[TAM][TAM];

            for(int i = 0; i < TAM; i++)
                for(int j = 0; j < TAM; j++)
                    matriz[i][j] = 0;
            pausa();
            break;
        }
        case 3:{
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

    int qtd_Cor = 4;
    int qtd_vert = 16;

    int valor_inicial_X = 2;
    int valor_inicial_Y = 3;

    int *vet_Cor;
    int *vet_Vertices;
    int **_matrizAdjacencia; // matriz adjacencia

    vet_Vertices = Alocar_vetor_real(qtd_vert);
    vet_Cor = Alocar_vetor_real(qtd_Cor);
    _matrizAdjacencia = Alocar_matriz_real(qtd_vert);

    for (int j = 0; j < qtd_vert; j++)//zerando vetor de vertices
        vet_Vertices[j] = 0;

    for (int j = 0; j < qtd_Cor; j++)//colocando numero das cores no vetor
        vet_Cor[j] = i+1;

    for (int i = 0; i < qtd_vert; i++)// zerando matriz
        for (int j = 0; j < qtd_vert; j++)
            _matrizAdjacencia[i][j] = 0;

    monta_matriz_adj(_matrizAdjacencia, qtd_vert);
    coloreMatriz(_matrizAdjacencia, qtd_vert, vet_Cor, qtd_Cor, valor_inicial_X, valor_inicial_Y, vet_Vertices);

    // ------------ printa matriz ---------------- //
    int i = 0;
    int j = 0;
    cout<< " --------- Matriz de adjacencia --------- "<<endl;
    for (i=0; i < qtd_vert; i++){
        for (j=0; j < qtd_vert; j++)
            cout << _matrizAdjacencia[i][j] << " ";
        cout << endl;
    }

    return 0;
}
