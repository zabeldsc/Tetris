#pragma once
#include "grid.h"
#include "blocos.cpp"

class Jogo
{
public:
    Jogo();
    ~Jogo();
    void Desenhar();
    void TratarEntrada();
    void GuardarPeca();
    void QuedaLivre();
    void DescerBloco();
    void Reset();
    bool gameOver = false;
    bool primeiroHold{};
    bool fezHold{};
    int totalLinhas{};
    int score = 0;
    int nivel = 1;
    int qtdBlocos = 7;
    Music musica{};

private:
    Bloco GetBlocoAleatorio();
    bool BlocoFora();
    void RotacionarBloco();
    void LockBloco();
    bool BlocoCabe();
    void MaisScoreLinha(int linhasDescidas);
    Grid grid{};
    std::vector<Bloco> blocos;
    Bloco blocoAtual{};
    Bloco proximoBloco{};
    Bloco blocoHold{};
    Sound rotateSound{};
    Sound clearSound{};
};