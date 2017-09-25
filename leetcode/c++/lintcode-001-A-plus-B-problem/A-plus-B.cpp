class Solution {
    public:
        /*
         * @param a: The first integer
         * @param b: The second integer
         * @return: The sum of a and b
         */
        int aplusb(int a, int b) {
            while (b != 0) {
                int _a = a ^ b;
                int _b = (a & b) << 1;
                a = _a;
                b = _b;
            }
            return a;
        }
};
