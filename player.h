#include "cpputils/graphics/image.h"
#include "game_element.h"

#ifndef PLAYER
#define PLAYER

class Opponent;
class OpponentProjectile;

class Player : public GameElement {
 public:
  Player() {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
};
#endif
