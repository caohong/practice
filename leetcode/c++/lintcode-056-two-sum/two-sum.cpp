/*
 * http://www.lintcode.com/en/problem/two-sum/
 */

class Solution {
    public:
        /*
         *      * @param numbers: An array of Integer
         *           * @param target: target = numbers[index1] + numbers[index2]
         *                * @return: [index1 + 1, index2 + 1] (index1 < index2)
         *                     */
        vector<int> twoSum(vector<int> numbers, int target) {
            vector<int> result(2, -1);
            for (int i = 0; i < numbers.size(); i ++) {
                int expected = target - numbers[i];
                result[0] = i + 1;
                for (int j = i + 1; j < numbers.size(); j ++) {
                    if (numbers[j] == expected) {
                        result[1] = j + 1;
                        return result;
                    }
                }
            }
            return result;
        }
};
