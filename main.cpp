//
// Created by eduar on 05/05/2022.
//
#include <iostream>
#include <list>
#include <queue>
using namespace std;

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

    int ranking_usuarios[V][V];
    for(int i = 0; i < V; i++){

        for(int j = 0; j < V; j++){
            int maior = 0, indice;

            for(int k = 0; k < V; k++){
                if(preferencias_usuarios[i][k] > maior){
                    maior = preferencias_usuarios[i][k];
                    indice = k;
                }
            }
            ranking_usuarios[i][j] = indice;
            preferencias_usuarios[i][indice] = -1;
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
    int distancia_bikes[V][V];

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
                    distancia_bikes[i][j] = fila.front().altura;
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

    // Calcula o ranking das Bikes (Usuário mais perto)
    int ranking_bikes[V][V];
    for(int i=0; i < V; i++){ // Para cada bike

        for(int j = 0; j < V; j++){
            int menor = N*M+1, id_menor;

            for(int k = 0; k < V; k++){ // Acha o menor na atual lista de distancia

                if(distancia_bikes[i][k] < menor){
                    menor = distancia_bikes[i][k];
                    id_menor = k;
                }
            }
            ranking_bikes[i][j] = id_menor;
            distancia_bikes[i][id_menor] = ((N*M)+1);
        }
    }


    // GALE-SHAPLEY

    /*
     *  0 = nunca propôs
     * -1 = propôs e recusou
     *  1 = propôs e aceitou
    */

    int proposicoes[V][V];
    bool usuario_sem_bike = true;
    int u = 0; // usuario sem bike

    // SETANDO AS ALOCACOES COMO 0
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++) {
            proposicoes[i][j] = 0;
        }
    }

    // ALG GALE-SHAPLEY //

    while(usuario_sem_bike){
        usuario_sem_bike = false;

        // ENCONTRA A BIKE (NUNCA PROPOSTA) PREFERIDA DO USUARIO
        int melhor_bike;
        for(int i = 0; i < V; i++){
            if(proposicoes[u][ranking_usuarios[u][i]] == 0) {
                melhor_bike = ranking_usuarios[u][i];
                break;
            }
        }

        // VERIFICA SE A BIKE JA FOI ALOCADA A ALGUEM
        bool bike_unmatched = true;
        int atual_match_da_bike;
        for(int j = 0; j< V; j++){
            if(proposicoes[j][melhor_bike] == 1){
                bike_unmatched = false;
                atual_match_da_bike = j;
            }

        }

        //VERIFICA PREFERENCIA DA BIKE
        bool prefere_antigo = false;
        if(!bike_unmatched){
            for(int i = 0; i < V; i++){
                // Se o antigo vier primerio
                if(ranking_bikes[melhor_bike][i] == atual_match_da_bike){
                    prefere_antigo = true;
                    break;
                }
                // Se o novo vier primeiro
                if(ranking_bikes[melhor_bike][i] == u){
                    break;
                }
            }
        }

        if(bike_unmatched){
            proposicoes[u][melhor_bike] = 1;
        } else if(!prefere_antigo){
            proposicoes[u][melhor_bike] = 1;
            proposicoes[atual_match_da_bike][melhor_bike] = -1;
        } else {
            proposicoes[u][melhor_bike] = -1;
        }

        // VERIFICA SE AINDA EXISTE USUARIO SEM BIKE
        for(int i = 0; i < V; i++){
            bool foi_aceito = false;

            for(int j = 0; j < V; j++){
                if(proposicoes[i][j] == 1) {
                    foi_aceito = true;
                    break;
                }
            }

            if(!foi_aceito){
                usuario_sem_bike = true;
                u = i;
                break;
            }
        }
    }

    for(int i=0; i < V; i++){
        cout << char(i+97) << " ";
        for(int j = 0; j < V; j++){
            if(proposicoes[i][j] == 1)
                cout << j;
        }
        cout << endl;
    }

    cout << endl;



    return 0;

}
