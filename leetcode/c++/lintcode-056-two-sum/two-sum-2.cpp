#include <unordered_map>

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result(2, -1);
        unordered_map<int, int> sum_map;
        for (int i = 0; i < nums.size(); i ++) {
            if (sum_map.find(target - nums[i]) != sum_map.end()) {
                result[0] = sum_map[target - nums[i]] + 1;
                result[1] = i + 1;
                break;
            } else {
                sum_map[nums[i]] = i;
            }
        }
        return result;
    }
};
