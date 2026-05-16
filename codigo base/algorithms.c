#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

// Algoritmo de Dijkstra usando matriz de adjacência
double dijkstra(int **matriz, int num_nos, int origem) {
    double custo = 0;
    //Algoritimo guloso

    // Comecar o array de distancia (infinito, origem no 0)
    int *distancia = (int *)malloc(num_nos * sizeof(int));
    for (int i = 0; i < num_nos; i++) {
        distancia[i] = INF;
    }
    distancia[origem] = 0;
    
    // Comecar array de visitados (falso)
    bool *visitado = (bool *)malloc(num_nos * sizeof(bool));
    for (int i = 0; i < num_nos; i++) {
        visitado[i] = false;
    }

    //LOOP 
    // Algoritimo guloso 
    for (int i = 0; i < num_nos; i++) {
        // menor distancia Ok / proximo vizinho de menor valor
        //Buscar no array de distancias qual e o nó NAO VISITADO que tem o menor valor atualmente
        int min_dist = INF;
        int u = -1;
        for (int j = 0; j < num_nos; j++) {
            custo++;
            if (!visitado[j] && distancia[j] < min_dist) {
                min_dist = distancia[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        
        //Marcar esse nó escolhido como VISITADO no array de visitados
        visitado[u] = true;
        custo++;

        // Vizualiza seus vizinhos / soma dos valores
        //Percorrer a linha da matriz correspondente a esse nó para achar os vizinhos
        // Para cada viizinho
        for (int v = 0; v < num_nos; v++) {
            custo++;
            if (matriz[u][v] != 0 && !visitado[v]) {
                // Se distancia atual + peso ate vizinho < distancia dovizinho salva
                // Atualiza a distância no array de distancias
                if (distancia[u] != INF && distancia[u] + matriz[u][v] < distancia[v]) {
                    distancia[v] = distancia[u] + matriz[u][v];
                    custo++;
                }
            }
        }
    }
    
    free(distancia);
    free(visitado);

    /* Esta retorno também é obrigatório e não deve ser retirado*/  
    return custo;
}

// Algoritmo de Duan usando matriz de adjacência
double duan(int **matriz, int num_nos, int origem) {
    double custo = 0;

    //Alocação de memória
    int *dist = (int *)malloc(num_nos * sizeof(int)); //dist[i] = menor distância conhecida a partir das fontes atuais até o nó i.
    bool *S = (bool *)malloc(num_nos * sizeof(bool)); //Conjunto de fontes.
    bool *pivots = (bool *)malloc(num_nos * sizeof(bool)); //Marca os pivôs (Algorithm 1 do pdf).
    int *dist_final = (int *)malloc(num_nos * sizeof(int));
    bool *in_queue = (bool *)malloc(num_nos * sizeof(bool)); //controle auxiliar da fila
    // Fila superdimensionada para garantir que não haverá overflow por múltiplos relaxamentos
    int max_fila = num_nos * num_nos * 2; 
    int *fila = (int *)malloc(max_fila * sizeof(int));

    // inicialização do histórico global de distâncias
    for (int i = 0; i < num_nos; i++) { //Para todos os nós do grafo
        custo++; // Operação de inicialização por nó
        dist_final[i] = INF; //Nenhuma distância é conhecida.
        S[i] = false; //Nenhum nó é fonte.
    }

    dist_final[origem] = 0;
    S[origem] = true; //Inicia-se com uma única fonte.

    int B = 55; //Limita a distância máxima de exploração em cada fase do algoritmo, controlando quais caminhos devem ser considerados e garantindo eficiência.
    int L = 3; //Número de níveis da recursão (controla profundidade da divisão).

    // =============================
    // SIMULAÇÃO DO BMSSP do pdf
    // =============================
    for (int l = 0; l <= L; l++) { //Isso é quivalente à "BMSSP(l) chama BMSSP(l-1)" do pdf.
        custo++; // Controle do loop de níveis
        // =============================
        // BASE CASE (Algorithm 2 do pdf)
        // =============================
        int front = 0, rear = 0; //Inicializa fila.

        for (int i = 0; i < num_nos; i++) { //Inicializa distâncias e insere as fontes na fila
            in_queue[i] = false; // Garante limpeza para a fase atual
            custo++; // Iteração para preparar a fila nesta fase
            dist[i] = dist_final[i];
            if (S[i] && dist[i] != INF) {
                //entra na fila.
                fila[rear] = i;
                rear = (rear + 1) % max_fila;
                in_queue[i] = true; /*Insere o vértice i na fila inicial (é uma fonte ativa nesta fase). 
                                    Marca in_queue[i] = true para indicar que i já está na fila e evitar duplicatas*/
                custo++; // Operação de inserção na fila
            }
        }

        // Execução do Base Case (Busca em Largura / Relaxamento)
        while (front != rear) { //Enquanto houver nós na fila.
            //Remove nó da fila.
            custo++; // Verificação e retirada da fila
            int u = fila[front]; 
            front = (front + 1) % max_fila; 
            in_queue[u] = false; //Marca in_queue[u] = false para permitir que ele volte à fila futuramente, se necessário

            for (int v = 0; v < num_nos; v++) { //Percorre todos os vizinhos.
                custo++; // Varredura de vizinhos na matriz de adjacência
                if (matriz[u][v] != 0) { //Se existir aresta u → v. "ou matriz[u][v] > 0 na versão antiga"
                    int w = matriz[u][v]; //Peso da aresta.

                    // Relaxamento considerando o limite B acumulado
                    if (dist[u] != INF && dist[u] + w < dist[v] && dist[u] + w <= B) { //Se a ((distância atual até o nó u + peso da aresta u->v) for < (custo de ir da fonte até v passando por u)) && (esse caminho não ultrapassar o limite B).
                        //Atualiza distância e coloca na fila.
                        dist[v] = dist[u] + w;
                        custo++;
                        if (!in_queue[v]) { // Só insere na fila se já não estiver nela
                            int next = (rear + 1) % max_fila;
                            if (next != front) { // evita sobrescrever
                                    fila[rear] = v;
                                    rear = next;
                                    in_queue[v] = true; /*Insere v na fila porque sua distância foi melhorada (precisa ser reprocessado)
                                                        Só insere se v ainda não estiver na fila (evita múltiplas cópias do mesmo vértice)
                                                        Marca in_queue[v] = true para indicar que v agora está na fila*/
                                    custo++; // Operação de atualização e re-enfileiramento
                            }
                        }
                    }
                }
            }
        }

        // Atualiza o mapa global de distâncias finais com os melhores caminhos desta fase
        for (int i = 0; i < num_nos; i++) {
            custo++; // Loop de atualização global
            if (dist[i] < dist_final[i]) {
                dist_final[i] = dist[i];
                custo++; // Atribuição do novo mínimo
            }
        }

        // =============================
        // FIND PIVOTS (Algorithm 1 do pdf)
        // =============================
        int threshold = B / (1 << l); //Calcula "B/(2^l)".

        /*Um nó vira pivô se sua distância calculada a partir das fontes atuais
        for menor ou igual a B/(2^l). Esses pivôs serão usados como novas fontes
        na próxima iteração.*/
        for (int i = 0; i < num_nos; i++) {
            custo++; // Varredura para encontrar pivôs
            pivots[i] = (dist[i] != INF && dist[i] <= threshold);
        }

        // Transforma os pivôs encontrados nas fontes da próxima iteração
        for (int i = 0; i < num_nos; i++) {
            custo++; // Loop de transição de fontes
            S[i] = pivots[i];
        }
    }

    //Liberação de memória
    free(dist);
    free(S);
    free(fila);
    free(pivots);
    free(dist_final);
    free(in_queue);

    /* Esta retorno também é obrigatório e não deve ser retirado*/  
    return custo; //Retorna soma das distâncias.
}

// Implementação do terceiro usando matriz de adjacência
double outro(int **matriz, int num_nos, int origem) {
    double custo = 0;

    /***********************
    ***********************
     Implementar código aqui
    ************************
    ***********************/

    /* Esta retorno também é obrigatório e não deve ser retirado*/  
    return custo;
}
