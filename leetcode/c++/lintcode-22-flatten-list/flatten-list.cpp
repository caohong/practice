/*
 * http://www.lintcode.com/en/problem/flatten-list
 */


class Solution {
public:
    void flatten2list(vector<int> &result, const vector<NestedInteger> &nestedList) {
        for (int i = 0; i < nestedList.size(); i ++) {
            if (nestedList[i].isInteger()) {
                result.push_back(nestedList[i].getInteger());
            } else {
                flatten2list(result, nestedList[i].getList());
            }
        }
    }
    
    // @param nestedList a list of NestedInteger
    // @return a list of integer
    vector<int> flatten(vector<NestedInteger> &nestedList) {
        vector<int> result;
        flatten2list(result, nestedList);
        return result;
    }
};
