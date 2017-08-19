#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    /**
     * @param nums: A list of integers.
     * @return: An integer denotes the middle number of the array.
     */
    int median(vector<int> &nums) {
        // write your code here
        int k = (nums.size() + 1) / 2;
        priority_queue<int> que;
        int len = nums.size();
        for(int i = 0; i < len; i ++) {
            if(que.size() == k) {
                if(nums[i] < que.top()) {
                    que.pop();
                    que.push(nums[i]);
                }
            }else {
                que.push(nums[i]);
            }
        }
        return que.top();
    }
};

void printVector(const vector<int> nums) {
    cout << "[";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << ", ";
    }
    cout << "]" << endl;
}

int main() {
    //vector<int> nums = {7, 9, 4, 5};
    vector<int> nums = {5, 9, 4, 7};
    Solution solution;
    int median = solution.median(nums);
    cout << median << endl;

    return 0;
}
