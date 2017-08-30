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
            if (numbers[i] > 0) {
                break;
            }
            
            if (numbers[i] == 0) {
                if (i < numbers.size() - 2 && (numbers[i + 1] == 0)
                    && (numbers[i + 2] == 0)) {
                    // there is three zero continuously
                    vector<int> tmp(3, 0);
                    result.push_back(tmp);
                }
                break;
            }
            
            int target = -numbers[i];
            
            int start = i + 1, end = numbers.size() - 1;
            bool start_updated = false, end_updated = false;
            while (start < end) {
                if (start_updated) {
                    if (numbers[start] == numbers[start - 1]) {
                        start++;
                        continue;
                    } else {
                        start_updated = false;
                    }
                }
                if (end_updated) {
                    if (numbers[end] == numbers[end + 1]) {
                        end--;
                        continue;
                    } else {
                        end_updated = false;
                    }
                }
                
                int sum = numbers[start] + numbers[end];
                if (sum == target) {
                    vector<int> tmp;
                    tmp.push_back(numbers[i]);
                    tmp.push_back(numbers[start]);
                    tmp.push_back(numbers[end]);
                    result.push_back(tmp);
                    start++;
                    start_updated = true;
                } else if (sum < target) {
                    start++;
                    start_updated = true;
                } else {
                    end--;
                    end_updated = true;
                }
            }

        }
        return result;
    }
};
