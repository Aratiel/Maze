#include "drawerview.h"

#include <iostream>

DrawerView::DrawerView(QWidget* parent) : QWidget{parent} {
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
}

void DrawerView::mouseReleaseEvent(QMouseEvent* event) {
  if (drawer_) drawer_->MouseReleaseEvent(event);
}

void DrawerView::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  if (drawer_) drawer_->ResizeEvent(event);
}

void DrawerView::paintEvent(QPaintEvent* event) {
  if (drawer_) drawer_->Draw();
}
