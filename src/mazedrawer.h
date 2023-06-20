#ifndef MAZEDRAWER_H
#define MAZEDRAWER_H
#include <QBrush>
#include <QPen>
#include <QVector2D>

#include "drawerbase.h"
#include "findpath.h"

namespace s21 {
class MazeDrawer : public DrawerBase {
 public:
  MazeDrawer() = delete;
  explicit MazeDrawer(DrawerView &parent);
  MazeDrawer(DrawerView &parent,
             std::vector<std::vector<bool>> *maze_vert_walls,
             std::vector<std::vector<bool>> *maze_hor_walls);
  void SetWalls(std::vector<std::vector<bool>> *maze_vert_walls,
                std::vector<std::vector<bool>> *maze_hor_walls);
  void Draw() override;

 protected:
  void ResizeEvent(QResizeEvent *event) override;
  void MouseReleaseEvent(QMouseEvent *event) override;

 private:
  void RecalculateWallLength();
  void DrawWalls(QPainter &painter, std::vector<std::vector<bool>> *matrix,
                 Qt::Orientation orient);
  void DrawPath(QPainter &painter);

  Path path_finder_{};
  QVector2D maze_wall_length_ = {0, 0};
  std::pair<QPoint, QPoint> path_start_end_;
  std::list<std::pair<std::size_t, std::size_t>> path_;
  std::vector<std::vector<bool>> *maze_vert_walls_ = nullptr;
  std::vector<std::vector<bool>> *maze_hor_walls_ = nullptr;
};
}  // namespace s21
#endif  // MAZEDRAWER_H
