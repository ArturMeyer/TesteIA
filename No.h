#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include <cstring>
#include "Aresta.h"
#include "Tabuleiro.h"

using namespace std;

class No
{
private:
    Aresta* primeiraAresta;
    Aresta* ultimaAresta;
    Tabuleiro* tabuleiro;
    string id;
    int nivel;
    int ordemDeInsercao;
    unsigned int grauDeSaida;
    unsigned int grauDeEntrada;
    float peso;
    No* proximoNo;
    No* pai;
    bool* jogadas;
public:
    //CONSTRUTOR
    No();
    No(string id, Tabuleiro* tabuleiro);
    //DESTRUTOR
    ~No();
    //SET
    void setProx(No* no);
    void setPeso(float val);
    void setPrimeiraAresta(Aresta* Primeira);
    void setUltimaAresta(Aresta* Ultima);
    void setOrdemDeInsercao(int pos);
    void setId(string str);
    void setGrauDeEntrada(unsigned int gE);
    void setGrauDeSaida(unsigned int gS);
    void setNivel(int n);
    void setPai(No* p);
    void setJogada(int coluna);
    //GET
    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();
    string getId();
    int getGrauDeEntrada();
    int getGrauDeSaida();
    int getOrdemDeInsercao();
    float getPeso();
    No* getProx();
    bool* getJogadas();
    Tabuleiro* getTabuleiro();
    int getNivel();
    No* getPai();
    int getJogada(int coluna);
    //REMOVER
    void removerArestas(int ord);
    void removeTodasArestas();
};

#endif //NO_H_INCLUDED





