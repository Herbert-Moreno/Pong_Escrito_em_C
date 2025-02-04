#include "stdio.h"
#include <raylib.h>
#include <Objects.h>

#define ScreenWidth 960
#define ScreenHeight 540
#define Quantidade_Maxima_Rastro 10

Vector2 Rastro[Quantidade_Maxima_Rastro]; // Array para armazenar as posições antigas da bola
int IndexRastro = 0; // Índice para armazenar a próxima posição
Color RastroColor = (Color){255, 255, 255, 128}; // cor do rastro com transparência (Alpha 128)

int main(int argc, char *argv[])
{
    Paddle Player;
    Paddle Enemy;
    Ball Ball;

    // chama a função init guarda valores do player inimigo e bola na memoria
    game_init(&Player, &Enemy, &Ball);
    // enquanto a tela não for fechada ele ira rodar o que ta dentro
    while (!WindowShouldClose()) {
        // chama a função update e passa os endereços da memoria de cada variável nos parâmetros
        game_update(&Player, &Enemy, &Ball);
        // chama a função draw e passa os endereços da memoria de cada variável nos parâmetros
        draw_game(&Player, &Enemy, &Ball);
    }
    CloseWindow();
    return 0;
}

//Inicializa a função de iniciar assets e a janela do jogo
void game_init(Paddle *player, Paddle *enemy, Ball *ball) {
    printf("Inicializando Jogo ...\n");

    // Variaveis do PLayer
    player->speed = 3.5f;
    player->size = (Vector2){15, 100};
    player->position = (Vector2){10,(float)ScreenHeight / 2};
    player->score = 0;
    player->color = BLUE;

    //Variaveis do Inimigo
    enemy->speed = 3.5f;
    enemy->size = (Vector2){15, 100};
    enemy->position = (Vector2){(float)ScreenWidth - 20,(float)ScreenHeight / 2};
    enemy->score = 0;
    enemy->color = RED;

    //Variaveis da Bola
    ball->radius = 10;
    ball->size = (Vector2){15, 100};
    ball->position = (Vector2){(float)ScreenWidth / 2,(float)ScreenHeight / 2};
    ball->color = RAYWHITE;
    ball->speed = (Vector2){4, 4};
    ball->rndballdir[0] = -1;
    ball->rndballdir[1] = 1;
    ball->speed.x *= (float)ball->rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo x da bola
    ball->speed.y *= (float)ball->rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo y da bola

    // função de iniciar tela
    InitWindow(ScreenWidth, ScreenHeight, "Pong Ping - The Game");
    // função de setar o fps do jogo
    SetTargetFPS(60);
}

// Atualiza variaveis dos objetos na tela
void game_update(Paddle *player, Paddle *enemy, Ball *ball){
    // atualização do player
    if (IsKeyDown(KEY_UP) && player->position.y >= 0 ||
        IsKeyDown(KEY_W) && player->position.y >= 0)
    {
        player->position.y -= player->speed;
    }
    else if (IsKeyDown(KEY_DOWN) && player->position.y <= (float)ScreenHeight - player->size.y ||
        IsKeyDown(KEY_S) && player->position.y <= (float)ScreenHeight - player->size.y)
    {
        player->position.y += player->speed;
    }

    //atualizar inimigo
    if (ball->position.x >= (float)ScreenWidth/2) {
        if (enemy->position.y + enemy->size.y / 2 >= ball->position.y &&
            enemy->position.y >= 0)
        {
            enemy->position.y -= enemy->speed;
        }
        else if (enemy->position.y + enemy->size.y / 2 <= ball->position.y &&
            enemy->position.y <= ((float)ScreenHeight - enemy->size.y))
        {
            enemy->position.y += enemy->speed;
        }
    }
    // atualização da bola
    ball->position.x += ball->speed.x;
    ball->position.y += ball->speed.y;

    if (ball->position.y >= ScreenHeight)
    {
        ball->speed.y *= -1;  // Inverte a direção vertical (bola sobe)
        ball->position.y = ScreenHeight;  // Impede que a bola ultrapasse a tela
    }
    else if (ball->position.y <= 0)
    {
        ball->speed.y *= -1;  // Inverte a direção vertical (bola desce)
        ball->position.y = 0;     // Impede que a bola ultrapasse a tela
    }

    // se tocar no canto da parede é ponto para um dos lados
    else if (ball->position.x >= (ScreenWidth + ball->radius))
    {
        ball->position.x = (float)ScreenWidth / 2; // reseta a posição x da bola para o meio da tela
        ball->position.y = (float)ScreenHeight / 2; // reseta a posição y da bola para o meio da tela
        ball->speed.x *= (float)ball->rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo x da bola
        ball->speed.y *= (float)ball->rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo y da bola

        player->score += 1; // aumenta o placar do player

        ball->speed.x = 4; // reseta a velocidade da bola
        ball->speed.y = 4; // reseta a velocidade da bola
    }
    else if (ball->position.x <= -ball->radius)
    {
        ball->position.x = (float)ScreenWidth / 2; // reseta a posição x da bola para o meio da tela
        ball->position.y = (float)ScreenHeight / 2; // reseta a posição y da bola para o meio da tela
        ball->speed.x *= (float)ball->rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo x da bola
        ball->speed.y *= (float)ball->rndballdir[GetRandomValue(0, 1)]; // escolhe uma direção aleatoria para o eixo y da bola

        enemy->score += 1; // aumenta o placar do player

        ball->speed.x = 4; // reseta a velocidade da bola
        ball->speed.y = 4; // reseta a velocidade da bola
    }

    // checar colisão da bola com player e inimigo
    Rectangle BallCollisor = {ball->position.x, ball->position.y, ball->radius, ball->radius}; // cria um array de vetor 2 para as posições da bola
    Rectangle PlayerCollisor = {player->position.x, player->position.y, player->size.x, player->size.y}; // cria a colisão do player
    Rectangle EnemyCollisor = {enemy->position.x, enemy->position.y, enemy->size.x, enemy->size.y}; // cria a colisão do inimigo
    if (CheckCollisionRecs(PlayerCollisor, BallCollisor)) // checa se houve colisão com o player
    {
        ball->speed.x += 1.2f; // aumenta a velocidade da bola
        ball->speed.y += 1.2f; // aumenta a velocidade da bola
        ball->speed.x *= -1; // inverte a direção do eixo horizontal da bola
    } else if (CheckCollisionRecs(EnemyCollisor, BallCollisor)) // checa se houve colisão com o inimigo
    {
        ball->speed.x += 1.2f; // aumenta a velocidade da bola
        ball->speed.y += 1.2f; // aumenta a velocidade da bola
        ball->speed.x *= -1; // inverte a direção do eixo horizontal da bola
    }
}

