#include "gmock/gmock.h"
#include "SimilarityChecker.cpp"
using namespace testing;

class SimilarityCheckerFixture : public Test {
public:
    SimilarityChecker checker;
};

// 같은 길이 -> 최대 점수 60점
TEST_F(SimilarityCheckerFixture, ReturnsMaxScoreWhenSameLength) {
    EXPECT_EQ(60, checker.calculate("hello", "world"));
}

// 길이가 정확히 2배 -> 0점 (경계값)
TEST_F(SimilarityCheckerFixture, ReturnsZeroWhenLengthIsExactlyDouble) {
    EXPECT_EQ(0, checker.calculate("ab", "abcd"));
}

// 길이가 2배 이상 -> 0점
TEST_F(SimilarityCheckerFixture, ReturnsZeroWhenLengthDiffersMoreThanDouble) {
    EXPECT_EQ(0, checker.calculate("a", "abcdef"));
}

// 부분 점수: A=4, B=3, Gap=1 -> (1 - 1/3)*60 = 40점
TEST_F(SimilarityCheckerFixture, ReturnsPartialScoreForModerateLengthDifference) {
    EXPECT_EQ(40, checker.calculate("abc", "abcd"));
}

// 인자 순서가 바뀌어도 동일한 점수
TEST_F(SimilarityCheckerFixture, IsSymmetricRegardlessOfArgumentOrder) {
    EXPECT_EQ(checker.calculate("abc", "abcd"),
              checker.calculate("abcd", "abc"));
}

// 한쪽이 빈 문자열이면 0점 (0으로 나누기 방지)
TEST_F(SimilarityCheckerFixture, ReturnsZeroWhenOneStringIsEmpty) {
    EXPECT_EQ(0, checker.calculate("", "abc"));
}

int main() {
    InitGoogleMock();
    return RUN_ALL_TESTS();
}
