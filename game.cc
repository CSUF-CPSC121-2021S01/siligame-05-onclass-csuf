#include "game.h"

void Game::CreateOpponents() {
  opponents.push_back(std::make_unique<Opponent>(50, 50));
  opponents.push_back(std::make_unique<Opponent>(100, 100));
  opponents.push_back(std::make_unique<Opponent>(150, 150));
  opponents.push_back(std::make_unique<Opponent>(200, 200));
  opponents.push_back(std::make_unique<Opponent>(250, 250));
  opponents.push_back(std::make_unique<Opponent>(300, 300));
  opponents.push_back(std::make_unique<Opponent>(350, 350));
}

void Game::Init() {
  daplaya.SetX(500);
  daplaya.SetY(300);
  screen.AddMouseEventListener(*this);
  screen.AddAnimationEventListener(*this);
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->LaunchProjectile() != nullptr) {
      oprojectiles.push_back(std::move(opponents[i]->LaunchProjectile()));
    }
  }
}

void Game::UpdateScreen() {
  screen.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  for (int i = 0; i < opponents.size(); i++) {
    if (opponents[i]->GetIsActive()) {
      opponents[i]->Draw(screen);
    }
  }
  for (int i = 0; i < oprojectiles.size(); i++) {
    if (oprojectiles[i]->GetIsActive()) {
      oprojectiles[i]->Draw(screen);
    }
  }
  for (int i = 0; i < pprojectiles.size(); i++) {
    if (pprojectiles[i]->GetIsActive()) {
      pprojectiles[i]->Draw(screen);
    }
  }
  if (daplaya.GetIsActive()) {
    daplaya.Draw(screen);
  }
  if (!HasLost()) {
    screen.DrawText(0, 0, std::to_string(score_), 15, graphics::Color(255,0,0));
  } else {
    screen.DrawText(screen.GetWidth()/2, screen.GetHeight()/2, "Game Over", 25, graphics::Color(255,0,0));
  }

}

void Game::RemoveInactive() {
  for (int i = opponents.size() - 1; i >= 0; i--) {
    if (!opponents[i]->GetIsActive()) {
      opponents.erase(opponents.begin()+i);
    }
  }
  for (int i = oprojectiles.size() - 1; i >= 0; i--) {
    if (!oprojectiles[i]->GetIsActive()) {
      oprojectiles.erase(oprojectiles.begin()+i);
    }
  }
  for (int i = pprojectiles.size() - 1; i >= 0; i--) {
    if (!pprojectiles[i]->GetIsActive()) {
      pprojectiles.erase(pprojectiles.begin()+i);
    }
  }
}

void Game::Start(graphics::Image &screen) { screen.ShowUntilClosed(); }

void Game::MoveGameElements() {
  for (int i = 0; i < opponents.size(); i++) {
    opponents[i]->Move(screen);
  }
  for (int i = 0; i < oprojectiles.size(); i++) {
    oprojectiles[i]->Move(screen);
  }
  for (int i = 0; i < pprojectiles.size(); i++) {
    pprojectiles[i]->Move(screen);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponents.size(); i++) {
    if (daplaya.IntersectsWith(opponents[i].get())) {
      daplaya.SetIsActive(false);
      opponents[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < oprojectiles.size(); i++) {
    if (oprojectiles[i]->IntersectsWith(&daplaya)) {
      daplaya.SetIsActive(false);
      oprojectiles[i]->SetIsActive(false);
      lost_ = true;
    }
  }
  for (int i = 0; i < pprojectiles.size(); i++) {
    for (int j = 0; j < opponents.size(); j++) {
      if (pprojectiles[i]->IntersectsWith(opponents[j].get())) {
        pprojectiles[i]->SetIsActive(false);
        opponents[j]->SetIsActive(false);
        if (daplaya.GetIsActive()) {
          score_++;
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if(opponents.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  screen.Flush();
}

void Game::OnMouseEvent(const graphics::MouseEvent &event) {
  event.GetMouseAction();
  if (event.GetX() > 0 && event.GetY() > 0 &&
      event.GetX() < screen.GetWidth() && event.GetY() < screen.GetHeight()) {
    daplaya.SetX(event.GetX() - daplaya.GetWidth() / 2);
    daplaya.SetY(event.GetY() - daplaya.GetHeight() / 2);
    pprojectiles.push_back(std::make_unique<PlayerProjectile>(daplaya.GetX() + 25, daplaya.GetY()));
  }
}
