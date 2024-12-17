#include "bloco.h"
#include "posicao.h"

class LBlock : public Bloco
{
public:
    LBlock()
    {
        id = 1;
        celulas[0] = {Posicao(0, 2), Posicao(1, 0), Posicao(1, 1), Posicao(1, 2)};
        celulas[1] = {Posicao(0, 1), Posicao(1, 1), Posicao(2, 1), Posicao(2, 2)};
        celulas[2] = {Posicao(1, 0), Posicao(1, 1), Posicao(1, 2), Posicao(2, 0)};
        celulas[3] = {Posicao(0, 0), Posicao(0, 1), Posicao(1, 1), Posicao(2, 1)};
        Mover(0, 3);
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
        Mover(0, 3);
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
        Mover(-1, 3);
    }
};

class OBlock : public Bloco
{
public:
    OBlock()
    {
        id = 4;
        celulas[0] = {Posicao(0, 0), Posicao(0, 1), Posicao(1, 0), Posicao(1, 1)};
        Mover(0, 4);
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
        Mover(0, 3);
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
        Mover(0, 3);
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
        Mover(0, 3);
    }
};