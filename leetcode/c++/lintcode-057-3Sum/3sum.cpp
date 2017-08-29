class Solution {
public:
    /*
     * @param numbers: Give an array numbers of n integer
     * @return: Find all unique triplets in the array which gives the sum of zero.
     */
    vector<vector<int>> threeSum(vector<int> numbers) {
        vector<vector<int>> result;
        sort(numbers.begin(), numbers.end());
        for (int i = 0; i < numbers.size(); i ++) {
            if (i > 0 && numbers[i] == numbers[i - 1]) {
                continue;
            }
            if (numbers[i] >= 0) {
                break;
            }
            int target = -numbers[i];
            
            unordered_map<int, int> sum_map;
            for (int j = i; j < numbers.size(); j ++) {
                if (j > i && numbers[j] == numbers[j - 1]) {
                    continue;
                }
                if (sum_map.find(target - numbers[j]) != sum_map.end()) {
                    vector<int> tmp;
                    tmp.push_back(numbers[i]);
                    tmp.push_back(target-numbers[j]);
                    tmp.push_back(numbers[j]);
                    result.push_back(tmp);
                } else {
                    sum_map[numbers[j]] = j;
                }
            }
        }
        return result;
    }
};