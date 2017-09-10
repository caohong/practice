/*
 * http://www.lintcode.com/en/problem/merge-sorted-array/
 */


class Solution {
public:
    /*
     * @param A: sorted integer array A which has m elements, but size of A is m+n
     * @param m: An integer
     * @param B: sorted integer array B which has n elements
     * @param n: An integer
     * @return: nothing
     */
    void mergeSortedArray(int A[], int m, int B[], int n) {
        int ia = m - 1, ib = n - 1, i = m + n - 1;
        while (ia >= 0 && ib >= 0) {
            if (A[ia] > B[ib]) {
                A[i] = A[ia--];
            } else {
                A[i] = B[ib--];
            }
            i--;
        }
        while (ib >= 0) {
            A[i--] = B[ib--];
        }
        return;
    }
};