#include "parser.h"

namespace s21 {
void Parser::Parse(std::string path, ParserType type) {
  std::ifstream file(path);  // файл из которого читаем
  if (!file.is_open())       // если не удалось открыть
    throw std::runtime_error("The file does not exist.");
  std::string line = {};  // считанные строки
  if (std::getline(file, line)) {
    if (sscanf(line.c_str(), "%u %u", &size_y_, &size_x_) != 2)
      throw std::runtime_error("Incorrect format");
    matrix1_.resize(size_y_, vector<bool>(size_x_));
    matrix2_.resize(size_y_, vector<bool>(size_x_));
  }
  unsigned int row_count = 0;
  do {
    std::getline(file, line);
    if (line.empty()) throw std::runtime_error("Incorrect format");
    ScanMatrix(row_count, line, &matrix1_);
    row_count++;
  } while (row_count < size_y_);
  if (type == ParserType::Maze) {
    std::getline(file, line);
    row_count = 0;
    do {
      std::getline(file, line);
      if (line.empty()) throw std::runtime_error("Incorrect format");
      ScanMatrix(row_count, line, &matrix2_);
      row_count++;
    } while (row_count < size_y_);
  }
  file.close();  // закрываем файл
}

void Parser::ScanMatrix(unsigned int row_count, std::string line,
                        std::vector<std::vector<bool>> *matrix) {
  unsigned int column_count = 0;
  std::istringstream iss(line);
  for (std::string token;
       std::getline(iss, token, ' ') && column_count < size_x_;) {
    int is_wall = 0;
    if (sscanf(token.c_str(), "%d", &is_wall) != 1)
      throw std::runtime_error("Incorrect format");
    matrix->at(row_count).at(column_count) = is_wall;
    column_count++;
  }
}
}  // namespace s21
