/*
 * disk_scheduler.h
 *
 * Common interface implemented by every disk arm scheduling
 * algorithm. New algorithms can be added by implementing this
 * interface and registering an instance in main() without touching
 * any existing algorithm code.
 */

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
