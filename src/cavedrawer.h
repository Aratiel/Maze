#ifndef SRC_CAVEDRAWER_H_
#define SRC_CAVEDRAWER_H_

#include <QBrush>
#include <QPen>
#include <QVector2D>
#include <vector>

#include "drawerbase.h"

namespace s21 {
class CaveDrawer : public DrawerBase {
 public:
  CaveDrawer() = delete;
  explicit CaveDrawer(DrawerView &parent);
  CaveDrawer(DrawerView &parent, std::vector<std::vector<bool>> *cave);
  void SetCave(std::vector<std::vector<bool>> *cave);
  void Draw() override;

 protected:
  void ResizeEvent(QResizeEvent *event) override;

 private:
  void RecalculateTileSize();
  QVector2D cave_tile_size_ = {0, 0};
  std::vector<std::vector<bool>> *cave_ = nullptr;
};
}  // namespace s21

#endif  // SRC_CAVEDRAWER_H_
