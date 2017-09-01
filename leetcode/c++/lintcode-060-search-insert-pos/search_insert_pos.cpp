/*
 * http://www.lintcode.com/en/problem/search-insert-position/
 */


class Solution {
public:
    /*
     * @param A: an integer sorted array
     * @param target: an integer to be inserted
     * @return: An integer
     */
    int searchInsert(vector<int> &A, int target) {
        int i = 0;

        if (A.size() < 1 || target <= A[0]) {
            return 0;
        }

        while ((i < A.size()) && (A[i] < target)) {
            i++;
        }

        return i;
    }
};