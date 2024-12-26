#include "grid.h"
#include <iostream>
#include "cores.h"

Grid::Grid()
{
    Inicializar();
    cores = GetCoresCelulas();
}

/* Inicializando a matriz com 0, o que representa a cor do retângulos que compõem o Grid */
void Grid::Inicializar()
{
    for (int linha = 0; linha < numLinhas; linha++)
    {
        for (int coluna = 0; coluna < numColunas; coluna++)
        {
            grid[linha][coluna] = 0;
        }
    }
}

/* Desenhando as células, o segredo do espaçamento está no -1 no WIDTH e no HEIGHT */
void Grid::Desenhar()
{
    for (int linha = 0; linha < numLinhas; linha++)
    {
        for (int coluna = 0; coluna < numColunas; coluna++)
        {
            int valorCelula = grid[linha][coluna];
            DrawRectangle(coluna * tamCelula + 11, linha * tamCelula + 11, tamCelula - 1, tamCelula - 1, cores[valorCelula]);
        }
    }
}

int Grid::LimparLinhasCheias()
{
    int linhasLimpas = 0;

    for (int linha = numLinhas - 1; linha >= 0; linha--)
    {
        bool linhaCheia = true;

        for (int coluna = 0; coluna < numColunas; coluna++)
        {
            /* Verifica se existe algum espaço vazio na linha*/
            if (grid[linha][coluna] == 0)
            {
                linhaCheia = false;
                break;
            }
        }

        if (linhaCheia)
        {
            linhasLimpas++;

            /* Se a linha estiver cheia, limpa-a */
            for (int coluna = 0; coluna < numColunas; coluna++)
            {
                grid[linha][coluna] = 0;
            }

            /* Todas as linhas acima deslocarão para baixo */
            for (int l = linha - 1; l >= 0; l--)
            {
                for (int coluna = 0; coluna < numColunas; coluna++)
                {
                    grid[l + 1][coluna] = grid[l][coluna];
                    grid[l][coluna] = 0;
                }
            }

            linha++;
        }
    }

    return linhasLimpas;
}