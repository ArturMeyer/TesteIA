#include <iostream>
#include <string>
#include <sstream>
#include "Tabuleiro.h"

using namespace std;

Tabuleiro::Tabuleiro(int tamanho)
{
    lado = tamanho;
    int tamanhoVetor = lado * lado;
    vet = new char[tamanhoVetor];
    jogadas = new bool[tamanhoVetor];

    for (int i = 0; i < tamanhoVetor; i++)
    {
        vet[i] = 'V';
    }

    for (int i = 0; i < tamanhoVetor; i++)
    {
        jogadas[i] = false;
    }
}

Tabuleiro::Tabuleiro()
{
    lado = 8;
    int tamanhoVetor = lado * lado;
    vet = new char[tamanhoVetor];

    for (int i = 0; i < tamanhoVetor; i++)
    {
        vet[i] = 'V';
    }
}

Tabuleiro::~Tabuleiro()
{
    delete[] vet;
}

int Tabuleiro::determinaIndice(int linha, int coluna)
{
    int indice = linha * lado + coluna;
    if (indice >= 0 && indice <= lado * lado && linha >= 0 && linha < lado && coluna >= 0 && coluna < lado)
    {
        return indice;
    }
    return -1;
}

bool Tabuleiro::insereRainha(int linha, int coluna)
{
    int indice = determinaIndice(linha, coluna);
    if (indice != -1 && vet[indice] == 'V')
    {
        vet[indice] = 'R';
        marcaLocaisAtacados(linha, coluna);
        return true;
    }
    return false;
}

void Tabuleiro::marcaHorizontalVertical(int linha, int coluna)
{
    int indiceColuna = 0;
    int indiceLinha = 0;

    for (int i = 0; i < lado; i++)
    {
        indiceColuna = determinaIndice(linha, i);
        if (i != coluna && vet[indiceColuna] != 1)
        {
            vet[indiceColuna] = 158;
        }

        indiceLinha = determinaIndice(i, coluna);
        if (i != linha && vet[indiceLinha] != 1)
        {
            vet[indiceLinha] = 158;
        }
    }
}

// Tipo pode assumir valores "NE", "NO", "SO" e "SE"
void Tabuleiro::marcaDiagonal(int linha, int coluna, string direcaoDiagonal)
{
    int linhaDiagonal = linha;
    int colunaDiagonal = coluna;

    bool diagonalCompleta = false;

    int fatorLinha = 0;
    int fatorColuna = 0;

    if (direcaoDiagonal == "NE")
    {
        fatorLinha = -1;
        fatorColuna = 1;
    }
    else if (direcaoDiagonal == "NO")
    {
        fatorLinha = -1;
        fatorColuna = -1;
    }
    else if (direcaoDiagonal == "SO")
    {
        fatorLinha = 1;
        fatorColuna = -1;
    }
    else if (direcaoDiagonal == "SE")
    {
        fatorLinha = 1;
        fatorColuna = 1;
    }

    for (int i = 0; i < lado || !diagonalCompleta; i++)
    {
        linhaDiagonal = linhaDiagonal + fatorLinha;
        colunaDiagonal = colunaDiagonal + fatorColuna;

        int indiceDiagonal = determinaIndice(linhaDiagonal, colunaDiagonal);

        if (indiceDiagonal != -1 && vet[indiceDiagonal] != 1)
        {
            vet[indiceDiagonal] = 158;
        }
        else if (indiceDiagonal == -1)
        {
            diagonalCompleta = true;
        }
    }
}

char Tabuleiro::getPosicao(int indice)
{
    return vet[indice];
}

void Tabuleiro::setPosicao(int valor, int indice)
{
    vet[indice] = valor;
}

void Tabuleiro::copiaTabuleiro(Tabuleiro *tabuleiro)
{
    for (int i = 0; i < lado * lado; i++)
    {
        setPosicao(tabuleiro->getPosicao(i), i);
    }
    tabuleiro->setJogadas(this->getJogadas());
}

void Tabuleiro::marcaLocaisAtacados(int linha, int coluna)
{
    marcaHorizontalVertical(linha, coluna);
    marcaDiagonal(linha, coluna, "SE");
    marcaDiagonal(linha, coluna, "SO");
    marcaDiagonal(linha, coluna, "NE");
    marcaDiagonal(linha, coluna, "NO");
}

void Tabuleiro::imprimeTabuleiro()
{
    for (int i = 0; i < (lado * lado); i++)
    {
        cout << vet[i] << '\t';
        if ((i + 1) % lado == 0 && i != 0)
        {
            cout << endl;
        }
    }

    cout << endl;
}

Tabuleiro *Tabuleiro::opcao(int nivel, bool* n)
{
    Tabuleiro *auxTab = new Tabuleiro(lado);
    auxTab->setJogadas(this->getJogadas());
    bool inseriu = false;
    int i = 0;
    cout << nivel << endl;
    for (i = 0; i < lado; i++)
    {
        auxTab->copiaTabuleiro(this);
        if (auxTab->insereRainha(nivel, i)  && n[i])
        {
            auxTab->setJogada(nivel, i);
            inseriu = true;
            n[i] = false;
            break;
        }
        else
        {
            n[i] = false;
        }
    }
    cout << "[ ";
    for (int i = 0; i < lado; i++)
    {
        cout << n[i] << " ";
    }
    cout << " ]" << endl;
    if (inseriu)
    {
        return auxTab;
    }
    else
        return NULL;
}

void Tabuleiro::setJogada(int linha, int coluna)
{
    jogadas[determinaIndice(linha, coluna)] = true;
}

void Tabuleiro::setJogadas(bool *j)
{
    jogadas = j;
}

bool *Tabuleiro::getJogadas()
{
    return jogadas;
}

bool Tabuleiro::getJogada(int linha, int coluna)
{
    return jogadas[determinaIndice(linha, coluna)];
}

void Tabuleiro::imprimeJogada()
{
    for (int i = 0; i < (lado * lado); i++)
    {
        cout << jogadas[i] << '\t';
        if ((i + 1) % lado == 0 && i != 0)
        {
            cout << endl;
        }
    }

    cout << endl;
}

bool Tabuleiro::ehSolucao()
{
    int contRainhas = 0;
    for (int i = 0; i < lado * lado; i++)
    {
        if (vet[i] == 'R')
        {
            contRainhas++;
        }
    }
    if (contRainhas == lado)
        return true;
    else
        return false;
}

int Tabuleiro::getLado()
{

    return lado;
}