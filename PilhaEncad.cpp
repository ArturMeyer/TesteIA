#include <iostream>
#include <cstdlib>
#include "PilhaEncad.h"

using namespace std;

// construtor
PilhaEncad::PilhaEncad()
{
    cout << "Criando PilhaEncad" << endl;
    topo = NULL;
}

// destrutor
PilhaEncad::~PilhaEncad()
{
    cout << "Destruindo PilhaEncad" << endl;
    NoFP* p = topo;
    while(topo != NULL)
    {
        topo = p->getProx();
        delete p;
        p = topo;
    }
}

void PilhaEncad::empilha(NoFP* n)
{
    n->setProx(topo);
    topo = n;
}

NoFP* PilhaEncad::desempilha()
{
    NoFP* p;
    if(topo != NULL)
    {
        p = topo;
        topo = p->getProx();
        return p;
    }
    else
    {
        cout << "ERRO: Pilha vazia!" << endl;
        exit(1);
    }
}

NoFP* PilhaEncad::getTopo()
{
    if(topo != NULL)
        return topo;
    else
    {
        cout << "Pilha vazia!" << endl;
        exit(1);
    }
}

bool PilhaEncad::vazia()
{
    if(topo == NULL)
        return(true);
    else
        return(false);
}
