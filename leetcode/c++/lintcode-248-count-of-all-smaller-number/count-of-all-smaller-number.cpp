/* 
 * http://www.lintcode.com/en/problem/count-of-smaller-number/
 */

#include <iostream>
#include <vector>
using namespace std;

void printData(const vector<int> data) {
    for (int i = 0; i < data.size(); i++) {
        cout << data[i] << ", ";
    }
    cout << endl;
}


class Solution {
public:

    int countOfSmallerNumber(vector<int> &A, int query) {
        int start = 0, end = A.size();
        if (end == 0 || A[0] >= query) {
            return 0;
        }
        int mid;
        while (start < end - 1) {
            mid = (end + start) >> 1;
            if (query > A[mid - 1]) {
                start = mid;
            } else {
                end = mid;
            }
        }
        return start;
    }

    /**
     * @param A: An integer array
     * @return: The number of element in the array that 
     *          are smaller that the given integer
     */
    vector<int> countOfSmallerNumber(vector<int> &A, vector<int> &queries) {
        sort(A.begin(), A.end());
        vector<int> result;
        for (int i = 0; i < queries.size(); i++) {
            result.push_back(countOfSmallerNumber(A, queries[i]));
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    vector<int> data = {1,2,4,6,7,8,10};
    vector<int> queries = {1, 5, 8};

    Solution s;
    vector<int> result = s.countOfSmallerNumber(data, queries);
    cout<< "count result:" << endl;
    printData(result);
    return 0;
}
