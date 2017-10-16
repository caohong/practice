class Solution {
    public:
        /*
         * @param A: An integer array
         * @return: An integer
         */
        int singleNumber(vector<int> &A) {
            int result = 0;
            for (int i = 0; i < A.size(); i++) {
                result ^= A[i];
            }
            return result;
        }
};
