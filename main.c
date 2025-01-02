#include "stdio.h"
#include "raylib.h"

unsigned int ScreenWidth = 960;
unsigned int ScreenHeight = 540;

int width = 15;
int height = 100;
int ballradius = 10;
int ballspeedy = 4;
int ballspeedx = 4;
int playerscore = 0;
int enemyscore = 0;

int main(int argc, char *argv[])
{
    // posição do player
    float playerposx = 10;
    float playerposy = ScreenHeight / 2 - height / 2;

    // posição do inimigo
    float enemyposx = ScreenWidth - 20;
    float enemyposy = ScreenHeight / 2 - height / 2;

    // posição da bola
    float ballposx = ScreenWidth / 2;
    float ballposy = ScreenHeight / 2;

    // função de iniciar tela
    InitWindow(ScreenWidth, ScreenHeight, "Pong Ping - The Game");
    // função de setar o fps do jogo
    SetTargetFPS(60);

    // enquanto a tela não for fechada ele ira rodar o que ta dentro
    while (!WindowShouldClose())
    {   
        // Desenha na tela Funções de Draw
        BeginDrawing();
            // limpa a tela e seta uma cor preta no fundo
            ClearBackground(BLACK);
            // desenha o player
            DrawRectangle(playerposx, playerposy, width, height, BLUE);
            // desenha o inimigo
            DrawRectangle(enemyposx, enemyposy, width, height, RED);
            // desenha a bola
            DrawCircle(ballposx, ballposy, ballradius, WHITE);
        EndDrawing();
    }

    // quando o while for falso a função Close irá fechar a tela
    CloseWindow();

    return 0;
}
