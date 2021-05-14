#include "cpputils/graphics/image.h"
#include "game_element.h"

#include <memory>

#ifndef OPPONENT
#define OPPONENT

class Opponent : public GameElement {
 public:
  Opponent() {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
  std::unique_ptr<class OpponentProjectile> LaunchProjectile();
  int counter = 0;
};

class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}
  void Draw(graphics::Image &image) override;
  void Move(const graphics::Image &image) override;
};
#endif
