/*
 * http://www.lintcode.com/en/problem/rotate-string/
 */


class Solution {
public:

    void swap(char& a, char& b) {
        char tmp = a;
        a = b;
        b = tmp;
    }
    
    /**
     * @param str: a string
     * @param offset: an integer
     * @return: nothing
     */
    void rotateString(string &str,int offset){
        int rotated = 0, i = 0, round = 0;
        char pop_char = str[0];
        int size = str.size();
        
        if (size < 2) {
            return;
        }
        
        while (rotated < size) {
            int change_pos = (i + offset) % size;
            swap(pop_char, str[change_pos]);
            rotated++;
            i = change_pos;
            if (i == round) {
                i++;
                round++;
                pop_char = str[i];
            }
        }
        
    }
};
