/*
 * http://www.lintcode.com/en/problem/recover-rotated-sorted-array/
 */


class Solution {
public:
    int findMinimumOffset(const vector<int> &nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i-1]) {
                return i;
            }
        }
        return 0;
    }

    void rotateString(vector<int> &nums, int offset) {
        if (offset < 1) {
            return;
        }
        reverseString(nums, 0, offset - 1);
        reverseString(nums, offset, nums.size() - 1);
        reverseString(nums, 0, nums.size() - 1);
    }
    
    void reverseString(vector<int> &nums, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(nums[i], nums[j]);
        }
    }
    
    void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    /*
     * @param nums: An integer
     * @return: 
     */
    
    void recoverRotatedSortedArray(vector<int> &nums) {
        int offset = findMinimumOffset(nums);
        rotateString(nums, offset);
    }
    
};
