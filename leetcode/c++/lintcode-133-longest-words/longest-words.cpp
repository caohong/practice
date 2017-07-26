/*
 * http://www.lintcode.com/en/problem/longest-words/
 */


class Solution {
public:
    /**
     * @param dictionary: a vector of strings
     * @return: a vector of strings
     */
    vector<string> longestWords(vector<string> &dictionary) {
        vector<string> result;
        int maxsize = 0;
        stack<int> maxstack;
        for (int i = 0; i < dictionary.size(); i++) {
            if (dictionary[i].size() >= maxsize) {
                maxsize = dictionary[i].size();
                maxstack.push(i);
            }
        }
        while (!maxstack.empty()) {
            if (dictionary[maxstack.top()].size() == maxsize) {
                result.push_back(dictionary[maxstack.top()]);
                maxstack.pop();
            } else {
                break;
            }
        }
        return result;
    }
};
