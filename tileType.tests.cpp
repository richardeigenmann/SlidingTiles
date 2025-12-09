#include "tileType.h"
#include <gmock/gmock.h>

TEST(TileType, Empty) {
  auto t = SlidingTiles::TileType::Empty;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("Empty", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L" ", single);
}

TEST(TileType, Horizontal) {
  SlidingTiles::TileType t = SlidingTiles::TileType::Horizontal;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("Horizontal", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"-", single);
}

TEST(TileType, Vertical) {
  SlidingTiles::TileType t = SlidingTiles::TileType::Vertical;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("Vertical", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"|", single);
}

TEST(TileType, StartTop) {
  SlidingTiles::TileType t = SlidingTiles::TileType::StartTop;
  ASSERT_TRUE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("StartTop", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┴", single);
}

TEST(TileType, StartBottom) {
  SlidingTiles::TileType t = SlidingTiles::TileType::StartBottom;
  ASSERT_TRUE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("StartBottom", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┬", single);
}

TEST(TileType, StartLeft) {
  SlidingTiles::TileType t = SlidingTiles::TileType::StartLeft;
  ASSERT_TRUE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("StartLeft", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┤", single);
}

TEST(TileType, StartRight) {
  SlidingTiles::TileType t = SlidingTiles::TileType::StartRight;
  ASSERT_TRUE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("StartRight", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"├", single);
}

TEST(TileType, EndTop) {
  SlidingTiles::TileType t = SlidingTiles::TileType::EndTop;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_TRUE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("EndTop", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┻", single);
}

TEST(TileType, EndBottom) {
  SlidingTiles::TileType t = SlidingTiles::TileType::EndBottom;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_TRUE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("EndBottom", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┳", single);
}

TEST(TileType, EndRight) {
  SlidingTiles::TileType t = SlidingTiles::TileType::EndRight;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_TRUE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("EndRight", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┣", single);
}

TEST(TileType, EndLeft) {
  SlidingTiles::TileType t = SlidingTiles::TileType::EndLeft;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_TRUE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("EndLeft", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┫", single);
}

TEST(TileType, LeftTop) {
  SlidingTiles::TileType t = SlidingTiles::TileType::LeftTop;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("LeftTop", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┘", single);
}

TEST(TileType, LeftBottom) {
  SlidingTiles::TileType t = SlidingTiles::TileType::LeftBottom;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("LeftBottom", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┐", single);
}

TEST(TileType, TopRight) {
  SlidingTiles::TileType t = SlidingTiles::TileType::TopRight;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("TopRight", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"└", single);
}

TEST(TileType, BottomRight) {
  SlidingTiles::TileType t = SlidingTiles::TileType::BottomRight;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("BottomRight", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"┌", single);
}

TEST(TileType, Obstacle) {
  SlidingTiles::TileType t = SlidingTiles::TileType::Obstacle;
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_FALSE(isMoveableType(t));
  auto s = tileTypeToString(t);
  ASSERT_EQ("Obstacle", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"o", single);
}

TEST(TileType, Unknown) {
  SlidingTiles::TileType t = static_cast<SlidingTiles::TileType>(65536);
  ASSERT_FALSE(isStartTileType(t));
  ASSERT_FALSE(isEndTileType(t));
  ASSERT_TRUE(isMoveableType(t)); // Actually undefined behaviour
  auto s = tileTypeToString(t);
  ASSERT_EQ("Unknown Type", s);
  std::wstring single = tileTypeToWstringChar(t);
  ASSERT_EQ(L"?", single);
}

TEST(TileType, randomStartTileType) {
  // non deterministic test !! Can this be improved?
  int StartTop{0};
  int StartBottom{0};
  int StartLeft{0};
  int StartRight{0};
  int Unexpected{0};
  for (int i = 0; i < 100; ++i) {
    SlidingTiles::TileType t = randomStartTileType();
    ASSERT_TRUE(isStartTileType(t));
    switch (t) {
    case SlidingTiles::TileType::StartTop:
      ++StartTop;
      break;
    case SlidingTiles::TileType::StartBottom:
      ++StartBottom;
      break;
    case SlidingTiles::TileType::StartLeft:
      ++StartLeft;
      break;
    case SlidingTiles::TileType::StartRight:
      ++StartRight;
      break;
    default:
      ++Unexpected;
    }
  }
  EXPECT_GT(StartTop, 0) << "After 100 random start tiles we should have "
                            "returned more than 0 StartTop tiles";
  EXPECT_GT(StartBottom, 0) << "After 100 random start tiles we should have "
                               "returned more than 0 StartBottom tiles";
  EXPECT_GT(StartLeft, 0) << "After 100 random start tiles we should have "
                             "returned more than 0 StartLeft tiles";
  EXPECT_GT(StartRight, 0) << "After 100 random start tiles we should have "
                              "returned more than 0 StartRight tiles";
  ASSERT_EQ(Unexpected, 0)
      << "After 100 random start tiles we must not have unexpected tiles";
}

TEST(TileType, randomEndTileType) {
  // non deterministic test !! Can this be improved?
  int EndTop{0};
  int EndBottom{0};
  int EndLeft{0};
  int EndRight{0};
  int Unexpected{0};
  for (int i = 0; i < 100; ++i) {
    SlidingTiles::TileType t = randomEndTileType();
    ASSERT_TRUE(isEndTileType(t));
    switch (t) {
    case SlidingTiles::TileType::EndTop:
      ++EndTop;
      break;
    case SlidingTiles::TileType::EndBottom:
      ++EndBottom;
      break;
    case SlidingTiles::TileType::EndLeft:
      ++EndLeft;
      break;
    case SlidingTiles::TileType::EndRight:
      ++EndRight;
      break;
    default:
      ++Unexpected;
    }
  }
  EXPECT_GT(EndTop, 0) << "After 100 random end tiles we should have returned "
                          "more than 0 EndTop tiles";
  EXPECT_GT(EndBottom, 0) << "After 100 random end tiles we should have "
                             "returned more than 0 EndBottom tiles";
  EXPECT_GT(EndLeft, 0) << "After 100 random end tiles we should have returned "
                           "more than 0 EndLeft tiles";
  EXPECT_GT(EndRight, 0) << "After 100 random end tiles we should have "
                            "returned more than 0 EndRight tiles";
  ASSERT_EQ(Unexpected, 0)
      << "After 100 random end tiles we must not have unexpected tiles";
}

TEST(TileType, isGameTileType) {
  // non deterministic test !! Can this be improved?
  int Horizontal{0};
  int Vertical{0};
  int LeftTop{0};
  int LeftBottom{0};
  int TopRight{0};
  int BottomRight{0};
  int Obstacle{0};
  int Unexpected{0};
  for (int i = 0; i < 100; ++i) {
    SlidingTiles::TileType t = randomGameTileType();
    switch (t) {
    case SlidingTiles::TileType::Horizontal:
      ++Horizontal;
      break;
    case SlidingTiles::TileType::Vertical:
      ++Vertical;
      break;
    case SlidingTiles::TileType::LeftTop:
      ++LeftTop;
      break;
    case SlidingTiles::TileType::LeftBottom:
      ++LeftBottom;
      break;
    case SlidingTiles::TileType::TopRight:
      ++TopRight;
      break;
    case SlidingTiles::TileType::BottomRight:
      ++BottomRight;
      break;
    case SlidingTiles::TileType::Obstacle:
      ++Obstacle;
      break;
    default:
      ++Unexpected;
    }
  }
  EXPECT_GT(Horizontal, 0) << "After 100 random game tiles we should have "
                              "returned more than 0 Horizontal tiles";
  EXPECT_GT(Vertical, 0) << "After 100 random game tiles we should have "
                            "returned more than 0 Vertical tiles";
  EXPECT_GT(LeftTop, 0) << "After 100 random game tiles we should have "
                           "returned more than 0 LeftTop tiles";
  EXPECT_GT(LeftBottom, 0) << "After 100 random game tiles we should have "
                              "returned more than 0 LeftBottom tiles";
  EXPECT_GT(TopRight, 0) << "After 100 random game tiles we should have "
                            "returned more than 0 TopRight tiles";
  EXPECT_GT(Obstacle, 0) << "After 100 random game tiles we should have "
                            "returned more than 0 Obstacle tiles";
  ASSERT_EQ(Unexpected, 0)
      << "After 100 random game tiles we must not have unexpected tiles";
}
