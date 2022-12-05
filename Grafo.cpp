#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "Grafo.h"
#include "Aresta.h"
#include "No.h"
#include "NoFP.h"
#include "FilaEncad.h"

using namespace std;

// CONSTRUTOR
Grafo::Grafo()
{
    ordem = 0;
    direcionado = 0;
    pesoArestas = 1;
    pesoNos = 0;
    primeiroNo = ultimoNo = NULL;
    adicionados = 0;
}

// CONSTRUTOR
Grafo::Grafo(int ord, bool direc, bool pesoA, bool pesoN, int l)
{
    ordem = ord;
    direcionado = direc;
    pesoArestas = pesoA;
    pesoNos = pesoN;
    primeiroNo = ultimoNo = NULL;
    adicionados = 0;
    lado = l;
}

// DESTRUTOR
Grafo::~Grafo()
{
    No *p = primeiroNo;
    while (p != NULL)
    {
        p->removeTodasArestas();
        No *t = p->getProx();
        delete p;
        p = t;
    }
}

// RETORNA ORDEM DO GRAFO
int Grafo::getOrdem()
{
    return ordem;
}

// RETORNA NÚMERO DE ARESTAS
int Grafo::getNumeroDeArestas()
{
    return numeroArestas;
}

// RETORNA SE O GRAFO É DIRECIONADO
bool Grafo::getDirecionado()
{
    return direcionado;
}

// RETORNA PESO DAS ARESTAS
bool Grafo::getPesoArestas()
{
    return pesoArestas;
}

// RETORNA PESO DOS NÓS
bool Grafo::getPesoNos()
{
    return pesoNos;
}

// RETORNA PRIMEIRO NÓ
No *Grafo::getPrimeiroNo()
{
    return primeiroNo;
}

// RETORNA ULTIMO NÓ
No *Grafo::getUltimoNo()
{
    return ultimoNo;
}

// RETORNA NÓ A PARTIR DE UM ID
No *Grafo::getNo(string Id)
{
    // Recebe primeiro nó
    No *n = primeiroNo;

    // Verifica se o grafo está vazio
    if (primeiroNo == NULL)
        return NULL;

    // Percorre o grafo até encontrar um nó com id desejado
    while (n->getId() != Id)
    {
        n = n->getProx();
        if (n == NULL)
        {
            break;
        }
    }

    // Se não existir retorna NULL
    if (n == NULL)
    {
        return NULL;
    }

    // Se existir retorna o nó
    return n;
}

// INSERE UM NÓ NA LISTA
No *Grafo::insereNo(string id, Tabuleiro *tab)
{
    // Gera um novo nó com o id
    No *novo = new No(id, tab);

    // Se o grafo está vazio esse nó é o primeiro
    if (primeiroNo == NULL)
    {
        primeiroNo = novo;
    }
    // Se não está vazio vira o último
    else
    {
        ultimoNo->setProx(novo);
    }
    ultimoNo = novo;
    novo->setProx(NULL);
    novo->setOrdemDeInsercao(adicionados);

    adicionados++;

    return novo;
}

// INSERE UMA NOVA ARESTA NO GRAFO
void Grafo::insereAresta(string Id, string idDirect, float peso)
{
    // Recupera o nó com Id
    No *noUm = getNo(Id);
    No *noDois = getNo(idDirect);

    // Verifica se os nós não existem
    // if(noUm == NULL)
    //{
    //    insereNo(Id);
    //}
    // if(noDois == NULL)
    //{
    //   insereNo(idDirect);
    //}

    // Recupera os nós caso não existiam antes
    if (noUm == NULL)
    {
        noUm = getNo(Id);
    }
    if (noDois == NULL)
    {
        noDois = getNo(idDirect);
    }

    // Se o grafo for direcionado aumenta o grau de entrada e de saída dos nós
    if (direcionado)
    {
        int GS = noUm->getGrauDeSaida() + 1;
        noUm->setGrauDeSaida(GS);
        int GE = noDois->getGrauDeEntrada() + 1;
        noDois->setGrauDeEntrada(GE);
    }

    // Cria nova aresta com sua direção
    Aresta *nova = new Aresta(idDirect);

    // Insere nova aresta
    // Se não existe aresta essa é a primeira
    if (noUm->getPrimeiraAresta() == NULL)
    {
        noUm->setPrimeiraAresta(nova);
    }
    // Se existe essa é a última
    else
    {
        noUm->getUltimaAresta()->setProximaAresta(nova);
    }
    nova->setPeso(peso);
    nova->setOrdemDeInsercao(noDois->getOrdemDeInsercao());
    noUm->setUltimaAresta(nova);
    nova->setProximaAresta(NULL);

    /*Se o grafo não é direcionado existe uma aresta de noUm para noDois
        e de noDois para noUM
    */
    if (direcionado == 0)
    {
        // Cria nova aresta com sua direção
        nova = new Aresta(Id);
        // Insere nova aresta
        if (noDois->getPrimeiraAresta() == NULL)
        {
            noDois->setPrimeiraAresta(nova);
        }
        else
        {
            noDois->getUltimaAresta()->setProximaAresta(nova);
        }
        nova->setPeso(peso);
        nova->setOrdemDeInsercao(noUm->getOrdemDeInsercao());
        noDois->setUltimaAresta(nova);
        nova->setProximaAresta(NULL);
    }

    noDois->setNivel(noUm->getNivel() + 1);
    noDois->setPai(noUm);
    // Aumenta o número de arestas
    numeroArestas++;
}

