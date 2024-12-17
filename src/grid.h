#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Inicializar();
    void Desenhar();
    bool ChecarCelulaFora(int linha, int coluna);
    bool ChecarCelulaVazia(int linha, int coluna);
    int LimparLinhasCheias();
    int grid[20][10];

private:
    bool LinhaCheia(int linha);
    void LimparLinha(int linha);
    void DescerLinha(int linha, int numLinhas);
    int numLinhas;
    int numColunas;
    int tamCelula;
    std::vector<Color> cores;
};