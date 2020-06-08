#include <iostream>

using namespace std;
#define TAM 9

bool verificaColuna(int mat[][TAM], int x, int y, int valor){

   for(int i = 0; i < TAM; i ++){
        if(mat[i][y] == valor)
            return false;
   }
   return true;
}

bool verificaLinha(int mat[][TAM], int x, int y, int valor){

   for(int i = 0; i < TAM; i ++){
        if(mat[x][i] == valor)
            return false;
   }
   return true;
}

int main()
{
    int mat[TAM][TAM]={0,0,0,0,0,0,0,0,0
                       0,0,2,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0
                       0,0,0,0,0,0,0,0,0};

    valor = 2
   // printf("retornou", verificaLinha(mat,tam,1,2,valor));





    return 0;
}
