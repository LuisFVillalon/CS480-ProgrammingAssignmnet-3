/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assignment 3
File: sstf_scheduler.cpp

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
Implements SstfScheduler::total_distance: repeatedly scans the
remaining requests to find the one nearest the current head
position, services it, and accumulates the seek distance until
every request has been visited.
*/

#include "sstf_scheduler.h"

#include <cstdlib>

#include "constants.h"

namespace simarm {

std::string SstfScheduler::name() const {
    return "Shortest Seek Time First (SSTF)";
}

long SstfScheduler::total_distance(const std::vector<int> &requests) const {
    long total = 0;
    int current = INITIAL_HEAD;
    // Tracks which requests have already been serviced.
    std::vector<bool> visited(requests.size(), false);

    // Repeat once per request until every request has been serviced.
    for (size_t serviced = 0; serviced < requests.size(); serviced++) {
        // index of the closest unvisited request found so far
        int best_index = -1; 
        // seek distance to that closest request        
        int best_distance = 0; 

        // Scan all requests to find the one nearest the current head position.
        for (size_t i = 0; i < requests.size(); i++) {
            if (visited[i]) {
                continue;
            }
            // Distance the head would have to travel to service this request.
            int distance = std::abs(current - requests[i]);
            // Keep this request if it's the first candidate or closer than the best found so far.
            if (best_index == -1 || distance < best_distance) {
                best_index = static_cast<int>(i);
                best_distance = distance;
            }
        }
        // accumulate the seek distance traveled
        total += best_distance; 
        // move the head to the serviced request
        current = requests[best_index];
        // mark it so it isn't chosen again
        visited[best_index] = true; 
    }
    // total seek distance across all requests
    return total; 
}

} // namespace simarm
