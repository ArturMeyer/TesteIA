#ifndef NOFP_H_INCLUDED
#define NOFP_H_INCLUDED
#include "No.h"

class NoFP
{
private:
    NoFP *prox;
    No *info;

public:
    NoFP(No *n){info = n;};
    ~NoFP(){};
    void setInfo(No *n) { info = n; };
    void setProx(NoFP *p) { prox = p; };
    No *getInfo() { return info; };
    NoFP *getProx() { return prox; };
};

#endif // NO_H_INCLUDED
