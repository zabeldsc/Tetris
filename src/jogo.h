#pragma once
#include "grid.h"
#include "blocos.cpp"

class Jogo
{
public:
    Jogo();
    ~Jogo();
    void Draw();
    void TratarEntrada();
    void GuardarPeca();
    void QuedaLivre();
    void DescerBloco();
    bool gameOver{};
    bool primeiroHold{};
    bool fezHold{};
    int totalLinhas{};
    int score{};
    int nivel = 1;                  // Nível atual do jogo
    Music musica{};

private:
    void MoveBlockLeft();
    void MoveBlockRight();
    Bloco GetRandomBlock();
    std::vector<Bloco> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Grid grid{};
    std::vector<Bloco> blocks;
    Bloco blocoAtual{};
    Bloco proximoBloco{};
    Bloco blocoHold{};
    Sound rotateSound{};
    Sound clearSound{};
};