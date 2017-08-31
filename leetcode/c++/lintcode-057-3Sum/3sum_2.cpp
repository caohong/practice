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
            
            int target = -numbers[i];
            
            int start = i + 1, end = numbers.size() - 1;
            while (start < end) {
                if (start > i + 1 && numbers[start - 1] == numbers[start]) {
                    start ++;
                    continue;
                }
                int sum = numbers[start] + numbers[end];
                if (sum == target) {
                    vector<int> tmp;
                    tmp.push_back(numbers[i]);
                    tmp.push_back(numbers[start]);
                    tmp.push_back(numbers[end]);
                    result.push_back(tmp);
                    start++;
                } else if (sum < target) {
                    start++;
                } else {
                    end--;
                }
            }

        }
        return result;
    }
};
