#include "bloco.h"

Bloco::Bloco()
{
    cores = GetCoresCelulas();
}

void Bloco::Desenhar(int deslocamentoX, int deslocamentoY)
{
    /* Aqui ele desenha cada célula individualmente! */
    std::vector<Posicao> tiles = GetCellPositions();
    for (Posicao item : tiles)
    {
        DrawRectangle(item.coluna * tamanhoCelula + deslocamentoX, item.linha * tamanhoCelula + deslocamentoY, tamanhoCelula - 1, tamanhoCelula - 1, cores[id]);
    }
}

std::vector<Posicao> Bloco::GetCellPositions()
{
    /* IMPORTANTE */
    /* Esse vetor vai ACESSAR dentro de celulas << Olhar o blocos.cpp novamente >>
    (a depender do bloco) o estado da rotação (que contém Posicao(linha, coluna)) */
    std::vector<Posicao> vetorPosicaoPeca = celulas[estadoRotacao];
    std::vector<Posicao> movedTiles;

    /* Cada item, ou seja, cada posição que uma das células do Bloco vai ocupar,
    é inserido dentro de movedTiles a novaPosicao da CELULA! */
    for (Posicao item : vetorPosicaoPeca)
    {
        /* A novaPosicao precisa ter não só a linha e coluna para formar a imagem, mas também conter o
        deslocamento da LINHA e da COLUNA (pois o usuário move a peça!) */
        Posicao novaPosicao = Posicao(item.linha + deslocamentoLinha, item.coluna + deslocamentoColuna);
        movedTiles.push_back(novaPosicao);
    }
    return movedTiles;
}

void Bloco::ReinicioPeca(int id)
{
    estadoRotacao = 0;
    deslocamentoColuna = 0;
    deslocamentoLinha = 0;

    switch (id)
    {
    case 3:
        deslocamentoColuna += 3;
        deslocamentoLinha--;
        break;
    case 4:
        deslocamentoColuna += 4;
        break;
    default:
        deslocamentoColuna += 3;
        break;
    }
}