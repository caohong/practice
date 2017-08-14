/*
 * http://www.lintcode.com/en/problem/majority-number/
 */

class Solution{
public:
    int majorityNumer(vector<int> nums) {
        int result, count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (count == 0) {
                result = nums[i];
                count++;
            } else {
                if (result == nums[i])
                    count ++;
                else
                    count --;
            }
        }
        return result;
    }
}
