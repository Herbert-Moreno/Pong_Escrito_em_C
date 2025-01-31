#pragma once
#include <raylib.h>
#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct paddle {
  float speed;
  int score;
  Vector2 position;
  Vector2 size;
  Color color;
} Paddle;

typedef struct ball {
  Vector2 speed;
  float radius;
  Vector2 position;
  Vector2 size;
  int rndballdir[2];
  Color color;
} Ball;

void game_init(Paddle *player, Paddle *enemy, Ball *ball);
void draw_game(const Paddle *player, const Paddle *enemy, const Ball *ball);
void game_update(Paddle *player, Paddle *enemy, Ball *ball);

#endif //OBJECTS_H
