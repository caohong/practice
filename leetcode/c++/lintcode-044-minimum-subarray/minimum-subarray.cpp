/*
 * http://www.lintcode.com/en/problem/minimum-subarray/
 */


class Solution {
public:
    /**
     * @param nums: a list of integers
     * @return: A integer denote the sum of minimum subarray
     */
    int minSubArray(vector<int> nums) {
        int sum = 0;
        int maxSum = 0;
        int minSum = nums[0];
        for (int i = 0; i < nums.size(); i ++) {
           sum += nums[i];
           if (sum - maxSum < minSum) {
               minSum = sum - maxSum;
           }
           if (sum > maxSum) {
               maxSum = sum;
           }
        }
        return minSum;
    }
};
