#include <string>
#include <algorithm>
using namespace std;

class LengthSimilarityChecker {
public:
    static constexpr int MAX_SCORE = 60;

    int calculate(const string& s1, const string& s2) const {
        const size_t longerLen  = max(s1.length(), s2.length());
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
};
