#include <raylib.h>
#include "jogo.h"   // Arquivo de cabeçalho para a lógica do jogo
#include "cores.h"  // Arquivo de cabeçalho para as definições de cores
#include <iostream> // Biblioteca padrão para entrada/saída de dados (não usada diretamente aqui)
#include <math.h>


// Variáveis globais para controle de tempo e nível do jogo
double ultimaAttTempo = 0;     // Armazena o tempo da última atualização de evento
double intervaloDescida = 1.0; // Intervalo inicial para a peça descer (em segundos)
bool jogoIniciado{};
bool jogoComecou{};
void DesenharMenu(Font fonte);
void EncerrarJogo(Font fonte);

// Função para verificar se um evento deve ser acionado baseado em um intervalo de tempo
bool eventoAcionado(double intervalo)
{
    double tempoAtual = GetTime();                // Obtém o tempo atual em segundos desde o início do jogo
    if (tempoAtual - ultimaAttTempo >= intervalo) // Verifica se o intervalo foi excedido
    {
        ultimaAttTempo = tempoAtual; // Atualiza o tempo da última atualização
        return true;                 // Evento acionado
    }
    return false; // Evento não acionado
}

int main()
{
    // Inicializa a janela do jogo com tamanho 500x620 e título "TETRIS"
    InitWindow(500, 620, "TETRIS");
    SetTargetFPS(60); // Define o limite de frames por segundo para 60

    // Carrega uma fonte customizada para o texto do jogo
    Font fonte = LoadFontEx("Font/pressstart2p.ttf", 64, 0, 0);

    // Cria um objeto da classe Jogo que gerencia a lógica do jogo
    Jogo jogo = Jogo();

    // Loop principal do jogo
    while (WindowShouldClose() == false) // Enquanto a janela não for fechada
    {

        if (!jogoIniciado)
        {
            // Desenha o menu
            DesenharMenu(fonte);
        }

        // Atualiza o fluxo de música para evitar travamentos ou loops incompletos
        UpdateMusicStream(jogo.musica);

        // Lida com a entrada do jogador, como teclas pressionadas
        jogo.TratarEntrada();

        // Verifica se o evento de descida da peça deve ser acionado
        if (eventoAcionado(intervaloDescida))
        {
            jogo.DescerBloco(); // Faz a peça atual descer uma posição
        }

        // Atualiza o nível do jogo e ajusta o intervalo com base na pontuação
        if (jogo.totalLinhas >= jogo.nivel * 10) // Cada 10 linhas limpas, aumenta o nível
        {
            printf("Aumentou o nível");
            jogo.nivel++;            // Incrementa o nível
            intervaloDescida *= 0.9; // Reduz o intervalo em 10% para acelerar o jogo
        }

        // Começa a renderização da tela
        BeginDrawing();
        ClearBackground(cinzaEscuro); // Define a cor de fundo como cinza claro

        // Desenha o texto "SCORE" no topo direito da tela
        DrawTextEx(fonte, "SCORE", {330, 10}, 38, 2, WHITE);

        // Desenha o texto "NEXT" indicando a área de próxima peça
        DrawTextEx(fonte, "NEXT", {330, 150}, 38, 2, WHITE);

        // Desenha o texto "HOLD" indicando a área de próxima peça
        DrawTextEx(fonte, "HOLD", {330, 385}, 38, 2, WHITE);

        // Se o jogo estiver em estado de "game over", exibe o texto "GAME OVER"
        if (jogo.gameOver)
        {
            EncerrarJogo(fonte);
            jogo.Reset();
        }    void Reset();

        // Desenha a área do placar (score) como um retângulo arredondado
        DrawRectangleRounded({320, 50, 170, 60}, 0.2, 6, BLACK);

        // Converte a pontuação atual para texto e centraliza na área do placar
        char scoreTexto[10];
        sprintf(scoreTexto, "%d", jogo.score);                          // Converte o score para uma string
        Vector2 tamanhoTexto = MeasureTextEx(fonte, scoreTexto, 38, 2); // Mede o tamanho do texto

        // Desenha o texto da pontuação no centro da área do placar
        DrawTextEx(fonte, scoreTexto, {320 + (170 - tamanhoTexto.x) / 2, 65}, 38, 2, WHITE);

        // Desenha a área de "próxima peça" como um retângulo arredondado
        DrawRectangleRounded({320, 190, 170, 180}, 0.1, 6, BLACK);

        // Desenha a área de "próxima peça" como um retângulo arredondado
        DrawRectangleRounded({320, 425, 170, 180}, 0.1, 6, BLACK);

        // Chama o método de desenho do objeto jogo, responsável por desenhar o estado atual do jogo
        jogo.Draw();

        // Finaliza a renderização da tela
        EndDrawing();
    }

    // Fecha a janela do jogo e libera os recursos alocados
    CloseWindow();
}

