#include "grid.h"
#include <iostream>
#include "cores.h"

Grid::Grid()
{
    numLinhas = 20;
    numColunas = 10;
    tamCelula = 30;
    Inicializar();
    cores = GetCoresCelulas();
}

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

bool Grid::ChecarCelulaFora(int linha, int coluna)
{
    if (linha >= 0 && linha < numLinhas && coluna >= 0 && coluna < numColunas)
    {
        return false;
    }
    return true;
}

bool Grid::ChecarCelulaVazia(int linha, int coluna)
{
    if (grid[linha][coluna] == 0)
    {
        return true;
    }
    return false;
}

int Grid::LimparLinhasCheias()
{
    int completa = 0;
    for (int linha = numLinhas - 1; linha >= 0; linha--)
    {
        if (LinhaCheia(linha))
        {
            LimparLinha(linha);
            completa++;
        }
        else if (completa > 0)
        {
            DescerLinha(linha, completa);
        }
    }
    return completa;
}

bool Grid::LinhaCheia(int linha)
{
    for (int coluna = 0; coluna < numColunas; coluna++)
    {
        if (grid[linha][coluna] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::LimparLinha(int linha)
{
    for (int coluna = 0; coluna < numColunas; coluna++)
    {
        grid[linha][coluna] = 0;
    }
}

void Grid::DescerLinha(int linha, int numLinhas)
{
    for (int coluna = 0; coluna < numColunas; coluna++)
    {
        grid[linha + numLinhas][coluna] = grid[linha][coluna];
        grid[linha][coluna] = 0;
    }
}