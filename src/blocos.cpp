#include "bloco.h"
#include "posicao.h"

/* Cada específico Bloco herda da classe Bloco, e é aqui que são inicializadas as variáveis de id e celulas[] !!! */
class LBlock : public Bloco
{
public:
    /* O id diz respeito a cor que vai ser colocada no Grid (correlação com GetCoresCelulas()) */
    /* Cada posição de células diz respeito a uma posição de rotação, (linha, coluna) */

    LBlock()
    {
        id = 1;
        celulas[0] = {Posicao(0, 2), Posicao(1, 0), Posicao(1, 1), Posicao(1, 2)};
        celulas[1] = {Posicao(0, 1), Posicao(1, 1), Posicao(2, 1), Posicao(2, 2)};
        celulas[2] = {Posicao(1, 0), Posicao(1, 1), Posicao(1, 2), Posicao(2, 0)};
        celulas[3] = {Posicao(0, 0), Posicao(0, 1), Posicao(1, 1), Posicao(2, 1)};
        /* Move o bloco para seu ponto de origem (no meio superior) */
        deslocamentoColuna += 3;
    }
};

class JBlock : public Bloco
{
public:
    JBlock()
    {
        id = 2;
        celulas[0] = {Posicao(0, 0), Posicao(1, 0), Posicao(1, 1), Posicao(1, 2)};
        celulas[1] = {Posicao(0, 1), Posicao(0, 2), Posicao(1, 1), Posicao(2, 1)};
        celulas[2] = {Posicao(1, 0), Posicao(1, 1), Posicao(1, 2), Posicao(2, 2)};
        celulas[3] = {Posicao(0, 1), Posicao(1, 1), Posicao(2, 0), Posicao(2, 1)};
        deslocamentoColuna += 3;
    }
};

class IBlock : public Bloco
{
public:
    IBlock()
    {
        id = 3;
        celulas[0] = {Posicao(1, 0), Posicao(1, 1), Posicao(1, 2), Posicao(1, 3)};
        celulas[1] = {Posicao(0, 2), Posicao(1, 2), Posicao(2, 2), Posicao(3, 2)};
        celulas[2] = {Posicao(2, 0), Posicao(2, 1), Posicao(2, 2), Posicao(2, 3)};
        celulas[3] = {Posicao(0, 1), Posicao(1, 1), Posicao(2, 1), Posicao(3, 1)};
        deslocamentoLinha--;
        deslocamentoColuna += 3;
    }
};

class OBlock : public Bloco
{
public:
    OBlock()
    {
        id = 4;
        celulas[0] = {Posicao(0, 0), Posicao(0, 1), Posicao(1, 0), Posicao(1, 1)};
        deslocamentoColuna += 4;
    }
};

class SBlock : public Bloco
{
public:
    SBlock()
    {
        id = 5;
        celulas[0] = {Posicao(0, 1), Posicao(0, 2), Posicao(1, 0), Posicao(1, 1)};
        celulas[1] = {Posicao(0, 1), Posicao(1, 1), Posicao(1, 2), Posicao(2, 2)};
        celulas[2] = {Posicao(1, 1), Posicao(1, 2), Posicao(2, 0), Posicao(2, 1)};
        celulas[3] = {Posicao(0, 0), Posicao(1, 0), Posicao(1, 1), Posicao(2, 1)};
        deslocamentoColuna += 3;
    }
};

class TBlock : public Bloco
{
public:
    TBlock()
    {
        id = 6;
        celulas[0] = {Posicao(0, 1), Posicao(1, 0), Posicao(1, 1), Posicao(1, 2)};
        celulas[1] = {Posicao(0, 1), Posicao(1, 1), Posicao(1, 2), Posicao(2, 1)};
        celulas[2] = {Posicao(1, 0), Posicao(1, 1), Posicao(1, 2), Posicao(2, 1)};
        celulas[3] = {Posicao(0, 1), Posicao(1, 0), Posicao(1, 1), Posicao(2, 1)};
        deslocamentoColuna += 3;
    }
};

class ZBlock : public Bloco
{
public:
    ZBlock()
    {
        id = 7;
        celulas[0] = {Posicao(0, 0), Posicao(0, 1), Posicao(1, 1), Posicao(1, 2)};
        celulas[1] = {Posicao(0, 2), Posicao(1, 1), Posicao(1, 2), Posicao(2, 1)};
        celulas[2] = {Posicao(1, 0), Posicao(1, 1), Posicao(2, 1), Posicao(2, 2)};
        celulas[3] = {Posicao(0, 1), Posicao(1, 0), Posicao(1, 1), Posicao(2, 0)};
        deslocamentoColuna += 3;
    }
};