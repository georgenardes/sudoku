#include <iostream>
#include <math.h>

using namespace std;

bool **Alocar_matriz_real (int qtdVert){
    bool** matriz = new bool*[qtdVert];

    for (int i = 0; i < qtdVert; ++i)
        matriz[i] = new bool[qtdVert];

    return (matriz);
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


void monta_matriz_adj(bool **_matrizAdjacencia, int qtd_vert){
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


int main()
{
    int qtd_vert = 16;

    bool **_matrizAdjacencia; // matriz adjacencia

    _matrizAdjacencia = Alocar_matriz_real(qtd_vert);

    for (int i = 0; i < qtd_vert; i++)// zerando matriz
        for (int j = 0; j < qtd_vert; j++)
            _matrizAdjacencia[i][j] = 0;

    monta_matriz_adj(_matrizAdjacencia, qtd_vert);

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
