#include "stdio.h"
#include "raylib.h"

unsigned int ScreenWidth = 960;
unsigned int ScreenHeight = 540;

int width = 15;
int height = 100;
float speed = 3.4;
int ballradius = 10;
int ballspeedy = 4;
int ballspeedx = 4;
int rndballdir[2] = {-1, 1};
int playerscore = 0;
int enemyscore = 0;

void update(float *pPlayerposx, float *pPlayerposy, float *pEnemyposx, float *pEnemyposy, float *pBallposx, float *pBallposy);

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
	// chama a função update e passa os endereços da memoria de cada variável nos parâmetros
        update(&playerposx, &playerposy, &enemyposx, &enemyposy, &ballposx, &ballposy);

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
            // desenha o placar do player
            DrawText(TextFormat("%i", playerscore), ScreenWidth / 4 - 20, 20, 60, RAYWHITE);
            // desenha o placar do inimigo
            DrawText(TextFormat("%i", enemyscore), 3 * ScreenWidth / 4 - 20, 20, 60, RAYWHITE);
            // desenha a linha que corta o meio
            DrawRectangle(ScreenWidth / 2, 10, 2, ScreenHeight - 20, RAYWHITE);
        EndDrawing();
    }

    // quando o while for falso a função Close irá fechar a tela
    CloseWindow();

    return 0;
}

// Atualiza variaveis dos objetos na tela
void update(float *pPlayerposx, float *pPlayerposy, float *pEnemyposx, float *pEnemyposy, float *pBallposx, float *pBallposy){
    // atualização do player
    if (IsKeyDown(KEY_W) && *pPlayerposy >= 10)
    {
        *pPlayerposy -= speed;
    }
    else if (IsKeyDown(KEY_S) && *pPlayerposy <= (ScreenHeight - height - 10))
    {
        *pPlayerposy += speed;
    };

    // atualização da bola
    *pBallposx += ballspeedx;
    *pBallposy += ballspeedy;

    if (*pBallposy >= ScreenHeight)
    {
        ballspeedy *= -1;  // Inverte a direção vertical (bola sobe)
        *pBallposy = ScreenHeight;  // Impede que a bola ultrapasse a tela
    }
    else if (*pBallposy <= 0)
    {
        ballspeedy *= -1;  // Inverte a direção vertical (bola desce)
        *pBallposy = 0;     // Impede que a bola ultrapasse a tela
    }

    // se tocar no canto da parede é ponto para um dos lados
    else if (*pBallposx >= (ScreenWidth + ballradius))
    {
        *pBallposx = ScreenWidth / 2; // reseta a posição x da bola para o meio da tela
        *pBallposy = ScreenHeight / 2; // reseta a posição y da bola para o meio da tela
        ballspeedx *= rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo x da bola
        ballspeedy *= rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo y da bola
        playerscore += 1; // aumenta o placar do player
        ballspeedx = 4; // reseta a velocidade da bola
        ballspeedy = 4; // reseta a velocidade da bola
    }
    else if (*pBallposx <= -ballradius)
    {
        *pBallposx = ScreenWidth / 2; // reseta a posição x da bola para o meio da tela
        *pBallposy = ScreenHeight / 2; // reseta a posição y da bola para o meio da tela
        ballspeedx *= rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo x da bola
        ballspeedy *= rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo y da bola
        enemyscore += 1; // aumenta o placar do player
        ballspeedx = 4; // reseta a velocidade da bola
        ballspeedy = 4; // reseta a velocidade da bola
    };

    //atualizar inimigo
    if (*pEnemyposy + height/2 > *pBallposy && *pEnemyposy >= 10)
    {
        *pEnemyposy -= speed;
    }
    else if (*pEnemyposy + height / 2 <= *pBallposy && *pEnemyposy <= (ScreenHeight - height - 10))
    {
        *pEnemyposy += speed;
    };

    // checar colisão da bola com player e inimigo
    Vector2 vec2ball = {*pBallposx, *pBallposy}; // cria um array de vetor 2 para as posições da bola
    Rectangle paddleplayer = {*pPlayerposx, *pPlayerposy, width, height}; // cria a colisão do player
    Rectangle paddleenemy = {*pEnemyposx, *pEnemyposy, width, height}; // cria a colisão do inimigo
    if (CheckCollisionCircleRec(vec2ball, ballradius, paddleplayer)) // checa se houve colisão com o player
    {
        ballspeedx = ballspeedx * 1.2; // aumenta a velocidade da bola 
        ballspeedy = ballspeedy * 1.2; // aumenta a velocidade da bola 
        ballspeedx *= -1; // inverte a direção do eixo horizontal da bola
    }
    else if (CheckCollisionCircleRec(vec2ball, ballradius, paddleenemy)) // checa se houve colisão com o inimigo
    {
        ballspeedx = ballspeedx * 1.2;
        ballspeedy = ballspeedy * 1.2;
        ballspeedx *= -1; // inverte a direção do eixo horizontal da bola
    }
}