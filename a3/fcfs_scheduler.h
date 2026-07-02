/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assignment 3
File: fcfs_scheduler.h

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
First Come First Served: service the requests in the exact order they were generated.
*/

#ifndef SIMARM_FCFS_SCHEDULER_H 
#define SIMARM_FCFS_SCHEDULER_H 

#include "disk_scheduler.h" 

namespace simarm { 

class FcfsScheduler : public DiskScheduler { 
public:
    // returns the human-readable name of this scheduling algorithm
    std::string name() const override; 
    // computes total head movement for servicing requests in the given (FCFS) order
    long total_distance(const std::vector<int> &requests) const override; 
}; 

} // namespace simarm

#endif // SIMARM_FCFS_SCHEDULER_H
