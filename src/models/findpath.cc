#include "findpath.h"

#include <limits>
#include <stdexcept>

namespace s21 {
void Path::SetMaze(vector<vector<bool>> wall_matrix_on_right,
                   vector<vector<bool>> wall_matrix_f_below) {
  wall_matrix_on_right_ = wall_matrix_on_right;
  wall_matrix_f_below_ = wall_matrix_f_below;
  size_y_ = wall_matrix_f_below_.size();
  size_x_ = wall_matrix_f_below_[0].size();
  visited_.resize(size_y_, vector<bool>(size_x_));
}

int Path::FindShortestPathLength() {
  if (!size_x_ || !size_y_) throw std::runtime_error("Matrix is not set");
  int min_dist = std::numeric_limits<int>::max();
  std::list<std::pair<std::size_t, std::size_t>> path;
  FindShortestPath(src.first, src.second, dest.first, dest.second, min_dist, 0,
                   path);
  if (min_dist == std::numeric_limits<int>::max()) min_dist = -1;
  return min_dist;
}

void Path::FindShortestPath(
    std::size_t i, std::size_t j, std::size_t y, std::size_t x, int &min_dist,
    int dist, std::list<std::pair<std::size_t, std::size_t>> &path) {
  // если место назначения найдено, обновить `min_dist`
  if (i == y && j == x) {
    if (dist < min_dist) {
      min_dist = std::min(dist, min_dist);
      path.push_back(std::make_pair(y, x));
      path_ = path;
    }
    return;
  }
  visited_[i][j] = true;  //  установить (i, j) ячейку как посещенную
  path.push_back(std::make_pair(i, j));
  // переходим в нижнюю ячейку
  if (IsSafeDown(i + 1, j)) {
    FindShortestPath(i + 1, j, y, x, min_dist, dist + 1, path);
  }
  // переходим в правую ячейку
  if (IsSafeRight(i, j + 1)) {
    FindShortestPath(i, j + 1, y, x, min_dist, dist + 1, path);
  }
  // переходим в верхнюю ячейку
  if (IsSafeUp(i - 1, j)) {
    FindShortestPath(i - 1, j, y, x, min_dist, dist + 1, path);
  }
  // переходим в левую ячейку
  if (IsSafeLeft(i, j - 1)) {
    FindShortestPath(i, j - 1, y, x, min_dist, dist + 1, path);
  }
  // возврат: удалить (i, j) из посещенной матрицы
  visited_[i][j] = false;
  path.pop_back();
}

// Проверяем, можно ли перейти в (x, y) из текущей позиции.
// функция возвращает false, если ячейка имеет значение 1 или уже посещена
bool Path::IsSafeDown(std::size_t y, std::size_t x) {
  return (y < size_y_ && x < size_x_) && y != 0 && !visited_[y][x] &&
         wall_matrix_f_below_[y - 1][x] != 1;
}

bool Path::IsSafeUp(std::size_t y, std::size_t x) {
  return (y < size_y_ && x < size_x_) && !visited_[y][x] &&
         wall_matrix_f_below_[y][x] != 1;
}

bool Path::IsSafeRight(std::size_t y, std::size_t x) {
  return (y < size_y_ && x < size_x_) && x != 0 && !visited_[y][x] &&
         wall_matrix_on_right_[y][x - 1] != 1;
}

bool Path::IsSafeLeft(std::size_t y, std::size_t x) {
  return (y < size_y_ && x < size_x_) && !visited_[y][x] &&
         wall_matrix_on_right_[y][x] != 1;
}
}  // namespace s21
