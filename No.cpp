#include <iostream>
#include "No.h"
#include "Tabuleiro.h"

No::No(string Id, Tabuleiro* tab)
{
    id = Id;
    primeiraAresta = ultimaAresta  = NULL;
    proximoNo = NULL;
    grauDeEntrada = grauDeSaida = peso = 0;
    tabuleiro = tab;
    nivel = 0;
    pai = NULL;
    jogadas = new bool[tab->getLado()];
    for(int i = 0; i < tab->getLado(); i++){
        jogadas[i] = 1;
    }
}

No::No()
{
    
}

No::~No()
{
    delete [] jogadas;
}

void No::removerArestas(int ord)
{
    Aresta* a = primeiraAresta;
    Aresta* ant;

    while (a != NULL)
    {
        if(a->getOrdemDeInsercao() == ord)
        {
            if(a == primeiraAresta)
            {
                primeiraAresta = a->getProximaAresta();
                ant = a;
                delete a;
                if(primeiraAresta == NULL)
                    ultimaAresta == NULL;
            }else if(a == ultimaAresta)
            {
                ultimaAresta = ant;
                ant->setProximaAresta(NULL);
                delete a;
                if(ultimaAresta == NULL)
                    primeiraAresta == NULL;
            }else
            {
                ant->setProximaAresta(a->getProximaAresta());
                ant = a;
                delete a;
            }
            grauDeSaida--;
        }

        if(a->getOrdemDeInsercao() > ord)
            a->setOrdemDeInsercao(a->getOrdemDeInsercao() -1);
        ant = a;
        a = a->getProximaAresta();
    }
    
}

void No::removeTodasArestas()
{
    Aresta* a = primeiraAresta;
    while(a!=NULL)
    {
        Aresta* t = a->getProximaAresta();
        delete a;
        a = t;
    }
    
}

void No::setProx(No* p)
{
    proximoNo  = p;
}

void No::setPeso(float val)
{
    peso = val;
}

Aresta* No::getPrimeiraAresta()
{
    return primeiraAresta;
}

Aresta* No::getUltimaAresta()
{
    return ultimaAresta;
}

string No::getId()
{
    return id;
}

int No::getGrauDeEntrada()
{
    return grauDeEntrada;
}

int No::getGrauDeSaida()
{
    return grauDeSaida;
}

int No::getOrdemDeInsercao()
{
    return ordemDeInsercao;
}


float No::getPeso()
{
    return peso;
}

No* No::getProx()
{
    return proximoNo;
}

void No::setPrimeiraAresta(Aresta* primeira)
{
    primeiraAresta = primeira;
}

void No::setUltimaAresta(Aresta* ultima)
{
    ultimaAresta = ultima;
}

void No::setOrdemDeInsercao(int pos)
{
    ordemDeInsercao = pos;
}

void No::setId(string str)
{
    id = str;
}

void No::setGrauDeEntrada(unsigned int gE)
{
    grauDeEntrada = gE;
}

void No::setGrauDeSaida(unsigned int gS)
{
    grauDeSaida = gS;
}

Tabuleiro* No::getTabuleiro()
{
    return tabuleiro;
}

int No::getNivel(){
    return nivel;
}

void No::setNivel(int n){
    nivel = n;
}

No* No::getPai(){
    return pai;
}

void No::setPai(No* p){
    pai = p;
}

void No::setJogada(int coluna){
    jogadas[coluna] = false;
}

int No::getJogada(int coluna){
    return jogadas[coluna];
}

bool* No::getJogadas(){
    return jogadas;
}