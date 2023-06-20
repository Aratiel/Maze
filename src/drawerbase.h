#ifndef SRC_DRAWERBASE_H_
#define SRC_DRAWERBASE_H_
#include <QBrush>
#include <QPainter>
#include <QPen>

#include "drawerview.h"

class DrawerView;

namespace s21 {
class DrawerBase {
  friend DrawerView;

 public:
  DrawerBase() = delete;
  DrawerBase(DrawerView &parent) : parent_(parent) { SetDefaultTools(); };
  void SetPen(const QPen &pen) { pen_ = pen; }
  void SetBrush(const QBrush &brush) { brush_ = brush; }
  void SetDefaultTools() {
    SetBrush(QBrush(Qt::darkGreen, Qt::BrushStyle::NoBrush));
    SetPen(QPen(Qt::black, 2, Qt::PenStyle::SolidLine,
                Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::MiterJoin));
  }
  virtual void Draw() = 0;
  virtual ~DrawerBase(){};

 protected:
  virtual void ResizeEvent(QResizeEvent *event) = 0;
  virtual void MouseReleaseEvent(QMouseEvent *event){};
  DrawerView &parent_;
  QPen pen_;
  QBrush brush_;
};
}  // namespace s21
#endif  // SRC_DRAWERBASE_H_
