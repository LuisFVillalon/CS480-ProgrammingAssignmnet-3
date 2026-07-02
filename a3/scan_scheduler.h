/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assignment 3
File: scan_scheduler.h

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
SCAN (elevator) algorithm: the arm sweeps upward from its current
position toward the highest cylinder, servicing every request it
passes along the way, continues to the end of the disk (as a real
disk arm would), then reverses direction and sweeps back down,
servicing the remaining requests until the last one has been
reached.
*/


#ifndef SIMARM_SCAN_SCHEDULER_H
#define SIMARM_SCAN_SCHEDULER_H

#include "disk_scheduler.h"

namespace simarm {

// Disk scheduler implementing the SCAN (elevator) algorithm.
class ScanScheduler : public DiskScheduler {
public:
    // Returns the scheduler's display name (e.g. "SCAN"), used in output/reports.
    std::string name() const override;
    // Computes the total seek distance to service all requests using SCAN ordering.
    long total_distance(const std::vector<int> &requests) const override;
};

} // namespace simarm

#endif // SIMARM_SCAN_SCHEDULER_H
