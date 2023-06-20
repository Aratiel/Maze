#include <list>
#include <vector>

using std::vector;

namespace s21 {
class Path {
 public:
  void SetMaze(vector<vector<bool>> wall_matrix_on_right,
               vector<vector<bool>> wall_matrix_f_below);
  void SetStart(int x, int y) { src = std::make_pair(y, x); }
  void SetFinish(int x, int y) { dest = std::make_pair(y, x); }
  std::list<std::pair<std::size_t, std::size_t>> GetPath() { return path_; }
  // Обертка над функцией findShortestPath()
  int FindShortestPathLength();

 private:
  vector<vector<bool>> wall_matrix_on_right_;
  vector<vector<bool>> wall_matrix_f_below_;
  vector<vector<bool>> visited_;
  std::list<std::pair<std::size_t, std::size_t>> path_;

  std::pair<std::size_t, std::size_t> src;
  std::pair<std::size_t, std::size_t> dest;
  std::size_t size_y_, size_x_;

  // Находим кратчайший путь в матрице `mat` из исходной ячейки (i, j)
  // в ячейку назначения (x, y).

  // `min_dist` передается по ссылке и хранит длину самого длинного пути
  // от источника к месту назначения, найденному до сих пор, и `dist`
  // поддерживает длину пути от исходной ячейки к текущей ячейке (i, j).
  void FindShortestPath(std::size_t i, std::size_t j, std::size_t y,
                        std::size_t x, int &min_dist, int dist,
                        std::list<std::pair<std::size_t, std::size_t>> &path);
  // Проверяем, можно ли перейти в (x, y) из текущей позиции.
  // функция возвращает false, если ячейка имеет значение 1 или уже посещена
  bool IsSafeDown(std::size_t y, std::size_t x);
  bool IsSafeUp(std::size_t y, std::size_t x);
  bool IsSafeRight(std::size_t y, std::size_t x);
  bool IsSafeLeft(std::size_t y, std::size_t x);
};
}  // namespace s21
