#include "bloco.h"

Bloco::Bloco()
{
    cores = GetCoresCelulas();
}

void Bloco::Desenhar(int deslocamentoX, int deslocamentoY)
{
    /* Aqui ele desenha cada célula individualmente! */
    std::vector<Posicao> tiles = GetCellPositions();
    for (int i = 0; i < (int)tiles.size(); i++)
    {
        int posX = tiles[i].coluna * tamanhoCelula + deslocamentoX;
        int posY = tiles[i].linha * tamanhoCelula + deslocamentoY;
        DrawRectangle(posX, posY, tamanhoCelula - 1, tamanhoCelula - 1, cores[id]);
    }
}

std::vector<Posicao> Bloco::GetCellPositions()
{
    /* IMPORTANTE */
    /* Esse vetor vai ACESSAR dentro de celulas << Olhar o blocos.cpp novamente >>
    (a depender do bloco) o estado da rotação (que contém Posicao(linha, coluna)) */
    std::vector<Posicao> vetorPosicaoPeca = celulas[estadoRotacao];
    std::vector<Posicao> movedTiles;

    for (int i = 0; i < (int)vetorPosicaoPeca.size(); i++)
    {
        int novaLinha = vetorPosicaoPeca[i].linha + deslocamentoLinha;
        int novaColuna = vetorPosicaoPeca[i].coluna + deslocamentoColuna;
        /* Pegando a posição da célula junto com o deslocamento */
        Posicao novaPosicao = Posicao(novaLinha, novaColuna);
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