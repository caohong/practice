/*
 * http://www.lintcode.com/en/problem/first-position-of-target/
 */


class Solution {
public:
    int binarySearch(vector<int> &array, int target) {
        int size = array.size();
        int start = 0, end = size - 1;
        int result = -1;
        if (size <= 0) {
            return -1;
        }
        while (size > 0) {
            int mid = start + size / 2;
            if (target > array[mid]) {
                start = mid + 1;
            } else if (target < array[mid]) {
                end = mid - 1;
            } else {
                result = mid;
                break;
            }
            size = end - start + 1;
        }
        
        while (result > 0 && array[result - 1] == target) {
            result--;
        }
        return result;
    }
};
