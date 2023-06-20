#include "cavedrawer.h"

#include <QPainter>

namespace s21 {
CaveDrawer::CaveDrawer(DrawerView &parent) : DrawerBase(parent) {
  SetBrush(QBrush(Qt::black, Qt::BrushStyle::SolidPattern));
};
CaveDrawer::CaveDrawer(DrawerView &parent,
                       std::vector<std::vector<bool> > *cave)
    : CaveDrawer(parent) {
  SetCave(cave);
}
void CaveDrawer::Draw() {
  if (cave_ == nullptr) return;
  QPainter painter(&this->parent_);
  painter.setPen(this->pen_);
  painter.setBrush(this->brush_);

  int rows = cave_->size();
  int columns = cave_->at(0).size();
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < columns; x++) {
      if (cave_->at(y).at(x)) {
        float x_pos = cave_tile_size_.x() * x;
        float y_pos = cave_tile_size_.y() * y;
        painter.drawRect(x_pos, y_pos, cave_tile_size_.x(),
                         cave_tile_size_.y());
      }
    }
  }
}

void CaveDrawer::SetCave(std::vector<std::vector<bool> > *cave) {
  cave_ = cave;
  RecalculateTileSize();
  this->parent_.update();
}

void CaveDrawer::ResizeEvent(QResizeEvent *event) {
  if (cave_ == nullptr) return;
  RecalculateTileSize();
}
void CaveDrawer::RecalculateTileSize() {
  cave_tile_size_.setX(static_cast<float>(this->parent_.width()) /
                       cave_->at(0).size());
  cave_tile_size_.setY(static_cast<float>(this->parent_.height()) /
                       cave_->size());
}
}  // namespace s21
