#include "jogo.h"
#include <random>
#include <time.h>

Jogo::Jogo()
{
    srand(time(NULL));
    grid = Grid();
    blocos = {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    blocoAtual = GetBlocoAleatorio();
    proximoBloco = GetBlocoAleatorio();
}

Bloco Jogo::GetBlocoAleatorio()
{
    /* Se o vetor de blocos estiver vazio, ele enche novamente */
    if (blocos.empty())
    {
        qtdBlocos = 7;
        blocos = {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    }

    /* Ele cria um index aleatório do tamanho de blocos, cria um bloco com esse index aleatório,
    e apaga o bloco que existe naquele index para que não ocorra repetição, depois retorna o bloco */
    int randomIndex = rand() % qtdBlocos;
    qtdBlocos--;
    Bloco block = blocos[randomIndex];
    blocos.erase(blocos.begin() + randomIndex);
    return block;
}

void Jogo::Desenhar()
{
    grid.Desenhar();
    blocoAtual.Desenhar(11, 11);
    switch (proximoBloco.id)
    {
    case 3:
        proximoBloco.Desenhar(255, 260);
        break;
    case 4:
        proximoBloco.Desenhar(255, 250);
        break;
    default:
        proximoBloco.Desenhar(270, 245);
        break;
    }

    switch (blocoHold.id)
    {
    case 3:
        blocoHold.Desenhar(255, 500);
        break;
    case 4:
        blocoHold.Desenhar(255, 490);
        break;
    default:
        blocoHold.Desenhar(270, 485);
        break;
    }
}

void Jogo::TratarEntrada()
{
    switch (GetKeyPressed())
    {
    case KEY_LEFT:
        blocoAtual.deslocamentoColuna--;
        if (BlocoFora() == true || BlocoCabe() == false)
        {
            blocoAtual.deslocamentoColuna++;
        }
        break;
    case KEY_RIGHT:
        blocoAtual.deslocamentoColuna++;
        if (BlocoFora() == true || BlocoCabe() == false)
        {
            blocoAtual.deslocamentoColuna--;
        }
        break;
    case KEY_DOWN:
        DescerBloco();
        score++;
        break;
    case KEY_UP:
        RotacionarBloco();
        break;
    case KEY_SPACE:
        QuedaLivre();
        break;
    case KEY_C:
        GuardarPeca();
    }
}

void Jogo::GuardarPeca()
{
    if (!fezHold)
    {
        if (primeiroHold)
        {
            Bloco auxiliar = blocoHold;
            blocoHold = blocoAtual;
            blocoAtual = auxiliar;
        }
        else
        {
            blocoHold = blocoAtual;
            blocoAtual = proximoBloco;
            proximoBloco = GetBlocoAleatorio();
            primeiroHold = true;
        }

        blocoHold.ReinicioPeca(blocoHold.id);
        fezHold = true;
    }
}

void Jogo::QuedaLivre()
{

    while (BlocoFora() == false && BlocoCabe() == true)
    {
        blocoAtual.deslocamentoLinha++;
        score++;
    }

    score--;
    blocoAtual.deslocamentoLinha--;
    LockBloco();
}

void Jogo::DescerBloco()
{

    blocoAtual.deslocamentoLinha++;
    if (BlocoFora() == true || BlocoCabe() == false)
    {
        blocoAtual.deslocamentoLinha--;
        LockBloco();
    }
}

void Jogo::RotacionarBloco()
{

    blocoAtual.estadoRotacao++;

    if (blocoAtual.estadoRotacao == (int)blocoAtual.celulas.size())
    {
        blocoAtual.estadoRotacao = 0;
    }

    /* Verifica colisões na nova posição */
    if (BlocoFora() == true || BlocoCabe() == false)
    {
        blocoAtual.estadoRotacao--;
        if (blocoAtual.estadoRotacao == -1)
        {
            blocoAtual.estadoRotacao = blocoAtual.celulas.size() - 1;
        }
    }
}

void Jogo::LockBloco()
{
    std::vector<Posicao> tiles = blocoAtual.GetCellPositions();
    for (int i = 0; i < (int)tiles.size(); i++)
    {
        auto celula = tiles[i];
        grid.grid[celula.linha][celula.coluna] = blocoAtual.id;
    }
    blocoAtual = proximoBloco;
    fezHold = false;
    if (BlocoCabe() == false)
    {
        gameOver = true;
    }
    proximoBloco = GetBlocoAleatorio();
    int linhasLimpas = grid.LimparLinhasCheias();
    totalLinhas += linhasLimpas;
    if (linhasLimpas > 0)
    {
        MaisScoreLinha(linhasLimpas);
    }
}

bool Jogo::BlocoCabe()
{
    std::vector<Posicao> tiles = blocoAtual.GetCellPositions();
    for (int i = 0; i < (int)tiles.size(); i++)
    {
        auto celula = tiles[i];
        /* Retorna falso se uma das células conter cor, ou seja, outro bloco */
        if (grid.grid[celula.linha][celula.coluna] != 0)
        {
            return false;
        }
    }
    return true;
}

bool Jogo::BlocoFora()
{
    std::vector<Posicao> tiles = blocoAtual.GetCellPositions();
    for (int i = 0; i < (int)tiles.size(); i++)
    {
        auto celula = tiles[i];
        /* Retorna true se uma das células estiver fora do Grid */
        if (celula.linha < 0 || celula.linha >= grid.numLinhas || celula.coluna < 0 || celula.coluna >= grid.numColunas)
        {
            return true;
        }
    }
    return false;
}

void Jogo::Reset()
{
    grid.Inicializar();
    blocoAtual = GetBlocoAleatorio();
    proximoBloco = GetBlocoAleatorio();
    score = 0;
    gameOver = false;
    blocoHold = {};
    primeiroHold = false;
}

void Jogo::MaisScoreLinha(int linhasDescidas)
{
    switch (linhasDescidas)
    {
    case 1:
        score += 100 * nivel;
        break;
    case 2:
        score += 300 * nivel;
        break;
    case 3:
        score += 500 * nivel;
        break;
    case 4:
        score += 800 * nivel;
        break;
    default:
        break;
    }
}