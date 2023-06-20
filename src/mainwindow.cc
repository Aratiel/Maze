#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>

#include "drawerview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  QTimer::singleShot(0, this, SLOT(OnWidgetLoad()));
}

void MainWindow::OnWidgetLoad() {
  ConnectToSignals();
  drawer_view_ = ui->drawer;
  maze_drawer_.reset(new s21::MazeDrawer(*drawer_view_));
  cave_drawer_.reset(new s21::CaveDrawer(*drawer_view_));
  OnIndexChanged(MainWindow::TabIndex::Cave);
}

void MainWindow::ConnectToSignals() {
  connect(ui->caveLoad, &QPushButton::clicked, this,
          &MainWindow::OnCaveLoadPressed);
  connect(ui->caveSave, &QPushButton::clicked, this,
          &MainWindow::OnCaveSavePressed);
  connect(ui->mazeLoad, &QPushButton::clicked, this,
          &MainWindow::OnMazeLoadPressed);
  connect(ui->mazeSave, &QPushButton::clicked, this,
          &MainWindow::OnMazeSavePressed);
  connect(ui->mazeGenerate, &QPushButton::clicked, this,
          &MainWindow::OnMazeGenerate);
  connect(ui->caveGenerate, &QPushButton::clicked, this,
          &MainWindow::OnCaveGenerate);
  connect(ui->caveNextStep, &QPushButton::clicked, this,
          &MainWindow::OnCaveNextStep);
  connect(ui->caveAutoGen, &QPushButton::clicked, this,
          &MainWindow::OnCaveAuto);
  connect(ui->tabWidget, &QTabWidget::currentChanged, this,
          &MainWindow::OnIndexChanged);
}

void MainWindow::OnIndexChanged(int new_index) {
  switch (new_index) {
    case MainWindow::TabIndex::Cave:
      drawer_view_->SetDrawer(maze_drawer_.get());
      break;
    case MainWindow::TabIndex::Maze:
      drawer_view_->SetDrawer(cave_drawer_.get());
      break;
    default:
      break;
  }
}

void MainWindow::OnCaveLoadPressed() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open cave file"),
                                                  QDir::homePath());
  if (!fileName.isEmpty()) {
    try {
      s21::Parser parser;
      parser.Parse(fileName.toStdString(), s21::ParserType::Cave);
      cave_.SetGrid(parser.GetMatrix1());
      cave_.SetCutoff(ui->caveBirthLimit->value(), ui->caveDeathLimit->value());
      cave_.SetSize(parser.GetYSize(), parser.GetXSize());
      ui->caveDimensionX->setValue(parser.GetXSize());
      ui->caveDimensionY->setValue(parser.GetYSize());
      cave_drawer_.get()->SetCave(&cave_.GetGrid());
    } catch (const std::exception& e) {
      QMessageBox::critical(
          this, "Error",
          QString("Error while openning file...\n\n").append(e.what()));
    }
  }
}

void MainWindow::OnCaveSavePressed() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save cave to file"),
                                                  QDir::homePath() + "/cave");
  if (!fileName.isEmpty()) {
    try {
      cave_.GenerateFileWithCave(fileName.toStdString());
    } catch (const std::exception& e) {
      QMessageBox::critical(
          this, "Error",
          QString("Error while openning file...\n\n").append(e.what()));
    }
  }
}

void MainWindow::OnMazeLoadPressed() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open cave file"),
                                                  QDir::homePath());
  if (!fileName.isEmpty()) {
    try {
      s21::Parser parser;
      parser.Parse(fileName.toStdString(), s21::ParserType::Maze);
      maze_.SetWallMatrixRight(parser.GetMatrix1());
      maze_.SetWallMatrixBellow(parser.GetMatrix2());
      maze_.SetColumns(parser.GetXSize());
      maze_.SetRows(parser.GetYSize());
      maze_drawer_.get()->SetWalls(&maze_.GetWallMatrixRight(),
                                   &maze_.GetWallMatrixBelow());
    } catch (const std::exception& e) {
      QMessageBox::critical(
          this, "Error",
          QString("Error while openning file...\n\n").append(e.what()));
    }
  }
}

void MainWindow::OnMazeSavePressed() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save cave to file"),
                                                  QDir::homePath() + "/maze");
  if (!fileName.isEmpty()) {
    try {
      maze_.GenerateFileWithMaze(fileName.toStdString());
    } catch (const std::exception& e) {
      QMessageBox::critical(
          this, "Error",
          QString("Error while saving file...\n\n").append(e.what()));
    }
  }
}

void MainWindow::OnMazeGenerate() {
  maze_.Generate(ui->mazeDimensionY->value(), ui->mazeDimensionX->value());
  maze_drawer_.get()->SetWalls(&maze_.GetWallMatrixRight(),
                               &maze_.GetWallMatrixBelow());
}

void MainWindow::OnCaveGenerate() {
  cave_.SetCutoff(ui->caveBirthLimit->value(), ui->caveDeathLimit->value());
  cave_.SetSize(ui->caveDimensionY->value(), ui->caveDimensionX->value());
  cave_.InitMap();
  cave_drawer_.get()->SetCave(&cave_.GetGrid());
}

void MainWindow::OnCaveNextStep() {
  if (!cave_.GetGrid().empty()) {
    cave_.Generation();
    cave_drawer_.get()->SetCave(&cave_.GetGrid());
  }
}

static void delay(int sleep) {
  QTime dieTime = QTime::currentTime().addMSecs(sleep);
  while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::OnCaveAuto() {
  if (!cave_.GetGrid().empty()) {
    int n = 0, max_n = 100, caveStepDelay = ui->caveStepDelay->value();
    for (; n < max_n && cave_.Generation(); n++) {
      delay(caveStepDelay);
      cave_drawer_.get()->SetCave(&cave_.GetGrid());
    }
  }
}

MainWindow::~MainWindow() { delete ui; }
