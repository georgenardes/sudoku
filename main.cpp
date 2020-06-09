#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;
int TAM = 0; // variavel global do tamanho da matriz

void pausa(){
    cout << "\n\n\n *** ";
    system("PAUSE");
}
int **Alocar_matriz_real (int qtdVert){
    int** matriz = new int*[qtdVert];

    for (int i = 0; i < qtdVert; ++i)
        matriz[i] = new int[qtdVert];

    return (matriz);
}

bool verificaColuna(int **mat, int TAM, int x, int y, int cor){

   for(int i = 0; i < TAM; i ++){
        if(mat[i][y] == cor)
            return false;
   }
   return true;
}

bool verificaLinha(int **mat, int TAM, int x, int y, int cor){

   for(int i = 0; i < TAM; i ++){
        if(mat[x][i] == cor)
            return false;
   }
   return true;
}

void criaMatriz(){

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

}

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
        case 1:
            TAM = 4;
            criaMatriz();
            break;
        case 2:
            TAM = 9;
            criaMatriz();

            break;
        case 3:
            TAM = 16;
            criaMatriz();

        case 4:
            system("CLS");


            break;
        default: {

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
			case 3:
			    cout << "-------Desenvolvedores------\n" <<endl;
			    cout << "Diogo Marchi" << endl;
			    cout << "George de Borba" << endl;
			    cout << "Leonardo Grando";
			    pausa();
                break;

        default: {

			}
        }
		system("CLS");

	}while(op!=0);

}

int main()
{
    menu();
    // se quiserem testar, so comenta o menu e descomenta o resto do main
    /*int TAM = 9;
    int **mat;
    mat = Alocar_matriz_real(TAM);

    for (int i = 0; i < TAM; i++)// zerando matriz
        for (int j = 0; j < TAM; j++)
            mat[i][j] = 0 ;

    //mat[1][2] = 2;//colocando um valor para testar as verificações

    int cor = 2;
    if(verificaColuna(mat,TAM,0,2,cor)==true)
        cout << "pode inserir neste lugar" << endl;
    else

        cout << "valor ja existente" << endl ;

    int cor2 = 2;
    if(verificaLinha(mat,TAM,3,0,cor2)==true)
        cout << "pode inserir neste lugar" << endl;
    else
        cout << "valor ja existente" << endl;


*/

    return 0;
}
