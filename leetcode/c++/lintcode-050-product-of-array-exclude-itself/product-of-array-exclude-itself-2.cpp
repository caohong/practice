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
        long long temp = 1;
        vector<long long> result;
        vector<long long> product_table(nums.size() + 1, 1);
        
        for (int i = nums.size() - 1; i >= 0; i--) {
            product_table[i] = product_table[i + 1] * nums[i];
        }
        
        for (int i = 0; i < nums.size(); i++) {
            result.push_back(temp * product_table[i + 1]);
            temp = temp * nums[i];
        }
        
        return result;
    }
};