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


    void sort(vector<int> &data) {
        int size = data.size();
        for (int i = size; i >= 0; i--) {
            bool do_swap = false;
            for (int j = 0; j < i; j ++) {
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
        int i = 1;
        if (A.size() == 0 || A[0] >= query) {
            return 0;
        }
        for (; i < A.size(); i++) {
            if (A[i] >= query) {
                break;
            }
        }
        return i;
    }

    /**
     * @param A: An integer array
     * @return: The number of element in the array that 
     *          are smaller that the given integer
     */
    vector<int> countOfSmallerNumber(vector<int> &A, vector<int> &queries) {
        sort(A);
        vector<int> result;
        for (int i = 0; i < queries.size(); i++) {
            result.push_back(countOfSmallerNumber(A, queries[i]));
        }
        return result;
    }
};

int main() {
    vector<int> data = {32, 67};
    vector<int> queries = {65, 50};

    Solution s;
    cout<< "sort result:" << endl;
    s.sort(data);
    printData(data);
    vector<int> result = s.countOfSmallerNumber(data, queries);

    cout<< "count result:" << endl;
    printData(result);
    return 0;
}
