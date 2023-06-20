#ifndef SRC_MODELS_PARSER_H_
#define SRC_MODELS_PARSER_H_

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;

namespace s21 {
enum class ParserType { Cave, Maze };

class Parser {
 public:
  void Parse(std::string path, ParserType type);
  unsigned int GetYSize() const { return size_y_; }
  unsigned int GetXSize() const { return size_x_; }
  vector<vector<bool>> GetMatrix1() const { return matrix1_; }
  vector<vector<bool>> GetMatrix2() const { return matrix2_; }

 private:
  unsigned int size_x_ = 0, size_y_ = 0;
  vector<vector<bool>> matrix1_;
  vector<vector<bool>> matrix2_;

  void ScanMatrix(unsigned int r_count, std::string line,
                  vector<vector<bool>> *matrix);
};
}  // namespace s21

#endif  // SRC_MODELS_PARSER_H_