void DesenharMenu(Font fonte)
{
    // Tamanho do botão
    Rectangle botaoJogar = {115, 400, 280, 50}; // Posição e tamanho do botão "Jogar"
    Rectangle botaoSair = {115, 470, 280, 50};  // Posição e tamanho do botão "Sair"

    // Variáveis para armazenar a cor dos botões
    Color corBotaoJogar = BLUE;
    Color corBotaoSair = RED;

    // Enquanto o jogo não começou, mantém o menu visível
    while (!jogoComecou)
    {
        Color DARKRED = {139, 0, 0, 255};
        Color MIDNIGHTBLUE = {25, 25, 112, 255}; // Azul escuro

        // Obtém a posição do mouse
        Vector2 posicaoMouse = GetMousePosition();

        // Muda a cor do botão "Jogar" se o mouse estiver sobre ele
        if (CheckCollisionPointRec(posicaoMouse, botaoJogar))
        {
            corBotaoJogar = DARKBLUE; // Cor escura quando o mouse está sobre o botão
        }
        else
        {
            corBotaoJogar = BLUE; // Cor normal do botão
        }

        // Muda a cor do botão "Sair" se o mouse estiver sobre ele
        if (CheckCollisionPointRec(posicaoMouse, botaoSair))
        {
            corBotaoSair = DARKRED; // Cor escura quando o mouse está sobre o botão
        }
        else
        {
            corBotaoSair = RED; // Cor normal do botão
        }

        // Limpa a tela e coloca o fundo em uma cor agradável
        BeginDrawing();
        ClearBackground(MIDNIGHTBLUE); // Cor de fundo do menu

        // Desenha o título do jogo no centro da tela
        DrawTextEx(fonte, "TETRIS", {125, 100}, 64, 2, WHITE);

        // Desenha instruções para o jogador
        DrawTextEx(fonte, "Pressione ENTER para jogar", {30, 250}, 32, 2, WHITE);
        DrawTextEx(fonte, "Pressione ESC para sair", {60, 300}, 32, 2, WHITE);

        // Exibe uma mensagem explicando o objetivo
        DrawTextEx(fonte, "Objetivo: Limpar as linhas!", {90, 350}, 24, 2, LIGHTGRAY);

        // Desenha os botões "Jogar" e "Sair" com a cor atual
        DrawRectangleRec(botaoJogar, corBotaoJogar); // Botão "Jogar"
        DrawRectangleRec(botaoSair, corBotaoSair);   // Botão "Sair"

        // Desenha o texto dentro dos botões
        DrawTextEx(fonte, "JOGAR", {botaoJogar.x + 85, botaoJogar.y + 10}, 32, 2, WHITE);
        DrawTextEx(fonte, "SAIR", {botaoSair.x + 100, botaoSair.y + 10}, 32, 2, WHITE);

        // Fim da renderização
        EndDrawing();

        // Espera pela interação do usuário
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // Detecta clique com o botão esquerdo do mouse
        {
            // Verifica se o clique foi dentro do botão "Jogar"
            if (CheckCollisionPointRec(posicaoMouse, botaoJogar))
            {
                jogoComecou = true; // Inicia o jogo ao clicar no botão "Jogar"
            }

            // Verifica se o clique foi dentro do botão "Sair"
            if (CheckCollisionPointRec(posicaoMouse, botaoSair))
            {
                CloseWindow(); // Fecha a janela ao clicar no botão "Sair"
                exit(0);
            }
        }

        // Verifica se a tecla ENTER foi pressionada para iniciar o jogo
        if (IsKeyPressed(KEY_ENTER))
        {
            jogoComecou = true; // Inicia o jogo ao pressionar ENTER
        }

        // Verifica se a tecla ESC foi pressionada para sair do jogo
        if (IsKeyPressed(KEY_ESCAPE))
        {
            CloseWindow(); // Fecha a janela ao pressionar ESC
            exit(0);
        }
    }
}

void EncerrarJogo(Font fonte)
{

    // Tamanho dos botões
    Rectangle botaoSim = {115, 350, 280, 50}; // Posição e tamanho do botão "Sim"
    Rectangle botaoNao = {115, 420, 280, 50}; // Posição e tamanho do botão "Não"

    // Variáveis para armazenar a cor dos botões
    Color corBotaoSim = BLUE;
    Color corBotaoNao = RED;

    while (true) // Loop até o jogador decidir
    {
        Color DARKRED = {139, 0, 0, 255};            // Vermelho escuro
        Color BACKGROUND_COLOR = {25, 25, 112, 255}; // Azul escuro

        // Obtém a posição do mouse
        Vector2 posicaoMouse = GetMousePosition();

        // Muda a cor do botão "Sim" se o mouse estiver sobre ele
        if (CheckCollisionPointRec(posicaoMouse, botaoSim))
        {
            corBotaoSim = DARKBLUE;
        }
        else
        {
            corBotaoSim = BLUE;
        }

        // Muda a cor do botão "Não" se o mouse estiver sobre ele
        if (CheckCollisionPointRec(posicaoMouse, botaoNao))
        {
            corBotaoNao = DARKRED;
        }
        else
        {
            corBotaoNao = RED;
        }

        // Renderiza a tela
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR); // Fundo

        // Mensagem de decisão
        DrawTextEx(fonte, "Deseja jogar novamente?", {60, 250}, 32, 2, WHITE);

        // Botões
        DrawRectangleRec(botaoSim, corBotaoSim); // Botão "Sim"
        DrawRectangleRec(botaoNao, corBotaoNao); // Botão "Não"

        // Texto dentro dos botões
        DrawTextEx(fonte, "SIM", {botaoSim.x + 100, botaoSim.y + 10}, 32, 2, WHITE);
        DrawTextEx(fonte, "NÃO", {botaoNao.x + 100, botaoNao.y + 10}, 32, 2, WHITE);

        EndDrawing();

        // Detecta clique com o mouse
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(posicaoMouse, botaoSim))
            {
                jogoComecou = true; // Reinicia o jogo
                break;              // Sai do loop e volta ao menu inicial
            }
            if (CheckCollisionPointRec(posicaoMouse, botaoNao))
            {
                CloseWindow(); // Fecha a janela e encerra o jogo
                exit(0);
            }
        }

        // Alternativa com o teclado
        if (IsKeyPressed(KEY_ENTER)) // ENTER para jogar novamente
        {
            jogoComecou = true;
            break;
        }
        if (IsKeyPressed(KEY_ESCAPE)) // ESC para sair
        {
            CloseWindow();
            exit(0);
        }
    }
}
