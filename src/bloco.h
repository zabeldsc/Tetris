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
    int estadoRotacao;
    int id;
    /* O MAP vai armazenar as chaves para acessar CADA bloco */
    std::map<int, std::vector<Posicao>> celulas;
    int deslocamentoLinha;
    int deslocamentoColuna;

private:
    /* tamanhoCelula é corresponte ao tamanho da célula que está CAINDO!!! */
    /* O bloco descendo NÃO está diretamente ligado à MATRIZ */
    int tamanhoCelula;
    std::vector<Color> cores;
};