#pragma once
#include <vector>
#include <map>
#include "posicao.h"
#include "cores.h"

class Bloco
{
public:
    Bloco();
    void Desenhar(int deslocamentoX, int deslocamentoY);
    std::vector<Posicao> GetCellPositions();
    void ReinicioPeca(int id);
    int estadoRotacao = 0;
    int id;
    /* O MAP vai armazenar as chaves para acessar CADA bloco */
    std::map<int, std::vector<Posicao>> celulas;
    int deslocamentoLinha = 0;
    int deslocamentoColuna = 0;

private:
    /* tamanhoCelula é corresponte ao tamanho da célula que está CAINDO!!! */
    /* O bloco descendo NÃO está diretamente ligado à MATRIZ */
    int tamanhoCelula = 30;
    std::vector<Color> cores;
};