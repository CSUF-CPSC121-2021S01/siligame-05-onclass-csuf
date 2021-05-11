#include "cpputils/graphics/image.h"

#ifndef GAME_ELEMENT
#define GAME_ELEMENT

class GameElement {
 public:
  GameElement() {
    x_ = 0;
    y_ = 0;
    width_ = 50;
    height_ = 50;
  }
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  virtual void Draw(graphics::Image &image) = 0;
  virtual void Move(const graphics::Image &image) = 0;
  bool IntersectsWith(GameElement *obj) {
    return !(GetX() > obj->GetX() + obj->GetWidth() ||
             obj->GetX() > GetX() + GetWidth() ||
             GetY() > obj->GetY() + obj->GetHeight() ||
             obj->GetY() > GetY() + GetHeight());
  }
  bool IsOutOfBounds(graphics::Image &image) {
    if (x_ + width_ > image.GetWidth() || y_ + height_ > image.GetHeight() ||
        x_ < 0 || y_ < 0) {
      return true;
    } else {
      return false;
    }
  }

  // variable modifications
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  bool GetIsActive() const { return is_active; }
  void SetIsActive(bool state) { is_active = state; }

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active = true;
};

#endif
