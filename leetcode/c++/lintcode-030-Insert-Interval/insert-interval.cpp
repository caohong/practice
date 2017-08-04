/*
 * http://www.lintcode.com/en/problem/insert-interval/
 */


/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */


class Solution {
public:


    /*
     * @param intervals: Sorted interval list.
     * @param newInterval: new interval.
     * @return: A new interval list.
     */
    
    vector<Interval> insert(vector<Interval> intervals, Interval newInterval) {
        vector<Interval> result;
        int i = 0;
        for (; i < intervals.size(); i++) {
            if (intervals[i].start >= newInterval.start) {
                break;
            }
            result.push_back(intervals[i]);
        }
        
        if (result.empty() || (newInterval.start > result.back().end)) {
            result.push_back(newInterval);
        } else {
            result.back().end = max(newInterval.end, result.back().end);
        }
        
        for (; i < intervals.size(); i++) {
            if (intervals[i].start <= result.back().end) {
                result.back().end = max(result.back().end, intervals[i].end);
            } else {
                result.push_back(intervals[i]);
            }
        }
        
        return result;
    }
};
