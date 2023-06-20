#include "maze.h"

#include <gtest/gtest.h>

#include "config.h"
#include "parser.h"

TEST(maze, test1) {
  s21::Maze test;
  test.Generate(5, 5);
  ASSERT_EQ(test.GetWallMatrixBelow().size(), 5);
  ASSERT_EQ(test.GetWallMatrixRight().size(), 5);
}

TEST(maze, test2) {
  s21::Maze test;
  test.Generate(10, 10);
  test.GenerateFileWithMaze("maze.txt");
  std::ifstream ifs("maze.txt");
  ASSERT_EQ(ifs.is_open(), true);
  ifs.close();
}

TEST(maze, test3) {
  s21::Parser P;
  P.Parse(CMAKE_CURRENT_SOURCE_DIR "/maze10x10.txt", s21::ParserType::Maze);
  auto mat1 = P.GetMatrix1();
  auto mat2 = P.GetMatrix2();
  ASSERT_EQ(mat1.size(), 10);
  ASSERT_EQ(mat1[0].size(), 10);
  ASSERT_EQ(mat2.size(), 10);
  ASSERT_EQ(mat2[0].size(), 10);
}
