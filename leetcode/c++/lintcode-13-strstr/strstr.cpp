/*
 * http://www.lintcode.com/en/problem/strstr/
 */

#include <iostream>
using namespace std;

class Solution {
public:
    bool strIsEqual(const char* source, const char* target, int size) {
        for (int i = 0; i < size; i ++) {
            if (source[i] != target[i]) {
                return false;
            }
        }
        return true;
    }

    /**
     * Returns a index to the first occurrence of target in source,
     * or -1  if target is not part of source.
     * @param source string to be scanned.
     * @param target string containing the sequence of characters to match.
     */
    int strStr(const char *source, const char *target) {
        if (source == NULL || target == NULL) {
            return -1;
        }
        int target_size = strlen(target);
        int source_size = strlen(source);
        if (source_size == 0 && target_size == 0) {
            return 0;
        }
        int size = source_size - target_size;
        if (size < 0) {
            return -1;
        }
        
        int i = 0;
        bool found = false;
        for (; i <= size; i ++) {
            if (strIsEqual(&source[i], target, target_size)) {
                found = true;
                break;
            }
        }
        return found ? i : -1;
    }
};

int main() {
    Solution s;
    char source[] = "lintcode";
    char target[] = "lintcode";
    cout << "strstr position is " << s.strStr(source, target) << endl;
}
