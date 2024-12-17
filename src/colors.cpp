#include "cores.h"

const Color preto = {0, 0, 0, 255};
const Color verde = {0, 255, 0, 255};
const Color vermelho = {255, 0, 0, 255};
const Color laranja = {255, 165, 0, 255};
const Color amarelo = {255, 255, 0, 255};
const Color roxo = {128, 0, 128, 255};
const Color ciano = {0, 255, 255, 255};
const Color cinzaClaro = {169, 169, 169, 255};
const Color azul = {0, 0, 255, 255};

std::vector<Color> GetCoresCelulas()
{
    return {preto, verde, vermelho, laranja, amarelo, roxo, ciano, azul};
}