/*
 * http://www.lintcode.com/en/problem/maximum-subarray/
 */


class Solution {
public:    
    /**
     * @param nums: A list of integers
     * @return: A integer indicate the sum of max subarray
     */
    int maxSubArray(vector<int> nums) {
        if (nums.size() < 1) {
            return 0;
        }
        int maxSum = INT_MIN, sum = 0;
        for (int i=0; i < nums.size(); i++) {
            sum += nums[i];
            maxSum = max(sum, maxSum);
            if (sum < 0) {
                sum = 0;
            }
        }
        return maxSum;
    }
};
