#include <iostream>
#include "Grafo.h"

using namespace std;

int main()
{
    Grafo *G = new Grafo(5, 0, 0, 0, 8); // lado = 8

    G->buscaLargura(); 

    return 0;
}
