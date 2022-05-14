//
// Created by eduar on 05/05/2022.
//
#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Grafo{
public:
    int numero_de_vertices;

    list<int> *l;

    Grafo(int V){
        this->numero_de_vertices = V;
        l = new list<int>[V];
    }

    void adiciona_vertice(int x, int y){
        l[x].push_back(y);
    }

    void mostra_lista_adjacencia(){
        for(int i=0; i<numero_de_vertices; i++){
            cout << "Vertice " << i << "->";
            for(int nbr:l[i]){
                cout << nbr <<",";
            }
            cout << endl;
        }
    }
};

class Node{
public:
    int vertice, altura;

    Node(int _v,int _a){
        this->vertice = _v;
        this->altura = _a;
    }
};

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
    }

    /*
     * Transforma o array de Strings em uma matriz de int
     * 48~57 = 0~9
     * 42 = *
     * 45 = -
     * 97~122 = a~z
     */

    int mapa[N][M];

    for(int i = 0; i< N; i++){
        for(int j = 0; j < M; j++){
            mapa[i][j] = int(mapa_char[i][j]);
        }
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
     * Monta o grafo a partir do mapa
     */

    Grafo g(N*M);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            // Se eu estiver em um obstáculo, passa para a próxima interação
            if(mapa[i][j] == 45){
                continue;
            }
            //Verifica casa de cima
            if((i-1) >= 0 && mapa[i-1][j] != 45){
                g.adiciona_vertice((i*M)+j, ((i-1)*M)+j);
            }

            //Verifica casa de baixo
            if((i+1) < N && mapa[i+1][j] != 45){
                g.adiciona_vertice((i*M)+j, ((i+1)*M)+j);
            }

            //Verifica casa da esquerda
            if((j-1) >= 0 && mapa[i][j-1] != 45){
                g.adiciona_vertice((i*M)+j, (i*M)+(j-1));
            }

            //Verifica casa da direita
            if((j+1) < M && mapa[i][j+1] != 45){
                g.adiciona_vertice((i*M)+j, (i*M)+(j+1));
            }
        }
    }

    // Pega a posicao de cada bicicleta

    int posicao_bikes[V];

    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(mapa[i][j] >= 48 && mapa[i][j] <= 57){
                posicao_bikes[mapa[i][j] - 48] = i*M+j;
            }
        }
    }

    // Pega a posicao de cada usuario

    int posicao_usuarios[V];

    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(mapa[i][j] >= 97 && mapa[i][j] <= 122){
                posicao_usuarios[mapa[i][j] - 97] = i*M+j;
            }
        }
    }

                    /*                */
                    /*  BFS NO GRAFO  */
                    /*               */

    // Encontra o menor caminho entre as bikes e os usuário (Lista de preferencias das Bikes)
    int preferencias_bikes[V][V];

    // Para cada uma das bikes 'i'
    for(int i = 0; i < V; i++){

        // Define todos os vertices como não visitados
        int visitado[N*M];
        for(int j = 0; j<N*M; j++){
            visitado[j] = 0;
        }

        // Cria uma fila com a posicao inicial da bike como 1º item
        queue<Node> fila;
        int posicao_inicial = posicao_bikes[i];
        fila.push(Node(posicao_inicial, 0));
        visitado[posicao_inicial] = 1;

        // Enquanto a fila não estiver vazia continua procurando
        while(!fila.empty()){

            // Checa se o primeiro elemento da fila equivale a algum usuario 'j'
            for(int j = 0; j < V; j++){
                if(fila.front().vertice == posicao_usuarios[j]){
                    preferencias_bikes[i][j] = fila.front().altura;
                    // Continua procurando o caminho para os outros usuários
                    break;
                }
            }

            // Adiciona os vizinhos do nó na fila
            for(int nbr:g.l[fila.front().vertice]){
                // Se ainda não tiver sido visitado
                if(visitado[nbr] == 0){
                    fila.push(Node(nbr,fila.front().altura+1)); // Aumenta a altura do vértice em 1
                    visitado[nbr] = 1; // Marca como visitado
                }
            }
            fila.pop();
        }
    }


    // preferencias_bikes
    // preferencias_usuarios  <<< METE GALESHAPLEY
    return 0;

}