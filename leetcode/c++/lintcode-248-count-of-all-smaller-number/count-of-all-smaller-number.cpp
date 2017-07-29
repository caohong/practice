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


    void swap(int& a, int& b) {
        int tmp = a;
        a = b;
        b = tmp;
    }


    void my_sort(vector<int> &data) {
        int size = data.size();
        for (int i = size; i > 0; i--) {
            bool do_swap = false;
            for (int j = 0; j < i-1; j ++) {
                if (data[j] > data[j+1]) {
                    swap(data[j], data[j+1]);
                    do_swap = true;
                }
            }
            if (!do_swap) {
                break;
            }
        }
    }

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
        my_sort(A);
        printData(A);

        //sort(A.begin(), A.end());
        //printData(A);
        vector<int> result;
        for (int i = 0; i < queries.size(); i++) {
            result.push_back(countOfSmallerNumber(A, queries[i]));
        }
        return result;
    }
};

int main(int argc, char* argv[]) {
    vector<int> data = {55,81,56,91,35,92,10,53,27,94,64,45,19,44,52,19,79,12,16,90,97,33,73,2,20,68,19,7,17,62,45,48,62,26,85,4,63,67,56,16};
    vector<int> queries = {10,43,2,17,28,75,75,12};
    //expected: [3,16,0,7,14,32,32,4]

    Solution s;
    vector<int> result = s.countOfSmallerNumber(data, queries);
    cout<< "count result:" << endl;
    printData(result);
    return 0;
}
