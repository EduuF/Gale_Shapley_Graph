//
// Created by eduar on 05/05/2022.
//
#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){

    /*
     * V = Visitantes
     * N = Linhas do mapa
     * M = Colunas do mapa
     */

    int V, N, M;
    cin >> V;
    cin >> N;
    cin >> M;

    /*
     * Recebe o desenho do mapa em formato de array de Strings
     */

    string mapa_char[N];

    for(int i = 0; i < N; i++){
        cin >> mapa_char[i];
        cout << mapa_char[i] << endl;
    }

    /*
     * Transforma o array de Strings em uma matriz de char
     */

    char mapa[N][M];

    for(int i = 0; i< N; i++){
        for(int j = 0; j < M; j++){
            mapa[i][j] = mapa_char[i][j];
        }
    }

    for(int i = 0; i< N; i++){
        for(int j = 0; j < M; j++){
            cout << i << j << ": ";
            cout << mapa[i][j] << "   ";
        }
        cout << endl;
    }

    /*
     * Capta a preferencia de cada um dos visitantes
     */

    int preferencias_usuarios[V][V];

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            cin >> preferencias_usuarios[i][j];
        }
    }

    /*
     * Calcula a preferencia das bicicletas (Distância para os usuários)
     */

    int preferencias_bike[V][V];

    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){

            /*
             * Transformando o mapa em um grafo do com a Bike X sendo a raiz
             */



        }
    }



    return 0;

}