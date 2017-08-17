/*
 * http://www.lintcode.com/en/problem/product-of-array-exclude-itself/
 */

class Solution {
public:
    /*
     * @param : Given an integers array A
     * @return: A long long array B and B[i]= A[0] * ... * A[i-1] * A[i+1] * ... * A[n-1]
     */
    vector<long long> productExcludeItself(vector<int> nums) {
        vector<long long> result(nums.size(), 1);
        for (int i = 0; i < nums.size(); i ++) {
            for (int j = 0; j < nums.size(); j ++) {
                if (j != i) {
                    result[j] = result[j] * nums[i];
                }
            }
        }
        return result;
    }
};