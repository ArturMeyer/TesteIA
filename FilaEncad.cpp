#include <iostream>
#include <cstdlib>
#include "FilaEncad.h"

using namespace std;

FilaEncad::FilaEncad()
{
    cout << "Criando FilaEncad" << endl;
    inicio = NULL;
    fim = NULL;
}

FilaEncad::~FilaEncad()
{
    cout << "Destruindo FilaEncad" << endl;
    NoFP *p = inicio;
    while (inicio != NULL)
    {
        inicio = p->getProx();
        delete p;
        p = inicio;
    }
    fim = NULL;
}

bool FilaEncad::vazia()
{
    if (inicio == NULL)
        return true;
    else
        return false;
}

void FilaEncad::enfileira(NoFP *n)
{
    n->setProx(NULL);
    if (fim == NULL)
        inicio = n;
    else
        fim->setProx(n);
    fim = n;
}

NoFP *FilaEncad::getInicio()
{
    if (inicio != NULL)
        return inicio;
    else
    {
        cout << "Fila vazia!" << endl;
        exit(1);
    }
}

NoFP *FilaEncad::desenfileira()
{
    NoFP *p;
    if (inicio != NULL)
    {
        p = inicio;
        inicio = p->getProx();
        if (inicio == NULL)
            fim = NULL;
        return p;
    }
    else
    {
        cout << "ERRO: Fila Vazia!" << endl;
        exit(1);
    }
}

void FilaEncad::imprime()
{
    if (inicio != NULL)
    {
        NoFP *p = inicio;
        while (p != NULL)
        {
            cout << p->getInfo()->getId() << ", ";
            p = p->getProx();
        }
        cout << endl;
    }
}
