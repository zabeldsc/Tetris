#include <raylib.h>
#include "jogo.h"  // Arquivo de cabeçalho para a lógica do jogo
#include "cores.h" // Arquivo de cabeçalho para as definições de cores
#include <iostream> // Biblioteca padrão para entrada/saída de dados (não usada diretamente aqui)

// Variáveis globais para controle de tempo e nível do jogo
double ultimaAttTempo = 0;       // Armazena o tempo da última atualização de evento
double intervaloDescida = 1.0;  // Intervalo inicial para a peça descer (em segundos)


// Função para verificar se um evento deve ser acionado baseado em um intervalo de tempo
bool eventoAcionado(double intervalo)
{
    double tempoAtual = GetTime(); // Obtém o tempo atual em segundos desde o início do jogo
    if (tempoAtual - ultimaAttTempo >= intervalo) // Verifica se o intervalo foi excedido
    {
        ultimaAttTempo = tempoAtual; // Atualiza o tempo da última atualização
        return true; // Evento acionado
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
            jogo.nivel++;                     // Incrementa o nível
            intervaloDescida *= 0.9;     // Reduz o intervalo em 10% para acelerar o jogo
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
            DrawTextEx(fonte, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }

        // Desenha a área do placar (score) como um retângulo arredondado
        DrawRectangleRounded({320, 50, 170, 60}, 0.2, 6, BLACK);

        // Converte a pontuação atual para texto e centraliza na área do placar
        char scoreTexto[10];
        sprintf(scoreTexto, "%d", jogo.score); // Converte o score para uma string
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
