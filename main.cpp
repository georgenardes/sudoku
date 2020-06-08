#include <iostream>

using namespace std;

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

int main()
{
    int TAM = 9;
    int **mat;
    mat = Alocar_matriz_real(TAM);

    for (int i = 0; i < TAM; i++)// zerando matriz
        for (int j = 0; j < TAM; j++)
            mat[i][j] = 0 ;

    mat[1][2] = 2;//colocando um valor para testar as verificações

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





    return 0;
}
