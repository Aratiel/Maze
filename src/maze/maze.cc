#include "maze.h"
namespace s21 {
bool Maze::YesCreate() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 1);
  return static_cast<bool>(distrib(gen));
}

void Maze::SettingValues(std::size_t rows, std::size_t columns) {
  rows_ = rows;
  columns_ = columns;  // можно упароться и не хрнаить эти значения
  wall_right_ =
      std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, 0));
  wall_bellow_ =
      std::vector<std::vector<bool>>(rows, std::vector<bool>(columns, 0));
}

void Maze::ChangeSet(std::size_t set_value, std::size_t new_set_value) {
  for (std::size_t i = 0; i < columns_; ++i) {
    if (row_[i] == set_value) {
      row_[i] = new_set_value;
    }
  }
}

std::size_t Maze::ValuesLeftInSet(std::size_t rows, std::size_t value_set) {
  std::size_t counter_unique_value_in_set = 0;
  for (std::size_t i = 0; i < columns_; ++i) {
    if (row_[i] == value_set && wall_bellow_[rows][i] != 1)
      counter_unique_value_in_set++;
  }
  return counter_unique_value_in_set;
}

void Maze::GenerateFileWithMaze(std::string path) {
  if (wall_right_.empty() || wall_bellow_.empty())
    throw std::runtime_error("maze empty");
  std::ofstream fout(path);
  if (!fout.is_open()) {
    throw std::runtime_error("not open");
  } else {
    fout << rows_ << " " << columns_ << std::endl;
    OutWallInFile(fout, wall_right_, true);
    OutWallInFile(fout, wall_bellow_, false);
  }
  fout.close();
}

void Maze::CreateRightWall(std::size_t rows) {
  for (std::size_t i = 0; i < columns_ - 1; ++i) {
    if (YesCreate() || row_[i] == row_[i + 1]) {
      wall_right_[rows][i] = true;
    } else {
      ChangeSet(row_[i + 1], row_[i]);
      wall_right_[rows][i] = false;
    }
  }
  wall_right_[rows][columns_ - 1] = true;
}

void Maze::CreateBottomWall(std::size_t rows) {
  for (std::size_t i = 0; i < columns_; ++i) {
    if (YesCreate() && ValuesLeftInSet(rows, row_[i]) != 1) {
      wall_bellow_[rows][i] = true;
    } else {
      wall_bellow_[rows][i] = false;
    }
  }
}

void Maze::DeleteCellsWithBottomWall(std::size_t rows) {
  for (std::size_t i = 0; i < columns_; ++i) {
    if (wall_bellow_[rows][i] == true) {
      row_[i] = unique_set_counter_++;
    }
  }
}

void Maze::EndOfMaze() {
  CreateRightWall(rows_ - 1);
  for (std::size_t i = 0; i < columns_ - 1; ++i) {
    wall_bellow_[rows_ - 1][i] = true;
    if (row_[i] != row_[i + 1]) {
      wall_right_[rows_ - 1][i] = false;
      ChangeSet(row_[i + 1], row_[i]);
    }
  }
  wall_bellow_[rows_ - 1][columns_ - 1] = true;
  row_.clear();
}

void Maze::Generate(std::size_t rows, std::size_t columns) {
  SettingValues(rows, columns);
  FirstFill();
  for (std::size_t i = 0; i < rows_ - 1; ++i) {
    CreateRightWall(i);
    CreateBottomWall(i);
    DeleteCellsWithBottomWall(i);
  }
  EndOfMaze();
}

void Maze::FirstFill() {
  for (std::size_t i = 0; i < columns_; ++i) {
    row_.push_back(unique_set_counter_++);
  }
}

void Maze::OutWallInFile(std::ofstream &outf,
                         std::vector<std::vector<bool>> const &out_wall,
                         bool flag_endl) {
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < columns_; ++j) {
      outf << out_wall[i][j];
      if (j != columns_ - 1) outf << " ";
    }
    outf << std::endl;
  }
  if (flag_endl) outf << std::endl;
}

}  // namespace s21
