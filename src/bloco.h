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
    void Mover(int linhas, int colunas);
    std::vector<Posicao> GetCellPositions();
    void Rotacionar();
    void DesfazerRotacao();
    void ReinicioPeca();
    int id;
    std::map<int, std::vector<Posicao>> celulas;

private:
    int tamanhoCelula;
    int estadoRotacao;
    std::vector<Color> cores;
    int deslocamentoLinha;
    int deslocamentoColuna;
};