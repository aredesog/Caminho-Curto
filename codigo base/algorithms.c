#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

// Algoritmo de Dijkstra usando matriz de adjacência
double dijkstra(int **matriz, int num_nos, int origem) {
    double custo = 0;
    //Algoritimo guloso

    // Comecar o array de distancia (infinito, origem no 0)
    // Comecar array de visitados (falso)

    //LOOP 
    // Algoritimo guloso 

        // menor distancia Ok / proximo vizinho de menor valor
        //Buscar no array de distancias qual e o nó NAO VISITADO que tem o menor valor atualmente
        
        //Marcar esse nó escolhido como VISITADO no array de visitados

        // Vizualiza seus vizinhos / soma dos valores
        //Percorrer a linha da matriz correspondente a esse nó para achar os vizinhos
        // Para cada vizinho
            // Se distancia atual + peso ate vizinho < distancia dovizinho salva
                // Atualiza a distância no array de distancias


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