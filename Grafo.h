#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <cstring>
using namespace std;
#include "No.h"

typedef struct {
    No* id;
    Aresta* idDirecao;
} aresta;

class Grafo
{
private:
    int ordem;
    int numeroArestas;
    bool direcionado;
    bool pesoArestas;
    bool pesoNos;
    No* primeiroNo;
    No* ultimoNo;
    int adicionados;
    int lado;

public:
    //CONSTRUTOR
    Grafo();
    Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoNos, int lado);
    //DESTRUTOR
    ~Grafo();
    //GET
    int getOrdem();
    int getNumeroDeArestas();
    bool getDirecionado();
    bool getPesoArestas();
    bool getPesoNos();
    No* getPrimeiroNo();
    No* getUltimoNo();
    No* getNo(string id);
    //INSERE
    No* insereNo(string id, Tabuleiro* tabuleiro);
    void insereAresta(string id, string idDirecao, float peso);
    //REMOVE
    void removeNo(string id);
    //IMPRIME
    void imprime();
    //GERA ARQUIVO
    void geraArquivoDot(string arquivoSaida, string nome);
    //PROCURA
    bool procuraNo(string Id);
    //COPIA
    Grafo* copiaGrafo();
    //BUSCA
    string* backtracking();
    void buscaLargura();
};

#endif