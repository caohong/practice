/* 
 * http://www.lintcode.com/en/problem/first-position-of-target/
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int binarySearch(vector<int> &array, int target) {
        int start = 0, end = array.size() - 1;
        int middle = array.size() / 2;
        int result = -1;
        
        if (start == end) {
            return (target == array[start]) ? 0 : -1;
        }

        while (start <= end) {
            //cout << start << "-->" << end << endl;
            if ((target < array[start]) || (target > array[end])) {
                return -1;
            }
            middle = end - start;
            middle = start + middle/2;
            if (target == array[middle]) {
                //cout << "target is equal: " << middle << endl;
                result = middle;
                break;
            }
            if (target > array[middle]) {
                start = middle + 1;
            } else {
                end = middle;
            }
        }
        while (result > 0 && array[result - 1] == target) {
            //cout << "check array result = " << result << ", array[result] = " << array[result] << endl;
            result--;
        }
        return result;
    }
};

int main() {
    vector<int> array = {1, 2, 3, 3, 4, 67, 191};
    int target = 1;

    Solution s;
    cout << s.binarySearch(array, target) << endl;
    return 0;
}
