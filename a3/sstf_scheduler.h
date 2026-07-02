/*
 * sstf_scheduler.h
 *
 * Shortest Seek Time First: always service whichever remaining
 * request is closest to the arm's current position.
 */

#ifndef SIMARM_SSTF_SCHEDULER_H
#define SIMARM_SSTF_SCHEDULER_H

#include "disk_scheduler.h"

namespace simarm {

class SstfScheduler : public DiskScheduler {
public:
    // Returns the scheduler's display name ("SSTF"), used for reporting results.
    std::string name() const override;
    // Computes the total arm movement for servicing the given requests in SSTF order.
    long total_distance(const std::vector<int> &requests) const override;
};

} // namespace simarm

#endif // SIMARM_SSTF_SCHEDULER_H
