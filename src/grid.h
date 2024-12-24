#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    void Inicializar();
    void Desenhar();
    int LimparLinhasCheias();
    int grid[20][10];
    int numLinhas = 20;
    int numColunas = 10;

private:
    int tamCelula = 30;
    std::vector<Color> cores;
};