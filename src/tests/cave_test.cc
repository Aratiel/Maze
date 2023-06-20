#include "cave.h"

#include <gtest/gtest.h>

#include <iostream>

#include "config.h"
#include "parser.h"

TEST(cave, test1) {
  s21::Parser P;
  s21::Cave C;
  P.Parse(CMAKE_CURRENT_SOURCE_DIR "/cave10x10.txt", s21::ParserType::Cave);
  C.SetGrid(P.GetMatrix1());
  C.SetSize(P.GetYSize(), P.GetXSize());
  C.SetCutoff(4, 4);
  int n = 0, max_n = 100;
  for (; n < max_n && C.Generation(); n++) {
  }
  ASSERT_TRUE(n = 8);
}

TEST(cave, test2) {
  s21::Cave C;
  C.InitMap();
  C.SetCutoff(0, 7);
  int n = 0, max_n = 100;
  for (; n < max_n && C.Generation(); n++) {
  }
  ASSERT_TRUE(n < 10);
  C.GenerateFileWithCave(CMAKE_CURRENT_SOURCE_DIR "/test_cave.txt");
  s21::Parser P;
  P.Parse(CMAKE_CURRENT_SOURCE_DIR "/test_cave.txt", s21::ParserType::Cave);
  ASSERT_EQ(P.GetMatrix1(), C.GetGrid());
}
