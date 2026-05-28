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

// === 합산 점수(0~100): 길이 점수 + 알파벳 점수 ===

// 같은 길이 + 같은 알파벳 -> 60 + 40 = 100점 (만점)
TEST_F(SimilarityCheckerFixture, ReturnsMaxTotalWhenLengthAndAlphabetBothMatch) {
    EXPECT_EQ(100, checker.calculate("ABC", "ABC"));
}

// 2배 이상 길이차 + 공통 알파벳 없음 -> 0 + 0 = 0점
TEST_F(SimilarityCheckerFixture, ReturnsZeroWhenBothScoresAreZero) {
    EXPECT_EQ(0, checker.calculate("AB", "CDEFGH"));
}

// 같은 길이(60) + 알파벳 부분 일치({A,B,C}/{A,B,D}: 2/4*40=20) -> 80점
TEST_F(SimilarityCheckerFixture, SumsLengthAndAlphabetScores) {
    EXPECT_EQ(80, checker.calculate("ABC", "ABD"));
}

// 길이는 0점이지만 알파벳은 만점 -> 0 + 40 = 40점
TEST_F(SimilarityCheckerFixture, KeepsAlphabetScoreEvenWhenLengthScoreIsZero) {
    // "A"(1) vs "AAAA"(4): 4배 차이 -> 길이 0점, {A}/{A} 동일 -> 알파벳 40점
    EXPECT_EQ(40, checker.calculate("A", "AAAA"));
}

// 알파벳만 일부 일치({A,B}/{A,B,C,D}: 2/4*40=20) + 길이 정확히 2배 -> 0 + 20 = 20점
TEST_F(SimilarityCheckerFixture, KeepsAlphabetPartialScoreWhenLengthScoreIsZero) {
    EXPECT_EQ(20, checker.calculate("AB", "ABCD"));
}

int main() {
    InitGoogleMock();
    return RUN_ALL_TESTS();
}
