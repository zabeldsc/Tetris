#include "bloco.h"

Bloco::Bloco()
{
    tamanhoCelula = 30;
    estadoRotacao = 0;
    cores = GetCoresCelulas();
    deslocamentoLinha = 0;
    deslocamentoColuna = 0;
}

void Bloco::Desenhar(int deslocamentoX, int deslocamentoY)
{
    std::vector<Posicao> tiles = GetCellPositions();
    for (Posicao item : tiles)
    {
        DrawRectangle(item.coluna * tamanhoCelula + deslocamentoX, item.linha * tamanhoCelula + deslocamentoY, tamanhoCelula - 1, tamanhoCelula - 1, cores[id]);
    }
}

void Bloco::Mover(int linhas, int colunas)
{
    deslocamentoLinha += linhas;
    deslocamentoColuna += colunas;
}

std::vector<Posicao> Bloco::GetCellPositions()
{
    std::vector<Posicao> tiles = celulas[estadoRotacao];
    std::vector<Posicao> movedTiles;
    for (Posicao item : tiles)
    {
        Posicao novaPosicao = Posicao(item.linha + deslocamentoLinha, item.coluna + deslocamentoColuna);
        movedTiles.push_back(novaPosicao);
    }
    return movedTiles;
}

void Bloco::Rotacionar()
{
    estadoRotacao++;
    if (estadoRotacao == (int)celulas.size())
    {
        estadoRotacao = 0;
    }
}

void Bloco::DesfazerRotacao()
{
    estadoRotacao--;
    if (estadoRotacao == -1)
    {
        estadoRotacao = celulas.size() - 1;
    }
}

void Bloco::ReinicioPeca()
{
    estadoRotacao = 0;
    deslocamentoColuna = 0;
    deslocamentoLinha = 0;
}