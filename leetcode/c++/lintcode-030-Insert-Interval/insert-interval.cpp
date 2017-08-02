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
        // write your code here
        vector<Interval> result;
        int i = 0;
        if (intervals.empty()) {
            result.push_back(newInterval);
            return result;
        }
        
        bool overlap = false;
        bool done_at_first = false;
        
        if (newInterval.end < intervals[0].start) {
            result.push_back(newInterval);
            done_at_first = true;
        }
        
        for (; i < intervals.size(); i++) {
            if (!done_at_first && (newInterval.start <= intervals[i].end)) {
                overlap = true;
                break;
            } 
            result.push_back(intervals[i]);
        }
        
        if (done_at_first) {
            return result;
        }
        
        if (!overlap) {
            result.push_back(newInterval);
            return result;
        }
        
        Interval tmp(min(newInterval.start, intervals[i].start), 
                    max(newInterval.end, intervals[i].end));
        i++;
        for (; i < intervals.size(); i++) {
            if (intervals[i].start > newInterval.end) {
                break;
            } else {
                tmp.end = max(tmp.end, intervals[i].end);
            }
        }
        result.push_back(tmp);

        
        for (; i < intervals.size(); i++) {
            result.push_back(intervals[i]);
        }
        return result;
    }
};