#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cavedrawer.h"
#include "maze.h"
#include "mazedrawer.h"
#include "models/cave.h"
#include "models/parser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  enum TabIndex { Cave = 0, Maze = 1 };
  ~MainWindow();

 private slots:
  void OnWidgetLoad();
  void OnIndexChanged(int new_index);
  void OnMazeLoadPressed();
  void OnMazeSavePressed();
  void OnMazeGenerate();
  void OnCaveLoadPressed();
  void OnCaveSavePressed();
  void OnCaveGenerate();
  void OnCaveNextStep();
  void OnCaveAuto();

 private:
  Ui::MainWindow *ui;
  void ConnectToSignals();

  DrawerView *drawer_view_ = nullptr;
  s21::Maze maze_;
  s21::Cave cave_;

  std::unique_ptr<s21::MazeDrawer> maze_drawer_;
  std::unique_ptr<s21::CaveDrawer> cave_drawer_;
};

#endif  // MAINWINDOW_H
