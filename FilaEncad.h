#ifndef FILAENCAD_H_INCLUDED
#define FILAENCAD_H_INCLUDED
#include "NoFP.h"

using namespace std;

class FilaEncad
{
private:
    NoFP *inicio;
    NoFP *fim;      /// ponteiros para os No's extremos
public:
    FilaEncad();
    ~FilaEncad();
    NoFP* getInicio();           /// retorna valor do primeiro No
    void enfileira(NoFP* n);   /// insere No no fim
    NoFP* desenfileira();        /// elimina No do inicio
    bool vazia();     
    void imprime();         /// verifica se fila esta vazia
};

#endif // FILAENCAD_H_INCLUDED
