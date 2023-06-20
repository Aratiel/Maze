#include "mazedrawer.h"

#include <QMouseEvent>

namespace s21 {

MazeDrawer::MazeDrawer(DrawerView &parent) : DrawerBase(parent) {}

MazeDrawer::MazeDrawer(DrawerView &parent,
                       std::vector<std::vector<bool>> *maze_vert_walls,
                       std::vector<std::vector<bool>> *maze_hor_walls)
    : DrawerBase(parent) {
  SetWalls(maze_vert_walls, maze_hor_walls);
}

void MazeDrawer::SetWalls(std::vector<std::vector<bool>> *maze_vert_walls,
                          std::vector<std::vector<bool>> *maze_hor_walls) {
  maze_vert_walls_ = maze_vert_walls;
  maze_hor_walls_ = maze_hor_walls;
  RecalculateWallLength();
  path_start_end_.first = QPoint(-1, -1);
  path_start_end_.second = QPoint(-1, -1);
  this->parent_.update();
}

void MazeDrawer::MouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    path_start_end_.first.setX(event->position().x() / maze_wall_length_.x());
    path_start_end_.first.setY(event->position().y() / maze_wall_length_.y());
    path_finder_.SetStart(path_start_end_.first.x(), path_start_end_.first.y());
  } else if (event->button() == Qt::RightButton) {
    path_start_end_.second.setX(event->position().x() / maze_wall_length_.x());
    path_start_end_.second.setY(event->position().y() / maze_wall_length_.y());
    path_finder_.SetFinish(path_start_end_.second.x(),
                           path_start_end_.second.y());
  }
  if (path_start_end_.first.x() >= 0 && path_start_end_.second.x() >= 0) {
    path_finder_.SetMaze(*maze_vert_walls_, *maze_hor_walls_);
    path_finder_.FindShortestPathLength();
    this->parent_.update();
  }
}

void MazeDrawer::DrawPath(QPainter &painter) {
  if (path_start_end_.first.x() < 0 || path_start_end_.second.x() < 0) return;
  std::list<std::pair<std::size_t, std::size_t>> path = path_finder_.GetPath();
  auto it = path.begin();
  std::pair<std::size_t, std::size_t> prev_point = *it;
  it++;
  for (; it != path.end(); it++) {
    QPoint start(
        maze_wall_length_.x() * prev_point.second + maze_wall_length_.x() / 2,
        maze_wall_length_.y() * prev_point.first + maze_wall_length_.y() / 2);
    QPoint end(maze_wall_length_.x() * it->second + maze_wall_length_.x() / 2,
               maze_wall_length_.y() * it->first + maze_wall_length_.y() / 2);
    painter.drawLine(start, end);
    prev_point = *it;
  }
}

void MazeDrawer::ResizeEvent(QResizeEvent *event) {
  if (maze_vert_walls_ == nullptr || maze_hor_walls_ == nullptr) return;
  RecalculateWallLength();
}

void MazeDrawer::RecalculateWallLength() {
  maze_wall_length_.setX(static_cast<float>(this->parent_.width()) /
                         maze_vert_walls_->at(0).size());
  maze_wall_length_.setY(static_cast<float>(this->parent_.height()) /
                         maze_vert_walls_->size());
}

void MazeDrawer::DrawWalls(QPainter &painter,
                           std::vector<std::vector<bool>> *matrix,
                           Qt::Orientation orient) {
  int rows = matrix->size();
  int columns = matrix->at(0).size();
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < columns; x++) {
      if (matrix->at(y).at(x)) {
        QPoint start;
        QPoint end;
        if (orient == Qt::Horizontal) {
          float y_pos = maze_wall_length_.y() * (y + 1);
          start = QPoint(maze_wall_length_.x() * x, y_pos);
          end = QPoint(start.x() + maze_wall_length_.x(), y_pos);
        } else {
          float x_pos = maze_wall_length_.x() * (x + 1);
          start = QPoint(x_pos, maze_wall_length_.y() * y);
          end = QPoint(x_pos, start.y() + maze_wall_length_.y());
        }
        painter.drawLine(start, end);
      }
    }
  }
}

void MazeDrawer::Draw() {
  if (maze_vert_walls_ == nullptr || maze_hor_walls_ == nullptr) return;
  QPainter painter(&this->parent_);
  this->SetPen(QPen(Qt::black, 2, Qt::PenStyle::SolidLine,
                    Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::MiterJoin));
  painter.setPen(this->pen_);
  painter.setBrush(this->brush_);
  // Draw widget frame
  painter.drawRect(QRect(this->pen_.widthF() / 2, this->pen_.widthF() / 2,
                         this->parent_.width() - this->pen_.widthF(),
                         this->parent_.height() - this->pen_.widthF()));
  painter.setRenderHint(QPainter::Antialiasing, true);
  DrawWalls(painter, maze_vert_walls_, Qt::Vertical);
  DrawWalls(painter, maze_hor_walls_, Qt::Horizontal);
  this->SetPen(QPen(Qt::darkGreen, 2, Qt::PenStyle::SolidLine,
                    Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::MiterJoin));
  painter.setPen(this->pen_);
  DrawPath(painter);
}
}  // namespace s21
