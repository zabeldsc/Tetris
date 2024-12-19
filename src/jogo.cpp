#include "jogo.h"
#include <random>
#include <time.h>

Jogo::Jogo()
{
    srand(time(NULL));
    grid = Grid();
    blocks = GetAllBlocks();
    blocoAtual = GetRandomBlock();
    proximoBloco = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    // musica = LoadMusicStream("sons/music.mp3");
    PlayMusicStream(musica);
    rotateSound = LoadSound("sons/rotate.mp3");
    clearSound = LoadSound("sons/clear.mp3");
}

Jogo::~Jogo()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(musica);
    CloseAudioDevice();
}

Bloco Jogo::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Bloco block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Bloco> Jogo::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Jogo::Draw()
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
        blocoHold.Desenhar(345, 500);
        break;
    case 4:
        blocoHold.Desenhar(375, 490);
        break;
    default:
        blocoHold.Desenhar(360, 485);
        break;
    }
}

void Jogo::TratarEntrada()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        DescerBloco();
        UpdateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
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
            proximoBloco = GetRandomBlock();
            primeiroHold = true;
        }

        blocoHold.ReinicioPeca();
        fezHold = true;
    }
}

void Jogo::QuedaLivre()
{
    int celulasDescidas = 0;

    if (!gameOver)
    {
        while (IsBlockOutside() == false && BlockFits() == true)
        {
            blocoAtual.Mover(1, 0);
            celulasDescidas++;
        }

        UpdateScore(0, celulasDescidas);
        blocoAtual.Mover(-1, 0);
        LockBlock();
    }
}

void Jogo::MoveBlockLeft()
{
    if (!gameOver)
    {
        blocoAtual.Mover(0, -1);
        if (IsBlockOutside() == true || BlockFits() == false)
        {
            blocoAtual.Mover(0, 1);
        }
    }
}

void Jogo::MoveBlockRight()
{
    if (!gameOver)
    {
        blocoAtual.Mover(0, 1);
        if (IsBlockOutside() == true || BlockFits() == false)
        {
            blocoAtual.Mover(0, -1);
        }
    }
}

void Jogo::DescerBloco()
{
    if (!gameOver)
    {
        blocoAtual.Mover(1, 0);
        if (IsBlockOutside() == true || BlockFits() == false)
        {
            blocoAtual.Mover(-1, 0);
            LockBlock();
        }
    }
}

bool Jogo::IsBlockOutside()
{
    std::vector<Posicao> tiles = blocoAtual.GetCellPositions();
    for (Posicao item : tiles)
    {
        if (grid.ChecarCelulaFora(item.linha, item.coluna))
        {
            return true;
        }
    }
    return false;
}

void Jogo::RotateBlock()
{
    if (!gameOver)
    {
        blocoAtual.Rotacionar();
        if (IsBlockOutside() == true || BlockFits() == false)
        {
            blocoAtual.DesfazerRotacao();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

void Jogo::LockBlock()
{
    std::vector<Posicao> tiles = blocoAtual.GetCellPositions();
    for (Posicao item : tiles)
    {
        grid.grid[item.linha][item.coluna] = blocoAtual.id;
    }
    blocoAtual = proximoBloco;
    fezHold = false;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    proximoBloco = GetRandomBlock();
    int rowsCleared = grid.LimparLinhasCheias();
    totalLinhas += rowsCleared;
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Jogo::BlockFits()
{
    std::vector<Posicao> tiles = blocoAtual.GetCellPositions();
    for (Posicao item : tiles)
    {
        if (grid.ChecarCelulaVazia(item.linha, item.coluna) == false)
        {
            return false;
        }
    }
    return true;
}

void Jogo::Reset()
{
    grid.Inicializar();
    blocks = GetAllBlocks();
    blocoAtual = GetRandomBlock();
    proximoBloco = GetRandomBlock();
    score = 0;
    gameOver = false;
}

void Jogo::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
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

    score += moveDownPoints;
}