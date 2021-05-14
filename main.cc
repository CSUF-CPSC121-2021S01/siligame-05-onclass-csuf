#include "game.h"

int main() {
  Game newgame;
  newgame.Init();
  newgame.Start(newgame.GetGameScreen());
  return 0;
}