void draw_game(const Paddle *player, const Paddle *enemy, const Ball *ball) {
    Vector2 posicaobola = {ball->position.x, ball->position.y};
    Rastro[IndexRastro] = posicaobola;
    IndexRastro = (IndexRastro + 1) % Quantidade_Maxima_Rastro;  // Avança no índice e volta ao início quando chega ao limite

    // Desenha na tela Funções de Draw
    BeginDrawing();
    // limpa a tela e seta uma cor preta no fundo
    ClearBackground(BLACK);
    // desenha o player
    DrawRectangle((int)player->position.x, (int)player->position.y, (int)player->size.x, (int)player->size.y, player->color);
    // desenha o inimigo
    DrawRectangle((int)enemy->position.x, (int)enemy->position.y, (int)enemy->size.x, (int)enemy->size.y, enemy->color);
    // desenha a bola
    DrawCircle((int)ball->position.x, (int)ball->position.y, ball->radius, ball->color);

    for (int i = 0; i < Quantidade_Maxima_Rastro; i++) {
        int RastroPos = (IndexRastro + i) % Quantidade_Maxima_Rastro;
        if (Rastro[RastroPos].x != 0 && Rastro[RastroPos].y != 0) {
            float opacity = (float)(Quantidade_Maxima_Rastro + i) / Quantidade_Maxima_Rastro;
            Color colorWithOpacity = (Color){RastroColor.r, RastroColor.g, RastroColor.b, (unsigned char)(opacity * 40)};
            DrawCircleV(Rastro[RastroPos], ball->radius - 3, colorWithOpacity);
        }
    }

    // desenha o placar do player
    DrawText(TextFormat("%i", player->score), ScreenWidth / 4 - 20, 20, 60, RAYWHITE);
    // desenha o placar do inimigo
    DrawText(TextFormat("%i", enemy->score), 3 * ScreenWidth / 4 - 20, 20, 60, RAYWHITE);
    // desenha a linha que corta o meio
    DrawRectangle(ScreenWidth / 2, 10, 2, ScreenHeight - 20, RAYWHITE);
    // desenha um circulo que define o meio da quadra
    Vector2 ringpos = {(float)ScreenWidth / 2, (float)ScreenHeight / 2};
    DrawRing(ringpos, 80, 82, 0, 360, 14, WHITE);
    EndDrawing();
}



/*
*/
/*for (int i = 0; i < Quantidade_Maxima_Rastro; i++)
{
    int RastroPos = (IndexRastro + i) % Quantidade_Maxima_Rastro;
    if (Rastro[RastroPos].x != 0 && Rastro[RastroPos].y != 0)
    {
        // O rastro é desenhado com transparência, o primeiro rastro é mais visível
        float opacity = (float)(Quantidade_Maxima_Rastro + i) / Quantidade_Maxima_Rastro;
        Color colorWithOpacity = (Color){RastroColor.r, RastroColor.g, RastroColor.b, (unsigned char)(opacity * 40)};
        DrawCircleV(Rastro[RastroPos], ballradius - 3, colorWithOpacity);
    }
}*/