// IMPRIME O GRAFO
void Grafo::imprime()
{
    // Recupera o primeiro nó
    No *p = primeiroNo;

    Aresta *a;
    cout << "Ordem:" << ordem << endl;

    // Percorre o grafo
    while (p != NULL)
    {
        // Recupera a primeira aresta do nó
        a = p->getPrimeiraAresta();
        cout << p->getId() << "\t";
        while (a != NULL)
        {
            cout << a->getDirecaoId() << "-" << a->getOrdemDeInsercao() << " ";
            a = a->getProximaAresta();
        }
        cout << endl;
        p = p->getProx();
    }
    cout << endl;
}

// PROCURA UM NÓ A PARTIR DO ID
bool Grafo::procuraNo(string str)
{
    // Recupera o primero nó
    No *p = primeiroNo;

    // Percorre os nós
    while (p != NULL)
    {
        // Se o id do nó é igual a do passado retorta true
        if (str == p->getId())
            return true;
        p = p->getProx();
    }
    // Se não encontrar retorna false
    return false;
}

// GERA UM ARQUIVO DOT A PARTIR DO GRAFO
void Grafo::geraArquivoDot(string arquivoSaida, string nome)
{
    // Abre o arquivo de saída
    ofstream saida;
    saida.open(arquivoSaida);

    No *p = primeiroNo;
    Aresta *a;

    bool adicionado[ordem];

    // Imprime de acordo com a direção do grafo
    if (direcionado == 0)
        saida << "graph " << nome << "{" << endl;
    else
        saida << "digraph " << nome << "{" << endl;

    // Percorre  o grafo
    while (p != NULL)
    {
        a = p->getPrimeiraAresta();

        // Deixa o nó marcado em sua posição como adicionado no arquivo
        adicionado[p->getOrdemDeInsercao()] = true;

        // Percorre as arestas
        while (a != NULL)
        {
            // Se a aresta ainda não foi adicionada
            if (adicionado[a->getOrdemDeInsercao()] == false || direcionado == 1)
            {
                // Verifica se o grafo é direcionado
                if (direcionado == 0)
                    saida << p->getId() << " -- " << a->getDirecaoId();
                else
                    saida << p->getId() << " -> " << a->getDirecaoId();

                // Verifica se possui peso nas arestas
                if (pesoArestas == true)
                {
                    saida << " [label=" << a->getPeso() << "]";
                }

                a = a->getProximaAresta();
                saida << endl;
            }
            // Se a aresta já foi adicionada passa para próxima aresta
            else
                a = a->getProximaAresta();
        }
        p = p->getProx();
    }
    saida << "}" << endl;
}

// REMOVE NÓ DO GRAFO
void Grafo::removeNo(string id)
{
    No *D = getNo(id);
    No *p = primeiroNo;
    No *ant = NULL;

    // Percorre o grafo
    while (p != NULL)
    {
        // Se é o nó que será removido
        if (p->getId() == id)
        {
            Aresta *a = p->getPrimeiraAresta();
            // Se é o primeiro nó
            if (p == primeiroNo)
            {
                // Próximo nó vai ser o primeiro
                primeiroNo = p->getProx();
                // Apaga o as arestas que esse nó possui
                // E atualiza o grau de entrada dos nós adjacentes
                while (a != NULL)
                {
                    Aresta *t = a->getProximaAresta();
                    No *adj = getNo(a->getDirecaoId());
                    adj->setGrauDeEntrada(adj->getGrauDeEntrada() - 1);
                    delete a;
                    a = t;
                }
                // Deleta o nó
                delete p;
                // Se o grafo ficar vazio
                if (primeiroNo == NULL)
                    ultimoNo == NULL;
            }
            // Se for o último nó
            else if (p == ultimoNo)
            {
                // O último nó será o nó anterior ao removido
                ultimoNo = ant;
                ant->setProx(NULL);
                while (a != NULL)
                {
                    Aresta *t = a->getProximaAresta();
                    No *adj = getNo(a->getDirecaoId());
                    adj->setGrauDeEntrada(adj->getGrauDeEntrada() - 1);
                    delete a;
                    a = t;
                }
                delete p;
                if (ultimoNo == NULL)
                    primeiroNo == NULL;
            }
            // Se está no meio
            else
            {
                // O anterior aponta para o próximo nó
                ant->setProx(p->getProx());
                while (a != NULL)
                {
                    Aresta *t = a->getProximaAresta();
                    No *adj = getNo(a->getDirecaoId());
                    adj->setGrauDeEntrada(adj->getGrauDeEntrada() - 1);
                    delete a;
                    a = t;
                }
                delete p;
            }

            // Armazenar o nó anterior
            if (ant != NULL)
                p = ant;
            else
                p = primeiroNo;
        }
        // Se não é o nó a ser removido
        else
        {
            // Se o nó tem ordem de inserção menor do que o removido
            // Diminui sua ordem de inserção
            if (p->getOrdemDeInsercao() > D->getOrdemDeInsercao())
                p->setOrdemDeInsercao(p->getOrdemDeInsercao() - 1);
            // Remove todas aretas com o nó removido
            p->removerArestas(D->getOrdemDeInsercao());
            // Armazena anterior
            ant = p;
            p = p->getProx();
        }
    }
    // Diminui ordem e adicionados
    ordem--;
    adicionados--;
}

