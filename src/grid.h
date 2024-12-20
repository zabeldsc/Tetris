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
        int numLinhas;
    int numColunas;

private:
    int tamCelula;
    std::vector<Color> cores;
};