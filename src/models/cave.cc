#include "cave.h"

#include <algorithm>

namespace s21 {
bool Cave::Randpick(void) {
  return (GetRandomInt(0, 100) < fillprob_) ? kTileWall : kTileFloor;
}

void Cave::InitMap(void) {
  unsigned int xi, yi;
  grid_.clear();
  grid_.resize(size_y_, vector<bool>(size_x_));

  for (yi = 1; yi < size_y_ - 1; yi++)
    for (xi = 1; xi < size_x_ - 1; xi++) grid_[yi][xi] = Randpick();

  for (yi = 0; yi < size_y_; yi++)
    grid_[yi][0] = grid_[yi][size_x_ - 1] = kTileWall;
  for (xi = 0; xi < size_x_; xi++)
    grid_[0][xi] = grid_[size_y_ - 1][xi] = kTileWall;
}

unsigned int Cave::Nearby(unsigned int yi, unsigned int xi) {
  unsigned int adjcount = 0;
  // считаем живых вокруг текущей
  unsigned int start_x =
      static_cast<unsigned int>(std::max(static_cast<int>(xi) - 1, 0));
  unsigned int start_y =
      static_cast<unsigned int>(std::max(static_cast<int>(yi) - 1, 0));
  unsigned int end_x = std::min(size_x_ - 1, xi + 1);
  unsigned int end_y = std::min(size_y_ - 1, yi + 1);
  for (unsigned int x = start_x; x <= end_x; x++) {
    for (unsigned int y = start_y; y <= end_y; y++) {
      if (grid_[y][x] == kTileFloor) adjcount++;
    }
  }
  if (grid_[yi][xi] == kTileFloor)  //  живая посчитала саму себя
    adjcount--;
  return adjcount;
}

bool Cave::Generation(void) {
  vector<vector<bool>> grid_next = grid_;
  unsigned int xi, yi;
  for (yi = 0; yi < size_y_; yi++)
    for (xi = 0; xi < size_x_; xi++) {
      unsigned int adjcount = Nearby(yi, xi);
      //  если вокруг живой недостаточно живых - умирает
      if ((adjcount < r1_cutoff_) && (grid_[yi][xi] == kTileFloor))
        grid_next[yi][xi] = kTileWall;
      //  если вокруг мёртвой достаточно живых - оживает
      if ((adjcount > r2_cutoff_) && (grid_[yi][xi] == kTileWall))
        grid_next[yi][xi] = kTileFloor;
    }
  bool result = !(grid_next == grid_);
  grid_ = grid_next;
  return result;
}

void Cave::GenerateFileWithCave(std::string path) {
  if (grid_.empty()) throw std::runtime_error("cave empty");
  std::ofstream fout(path);
  if (!fout.is_open()) {
    throw std::runtime_error("not open");
  } else {
    fout << size_y_ << " " << size_x_ << std::endl;
    for (std::size_t i = 0; i < size_y_; ++i) {
      for (std::size_t j = 0; j < size_x_; ++j) {
        fout << grid_[i][j];
        if (j != size_x_ - 1) fout << " ";
      }
      fout << std::endl;
    }
  }
  fout.close();
}
}  //  namespace s21
