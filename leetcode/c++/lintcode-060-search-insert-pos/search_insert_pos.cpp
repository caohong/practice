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
        if (A.size() < 1) {
            return 0;
        }
        int start = 0, end = A.size() - 1;
        int size = end - start + 1;
        while (size > 0) {
            int mid = start + size / 2;
            if (target > A[mid]) {
                start = mid + 1;
            } else if (target < A[mid]) {
                end = mid - 1;
            } else {
                return mid;
            }
            size = end - start + 1;
        }

        return start;

    }
};