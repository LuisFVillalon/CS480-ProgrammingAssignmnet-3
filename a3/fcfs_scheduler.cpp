// Implements the First-Come-First-Served (FCFS) disk scheduling algorithm,
// servicing requests in the order they arrive and computing total head seek distance.
#include "fcfs_scheduler.h"

#include <cstdlib>

#include "constants.h"

namespace simarm {

std::string FcfsScheduler::name() const {
    // scheduler's display name
    return "Fist Come First Serve (FCFS)"; 
}

long FcfsScheduler::total_distance(const std::vector<int> &requests) const {
    // accumulated head movement
    long total = 0;           
    // head starts at the initial cylinder
    int current = INITIAL_HEAD; 
    // service requests in arrival order (FCFS)
    for (int cylinder : requests) { 
        // distance from current head position to this request
        total += std::abs(current - cylinder); 
        // move head to the serviced cylinder
        current = cylinder; 
    }
    // total seek distance for this ordering
    return total; 
}

} // namespace simarm