// RETORNA O PESO DA ARESTA ENTRE DOIS NÓS
float c(string str, string u, aresta arestas[], int tam)
{
    // Percorre o vetor de arestas e enconta o peso entre esses dois nós
    for (int i = 0; i < tam; i++)
    {
        if (arestas[i].id->getId() == str && arestas[i].idDirecao->getDirecaoId() == u)
        {
            return arestas[i].idDirecao->getPeso();
        }
        else if (arestas[i].id->getId() == u && arestas[i].idDirecao->getDirecaoId() == str)
        {
            return arestas[i].idDirecao->getPeso();
        }
    }
    // Se os nós são iguais
    if (str == u)
    {
        return 0;
    }
    // Se não exxiste a aresta
    return 9999999999999;
}

// RETORNA UMA CÓPIA DO GRAFO
Grafo *Grafo::copiaGrafo()
{
    Grafo *G = new Grafo(ordem, direcionado, pesoArestas, pesoNos, lado);
    No *p = primeiroNo;
    Aresta *a;

    // Percorre o grafo inserindo as arestas no novo grafo
    while (p != NULL)
    {
        a = p->getPrimeiraAresta();
        while (a != NULL)
        {
            G->insereAresta(p->getId(), a->getDirecaoId(), a->getPeso());
            a = a->getProximaAresta();
        }
        p = p->getProx();
    }
    return G;
}

string *Grafo::backtracking()
{

    Tabuleiro *T = new Tabuleiro(lado);

    No *S = insereNo("0", T);
    No *N = S;

    bool fracasso = false;
    bool sucesso = false;

    int nivel = 1;
    int cont = 1;

    while (!(fracasso || sucesso))
    {

        Tabuleiro *P = N->getTabuleiro()->opcao(nivel - 1, N->getJogadas());

        if (P != NULL)
        {
            nivel++;
            No *aux = insereNo(to_string(cont), P);
            cout << "Aresta de " << N->getId() << " para " << aux->getId() << endl;
            insereAresta(N->getId(), aux->getId(), 0);
            N = aux;
            if (N->getTabuleiro()->ehSolucao())
            {
                sucesso = true;
                cout << "Sucesso" << endl;
            }
        }
        else
        {
            if (N == S)
            {
                fracasso = true;
                cout << "Fracasso" << endl;
            }
            else
            {
                N = N->getPai();
                nivel--;
            }
        }
        cont++;

        cout << "Nivel: " << nivel << endl;
        cout << "Tabuleiro" << endl;
        N->getTabuleiro()->imprimeTabuleiro();
    }
}

void Grafo::buscaLargura()
{
    Tabuleiro *T = new Tabuleiro(lado);

    No *S = insereNo("0", T);
    No *N = S;
    N->setNivel(0);
    NoFP *n = new NoFP(N);
    NoFP *s = new NoFP(S);

    FilaEncad *abertos = new FilaEncad();
    abertos->enfileira(s);

    FilaEncad *fechados = new FilaEncad();

    bool fracasso = false;
    bool sucesso = false;

    int nivel = 1;
    int cont = 1;

    while (!(sucesso || fracasso))
    {
        if (abertos->vazia())
        {
            fracasso = true;
        }
        else
        {
            n = abertos->desenfileira();
            N = n->getInfo();
            Tabuleiro *P = N->getTabuleiro()->opcao(N->getNivel(), N->getJogadas());
            cout << N->getId() << " Pai: " << endl;
            cout << "Nivel: " << N->getNivel() << endl;
            N->getTabuleiro()->imprimeTabuleiro();

            if (N->getTabuleiro()->ehSolucao())
            {
                sucesso = true;
            }

            while (P != NULL)
            {
                No *AUX = insereNo(to_string(cont), P);
                insereAresta(N->getId(), AUX->getId(), 0);
                AUX->setNivel(N->getNivel() + 1);
                NoFP *aux = new NoFP(AUX);
                abertos->enfileira(aux);
                cont++;
                cout << AUX->getId() << " Filho do " << N->getId() << ": " << endl;
                AUX->getTabuleiro()->imprimeTabuleiro();
                P = N->getTabuleiro()->opcao(N->getNivel(), N->getJogadas());
            }

            fechados->enfileira(n);

            cout << "Abertos: ";
            abertos->imprime();
            cout << "Fechados: ";
            fechados->imprime();
            
            nivel++;
        }
    }
}
