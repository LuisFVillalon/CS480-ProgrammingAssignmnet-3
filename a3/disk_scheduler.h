/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assignment 3
File: disk_scheduler.h

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
 * Common interface implemented by every disk arm scheduling
 * algorithm. New algorithms can be added by implementing this
 * interface and registering an instance in main() without touching
 * any existing algorithm code.
*/

#ifndef SIMARM_CONSTANTS_H
#define SIMARM_CONSTANTS_H

namespace simarm {

const int MIN_CYLINDER = 0;
const int MAX_CYLINDER = 999;

/* Fixed starting position of the disk arm for every algorithm, so
 * that the algorithms can be compared fairly on identical
 * conditions. */
const int INITIAL_HEAD = 50;

} // namespace simarm

#endif // SIMARM_CONSTANTS_H


#ifndef SIMARM_DISK_SCHEDULER_H
#define SIMARM_DISK_SCHEDULER_H

#include <string>
#include <vector>

namespace simarm {

class DiskScheduler {
public:
    virtual ~DiskScheduler() = default;

    /* Human-readable name of the algorithm, used for reporting. */
    virtual std::string name() const = 0;

    /* Total head movement in cylinders required to service every
     * request, starting from the arm's initial position. */
    virtual long total_distance(const std::vector<int> &requests) const = 0;
};

} // namespace simarm

#endif // SIMARM_DISK_SCHEDULER_H
