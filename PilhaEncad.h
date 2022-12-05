#ifndef PILHAENCAD_H_INCLUDED
#define PILHAENCAD_H_INCLUDED
#include "NoFP.h"

using namespace std;

class PilhaEncad
{
private:
    NoFP *topo;                /// ponteiro p/ o NoFP do topo

public:
    PilhaEncad();
    ~PilhaEncad();
    NoFP* getTopo();           /// retorna valor do NoFP do topo
    void empilha(NoFP* n);   /// insere No no topo
    NoFP* desempilha();        /// elimina NoFP do topo
    bool vazia();            /// verifica se est� vazia
};

#endif // PILHAENCAD_H_INCLUDED
