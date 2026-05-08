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

    /***********************
    ***********************
     Implementar código aqui
    ************************
    ***********************/

    /* Esta retorno também é obrigatório e não deve ser retirado*/  
    return custo;
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