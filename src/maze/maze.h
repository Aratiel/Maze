#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <vector>

namespace s21 {
class Maze {
 public:
  void GenerateFileWithMaze(std::string path);
  void Generate(std::size_t rows, std::size_t columns);
  std::vector<std::vector<bool>> &GetWallMatrixRight() { return wall_right_; }
  std::vector<std::vector<bool>> &GetWallMatrixBelow() { return wall_bellow_; }
  void SetWallMatrixRight(std::vector<std::vector<bool>> wall_right) {
    wall_right_ = wall_right;
  }
  void SetWallMatrixBellow(std::vector<std::vector<bool>> wall_bellow) {
    wall_bellow_ = wall_bellow;
  }
  void SetRows(unsigned int rows) { rows_ = rows; }
  void SetColumns(unsigned int columns) { columns_ = columns; }

 private:
  std::vector<std::vector<bool>> wall_right_;
  std::vector<std::vector<bool>> wall_bellow_;

  std::vector<std::size_t> row_;
  std::size_t rows_, columns_;
  std::size_t unique_set_counter_ = 1;
  bool YesCreate();
  void FirstFill();
  void CreateRightWall(std::size_t rows);
  void CreateBottomWall(std::size_t rows);
  void DeleteCellsWithBottomWall(std::size_t rows);
  void EndOfMaze();
  void SettingValues(std::size_t rows, std::size_t columns);
  void ChangeSet(std::size_t set_value, std::size_t new_set_value);
  std::size_t ValuesLeftInSet(std::size_t rows, std::size_t value_set);
  void OutWallInFile(std::ofstream &outf,
                     std::vector<std::vector<bool>> const &out_wall,
                     bool flag_endl);
};
}  // namespace s21
