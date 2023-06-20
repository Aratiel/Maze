#include <gtest/gtest.h>

#include "config.h"
#include "findpath.h"
#include "parser.h"

TEST(path, test1) {
  s21::Path P;
  std::vector<std::vector<bool>> m1 = {
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 1, 1, 1},
      {1, 0, 1, 0, 0, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
      {0, 0, 1, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
      {0, 0, 0, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 0, 0, 1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
  };
  std::vector<std::vector<bool>> m2 = {
      {0, 1, 0, 0, 0, 1, 1, 1, 0, 0}, {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };
  P.SetMaze(m1, m2);
  P.SetStart(0, 0);
  P.SetFinish(2, 3);
  int n = P.FindShortestPathLength();
  ASSERT_TRUE(n = 15);
}

TEST(path, test2) {
  s21::Path P;
  s21::Parser C;
  C.Parse(CMAKE_CURRENT_SOURCE_DIR "/maze10x10.txt", s21::ParserType::Maze);
  P.SetMaze(C.GetMatrix1(), C.GetMatrix2());
  P.SetStart(0, 0);
  P.SetFinish(2, 3);
  int n = P.FindShortestPathLength();
  ASSERT_TRUE(n = 15);
}
