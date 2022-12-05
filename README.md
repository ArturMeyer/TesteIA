# TesteIA

## Compilar
Na pasta do projeto utilizar os comandos
```
g++ *.c* -o main
```

## Rodar
No caso de Windows
```sh
main
```

## Utilizar as buscas
Aconselho testar com lado de tamanho 4 antes
```c
int main()
{
    //O ultimo parâmetro define o tamanho dos lados do tabuleiro
    Grafo *G = new Grafo(5, 0, 0, 0, 8); // lado = 8
    //Utilizar busca em largura
    G->buscaLargura();
    //Utilizar backtracking
    G->backtracking();

    return 0;
}
```
