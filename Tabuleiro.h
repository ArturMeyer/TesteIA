#ifndef TABULEIRO_H_INCLUDED
#define TABULEIRO_H_INCLUDED

using namespace std;

class Tabuleiro
{

private:
    int lado;
    char* vet;
    int quantidadeRainhas;
    bool* jogadas;

    int determinaIndice(int linha, int coluna);
    void marcaLocaisAtacados(int linha, int coluna);
    void marcaHorizontalVertical(int linha, int coluna);
    void marcaDiagonal(int linha, int coluna, string tipoDiagonal);

    void setPosicao(int valor, int indice);

public:
    //CONSTRUTOR
    Tabuleiro();
    Tabuleiro(int lado);

    //DESTRUTOR
    ~Tabuleiro();
    
    bool insereRainha(int linha, int coluna);
    void imprimeTabuleiro();
    void copiaTabuleiro(Tabuleiro* tabuleiro);
    char getPosicao(int indice);
    Tabuleiro* opcao(int nivel, bool* n);
    void setJogada(int linha, int coluna);
    void setJogadas(bool* jogadas);
    bool getJogada(int linha, int coluna);
    bool* getJogadas();
    bool ehSolucao();
    void imprimeJogada();
    int getLado();
};

#endif
