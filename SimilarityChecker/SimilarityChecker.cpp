#include <string>
#include <algorithm>
#include <set>
using namespace std;

class SimilarityChecker {
public:
    static const int MAX_SCORE = 60;
    static const int MAX_ALPHABET_SCORE = 40;

    int calculate(const string& s1, const string& s2) const {
        return calculateLengthScore(s1, s2) + calculateAlphabetScore(s1, s2);
    }

    int calculateLengthScore(const string& s1, const string& s2) const {
        const size_t longerLen = max(s1.length(), s2.length());
        const size_t shorterLen = min(s1.length(), s2.length());

        if (longerLen == shorterLen) {
            return MAX_SCORE;
        }
        if (shorterLen == 0 || longerLen >= 2 * shorterLen) {
            return 0;
        }

        const size_t gap = longerLen - shorterLen;
        const double ratio = 1.0 - static_cast<double>(gap) / static_cast<double>(shorterLen);
        return static_cast<int>(ratio * MAX_SCORE);
    }

    int calculateAlphabetScore(const string& s1, const string& s2) const {
        const set<char> letters1 = extractUppercaseLetters(s1);
        const set<char> letters2 = extractUppercaseLetters(s2);

        int sameCnt = 0;
        for (char ch : letters1) {
            if (letters2.count(ch) > 0) {
                ++sameCnt;
            }
        }
        const int totalCnt = static_cast<int>(letters1.size() + letters2.size()) - sameCnt;

        if (totalCnt == 0 || sameCnt == 0) {
            return 0;
        }
        return static_cast<int>(
            static_cast<double>(sameCnt) / static_cast<double>(totalCnt) * MAX_ALPHABET_SCORE
        );
    }

private:
    static set<char> extractUppercaseLetters(const string& s) {
        set<char> result;
        for (char ch : s) {
            if (ch >= 'A' && ch <= 'Z') {
                result.insert(ch);
            }
        }
        return result;
    }
};
