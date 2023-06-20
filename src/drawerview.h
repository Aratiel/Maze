#ifndef DRAWERVIEW_H
#define DRAWERVIEW_H

#include <QWidget>

#include "drawerbase.h"

namespace s21 {
class DrawerBase;
}

class DrawerView : public QWidget {
  Q_OBJECT
 public:
  explicit DrawerView(QWidget *parent = nullptr);
  void SetDrawer(s21::DrawerBase *drawer) {
    this->drawer_ = drawer;
    update();
  }
 signals:

 protected:
  void SetDefaultTools();
  void resizeEvent(QResizeEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
 protected slots:
  void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  s21::DrawerBase *drawer_ = nullptr;
};

#endif  // DRAWERVIEW_H
