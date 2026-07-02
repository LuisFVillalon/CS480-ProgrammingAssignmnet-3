/*
CS 480 - Operating Systems [2026 Summer Session]
Project: Assignment 3
File: simarm.cpp

Team Members:
- Luis Villalon: cssc3169 
- Bobby Bavongkhoun: cssc3110

Description:
 * Disk arm scheduling simulator.
 
 * Generates a random sequence of cylinder requests (each in the range
 * 0 - 999) and services that same sequence with a set of disk arm
 * scheduling algorithms (FCFS, SSTF, SCAN, ...). For each algorithm
 * the program prints the total number of cylinders the disk arm had
 * to travel (the "seek distance") to service the whole request
 * sequence, starting from a fixed initial head position.

 * Usage:
 *     simarm <number-of-requests>

 * Example:
 *     simarm 64

 * Build with the accompanying Makefile ("make"), which produces the
 * executable "simarm".
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

#include "constants.h"
#include "disk_scheduler.h"
#include "fcfs_scheduler.h"
#include "request_generator.h"
#include "scan_scheduler.h"
#include "sstf_scheduler.h"

using namespace simarm;

int main(int argc, char *argv[]) {
    // Require exactly one argument beyond the program name (the sequence length).
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <length-of-sequence>\n";
        return EXIT_FAILURE;
    }

    // Parse the requested sequence length and reject non-positive values.
    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "simarm: length of sequence must be a positive integer\n";
        return EXIT_FAILURE;
    }

    // Seed the RNG from the current time so each run produces a different sequence.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Generate n random cylinder requests to feed each scheduler.
    std::vector<int> requests = generate_requests(n);

    // Announce the generated sequence and the disk head's starting cylinder.
    std::cout << "Generated sequence of " << n
              << " cylinder requests (initial head position: " << INITIAL_HEAD << "):\n";
    // Print the requests as a comma-separated list.
    for (int i = 0; i < n; i++) {
        std::cout << requests[i] << (i == n - 1 ? "\n" : ", ");
    }
    std::cout << "\n";

    /* Register every algorithm to run here. Adding a new algorithm
     * only requires implementing DiskScheduler and adding an entry
     * to this list. */
    std::vector<std::unique_ptr<DiskScheduler>> schedulers;
    schedulers.push_back(std::make_unique<FcfsScheduler>());
    schedulers.push_back(std::make_unique<SstfScheduler>());
    schedulers.push_back(std::make_unique<ScanScheduler>());

    // Run the same request sequence through each registered scheduler and
    // report the total head movement it produces, for comparison.
    for (const auto &scheduler : schedulers) {
        std::cout << scheduler->name() << " total head movement: "
                  << scheduler->total_distance(requests) << " cylinders\n";
    }

    return EXIT_SUCCESS;
}
