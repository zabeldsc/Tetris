#include "cores.h"

const Color preto = {0, 0, 0, 255};
const Color verde = {0, 255, 0, 255};
const Color vermelho = {255, 0, 0, 255};
const Color laranja = {255, 165, 0, 255};
const Color amarelo = {255, 255, 0, 255};
const Color roxo = {128, 0, 128, 255};
const Color ciano = {0, 255, 255, 255};
const Color cinzaEscuro = {100, 100, 100, 255};
const Color azul = {0, 0, 255, 255};
const Color DARKRED = {139, 0, 0, 255};         
const Color MIDNIGHTBLUE = {25, 25, 112, 255}; 

/* Isso aqui é um vetor de Structs! Cada cor é um Struct com os atributos Red, Green, Blue e Opacidade! */
std::vector<Color> GetCoresCelulas()
{
    return {preto, verde, vermelho, laranja, amarelo, roxo, ciano, azul};
}