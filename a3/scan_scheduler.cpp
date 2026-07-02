/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assignment 3
File: scan_scheduler.cpp

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
Implements ScanScheduler, which computes total seek distance under
the SCAN (elevator) algorithm: sort pending requests, sweep upward
from the initial head position to the highest cylinder (servicing
requests along the way and continuing to the disk's end), then
sweep back down servicing the remaining requests below the start.
*/

#include "scan_scheduler.h"

#include <algorithm>
#include <cstdlib>

#include "constants.h"

namespace simarm {

std::string ScanScheduler::name() const {
    return "SCAN (elevator)";
}

long ScanScheduler::total_distance(const std::vector<int> &requests) const {
    long total = 0;
    int current = INITIAL_HEAD;

    std::vector<int> sorted = requests;
    std::sort(sorted.begin(), sorted.end());

    /* Find the split point between requests below and above the
     * current head position. */
    size_t split = 0;
    while (split < sorted.size() && sorted[split] < current) {
        split++;
    }

    /* Sweep upward, servicing requests >= current position. */
    for (size_t i = split; i < sorted.size(); i++) {
        total += std::abs(current - sorted[i]);
        current = sorted[i];
    }

    /* Continue to the end of the disk if we haven't reached it yet
     * and there is anything left to service on the way back. */
    if (split > 0 && current != MAX_CYLINDER) {
        total += std::abs(current - MAX_CYLINDER);
        current = MAX_CYLINDER;
    }

    /* Sweep back downward, servicing the remaining requests. */
    for (size_t i = split; i-- > 0;) {
        total += std::abs(current - sorted[i]);
        current = sorted[i];
    }

    return total;
}

} // namespace simarm
