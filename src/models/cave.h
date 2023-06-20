#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

namespace s21 {
class Cave {
 public:
  Cave() {}
  ~Cave() {}
  void InitMap(void);  //  инициализация (рандомная) пещеры
  bool Generation(void);  //  очередной шаг генерации: true пока есть изменения
  void SetGrid(vector<vector<bool>> grid) { grid_ = grid; }
  void SetSize(unsigned int y, unsigned int x) {
    size_y_ = y;
    size_x_ = x;
  }
  void SetCutoff(unsigned int r1_cutoff, unsigned int r2_cutoff) {
    r1_cutoff_ = r1_cutoff;
    r2_cutoff_ = r2_cutoff;
  }
  void GenerateFileWithCave(std::string path);
  vector<vector<bool>> &GetGrid() { return grid_; }

 private:
  static const bool constexpr kTileFloor = 0;
  static const bool constexpr kTileWall = 1;
  vector<vector<bool>> grid_;
  int fillprob_ = 40;
  unsigned int r1_cutoff_ = 4, r2_cutoff_ = 4;
  unsigned int size_x_ = 20, size_y_ = 10;

  bool Randpick(void);
  unsigned int Nearby(unsigned int yi, unsigned int xi);
  int GetRandomInt(int rand_min, int rand_max) {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> distrib(rand_min, rand_max);
    return distrib(gen);
  }
};
}  // namespace s21
