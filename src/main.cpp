#include <raylib.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <fstream>
#include "jogo.h"
#include "cores.h"

typedef struct
{
    char nome[50];
    int score;
} Jogadores;

Jogadores topJogadores[10] = {};
double ultimaAttTempo = 0;
double intervaloDescida = 1.0;
bool jogoIniciado{};
void DesenharMenu(Font fonte, Jogadores *Jogador);
void EncerrarJogo(Font fonte, Jogadores *Jogador);
void checkRanking(Jogadores *Jogador, int score);
void atualizarRanking();
void getJogadores();
bool eventoAcionado(double intervalo);

int main()
{
    InitWindow(500, 620, "TETRIS");
    SetTargetFPS(60);
    Font fonte = LoadFontEx("Font/pressstart2p.ttf", 64, 0, 0);
    Jogo jogo = Jogo();
    Jogadores jogador;

    while (WindowShouldClose() == false) // Enquanto a janela não for fechada
    {

        if (!jogoIniciado)
        {
            getJogadores();
            DesenharMenu(fonte, &jogador);
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

        BeginDrawing();
        ClearBackground(cinzaEscuro);
        DrawTextEx(fonte, "SCORE", {330, 10}, 38, 2, WHITE);
        DrawTextEx(fonte, "NEXT", {330, 150}, 38, 2, WHITE);
        DrawTextEx(fonte, "HOLD", {330, 385}, 38, 2, WHITE);

        // Se o jogo estiver em estado de "game over", exibe o texto "GAME OVER"
        if (jogo.gameOver)
        {
            checkRanking(&jogador, jogo.score);
            EncerrarJogo(fonte, &jogador);
            jogo.Reset();
            jogoIniciado = false;
            DesenharMenu(fonte, &jogador);
        }

        DrawRectangleRounded({320, 50, 170, 60}, 0.2, 6, BLACK);
        char scoreTexto[10];
        sprintf(scoreTexto, "%d", jogo.score); // Converte o score para uma string
        Vector2 tamanhoTexto = MeasureTextEx(fonte, scoreTexto, 38, 2); // Mede o tamanho do texto
        DrawTextEx(fonte, scoreTexto, {320 + (170 - tamanhoTexto.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 190, 170, 180}, 0.1, 6, BLACK);
        DrawRectangleRounded({320, 425, 170, 180}, 0.1, 6, BLACK);

        jogo.Desenhar();
        EndDrawing();
    }
    
    CloseWindow();
}

void DesenharMenu(Font fonte, Jogadores *Jogador)
{
    // Tamanho do botão
    Rectangle botaoJogar = {115, 430, 280, 50}; // Posição e tamanho do botão "Jogar"
    Rectangle botaoSair = {115, 500, 280, 50};  // Posição e tamanho do botão "Sair"

    // Variáveis para armazenar a cor dos botões
    Color corBotaoJogar = BLUE;
    Color corBotaoSair = RED;

    // Variáveis para o nome do jogador
    char nomeJogador[50] = "";  // Array para armazenar o nome do jogador
    bool textoEditando = false; // Para verificar se o jogador está editando o nome

    // Tamanho da caixa de entrada
    Rectangle caixaTexto = {105, 345, 300, 40}; // Posição e tamanho da caixa de texto

    // Enquanto o jogo não começou, mantém o menu visível
    while (!jogoIniciado)
    {
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
        DrawTextEx(fonte, "Pressione ENTER para jogar", {30, 200}, 32, 2, WHITE);
        DrawTextEx(fonte, "Pressione ESC para sair", {60, 250}, 32, 2, WHITE);

        // Exibe uma mensagem explicando o objetivo
        DrawTextEx(fonte, "Insira seu nome:", {105, 320}, 24, 2, LIGHTGRAY);

        // Desenha a caixa de texto para o nome do jogador (como um campo editável)
        DrawRectangleRec(caixaTexto, LIGHTGRAY);                                              // Caixa de entrada
        DrawTextEx(fonte, nomeJogador, {caixaTexto.x + 10, caixaTexto.y + 10}, 32, 2, BLACK); // Exibe o nome digitado

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
            // Verifica se o clique foi dentro da caixa de texto para editar o nome
            if (CheckCollisionPointRec(posicaoMouse, caixaTexto))
            {
                textoEditando = true; // Começa a editar o nome
            }
            else
            {
                textoEditando = false; // Interrompe a edição se clicar fora da caixa de texto
            }

            // Verifica se o clique foi dentro do botão "Jogar"
            if (CheckCollisionPointRec(posicaoMouse, botaoJogar) && nomeJogador[0] != '\0') // Verifica se o nome foi digitado
            {
                jogoIniciado = true; // Inicia o jogo ao clicar no botão "Jogar"
            }

            // Verifica se o clique foi dentro do botão "Sair"
            if (CheckCollisionPointRec(posicaoMouse, botaoSair))
            {
                CloseWindow(); // Fecha a janela ao clicar no botão "Sair"
                exit(0);
            }
        }

        // Verifica se a tecla ENTER foi pressionada para iniciar o jogo
        if (IsKeyPressed(KEY_ENTER) && nomeJogador[0] != '\0')
        {
            strcpy(Jogador->nome, nomeJogador);
            jogoIniciado = true; // Inicia o jogo ao pressionar ENTER
        }

        // Verifica se a tecla ESC foi pressionada para sair do jogo
        if (IsKeyPressed(KEY_ESCAPE))
        {
            CloseWindow(); // Fecha a janela ao pressionar ESC
            exit(0);
        }

        // Lê as teclas digitadas para o nome do jogador
        if (textoEditando)
        {
            for (int i = 0; i < 255; i++) // Verifica as teclas pressionadas
            {
                if (IsKeyPressed(i) && i >= 32 && i <= 126) // Apenas caracteres visíveis
                {
                    int len = strlen(nomeJogador);
                    if (len < 49) // Limita o tamanho máximo do nome
                    {
                        nomeJogador[len] = (char)i;  // Adiciona o caractere no nome
                        nomeJogador[len + 1] = '\0'; // Finaliza a string
                    }
                }

                if (IsKeyPressed(KEY_BACKSPACE)) // Remove o último caractere
                {
                    int len = strlen(nomeJogador);
                    if (len > 0)
                    {
                        nomeJogador[len - 1] = '\0'; // Remove o último caractere
                    }
                }
            }
        }
    }
}

void getJogadores()
{
    std::ifstream arquivo("/home/isabel/Documents/faculdade/Tetris/ranking.txt");

    if (!arquivo)
    {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return;
    }

    int i = 0;
    while (arquivo >> topJogadores[i].nome >> topJogadores[i].score && i < 10)
    {
        i++;
    }

    arquivo.close();

    // Exibir os jogadores lidos (opcional)
    for (int j = 0; j < i; j++)
    {
        std::cout << "Nome: " << topJogadores[j].nome
                  << ", Pontuação: " << topJogadores[j].score << std::endl;
    }
}

void EncerrarJogo(Font fonte, Jogadores *Jogador)
{
    // Tamanho dos botões
    Rectangle botaoSim = {115, 350, 280, 50}; // Posição e tamanho do botão "Sim"
    Rectangle botaoNao = {115, 420, 280, 50}; // Posição e tamanho do botão "Não"

    // Variáveis para armazenar a cor dos botões
    Color corBotaoSim = BLUE;
    Color corBotaoNao = RED;

    while (true) // Loop até o jogador decidir
    {
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
        ClearBackground(MIDNIGHTBLUE); // Fundo

        DrawTextEx(fonte, "GAME OVER!", {100, 100}, 50, 2, WHITE);

        // Mensagem de decisão
        DrawTextEx(fonte, "Deseja jogar novamente?", {60, 250}, 32, 2, WHITE);

        // Botões
        DrawRectangleRec(botaoSim, BLUE); // Botão "Sim"
        DrawRectangleRec(botaoNao, RED);  // Botão "Não"

        // Texto dentro dos botões
        DrawTextEx(fonte, "SIM", {botaoSim.x + 100, botaoSim.y + 10}, 32, 2, WHITE);
        DrawTextEx(fonte, "NÃO", {botaoNao.x + 100, botaoNao.y + 10}, 32, 2, WHITE);

        EndDrawing();

        // Detecta clique com o mouse
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(posicaoMouse, botaoSim))
            {
                jogoIniciado = true; // Reinicia o jogo
                break;               // Sai do loop e volta ao menu inicial
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
            jogoIniciado = true;
            break;
        }
        if (IsKeyPressed(KEY_ESCAPE)) // ESC para sair
        {
            CloseWindow();
            exit(0);
        }
    }
}

void checkRanking(Jogadores *Jogador, int score)
{
    for (int i = 0; i < 10; i++)
    {
        if (score > topJogadores[i].score)
        {
            // Desloca os jogadores para baixo
            for (int j = 9; j > i; j--)
            {
                // Desloca para a próxima posição
                strcpy(topJogadores[j].nome, topJogadores[j - 1].nome);
                topJogadores[j].score = topJogadores[j - 1].score;
            }

            // Insere o novo jogador na posição correta
            strcpy(topJogadores[i].nome, Jogador->nome);
            topJogadores[i].score = score;
            atualizarRanking();
            break; // Sai do loop após a inserção
        }
    }
}

// Função para atualizar o ranking no arquivo
void atualizarRanking()
{
    // Abre o arquivo para escrita (sobrescreve se já existir)
    FILE *arquivo = fopen("ranking.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve os dados dos jogadores no arquivo
    for (int i = 0; i < 10; i++)
    {
        fprintf(arquivo, "%s %d\n", topJogadores[i].nome, topJogadores[i].score);
    }

    // Fecha o arquivo
    fclose(arquivo);

    printf("Ranking atualizado com sucesso!\n");
}

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