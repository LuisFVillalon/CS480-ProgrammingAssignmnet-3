/*
 * simarm.cpp
 *
 * Disk arm scheduling simulator.
 *
 * Generates a random sequence of cylinder requests (each in the range
 * 0 - 999) and services that same sequence with three disk arm
 * scheduling algorithms:
 *
 *   1. FCFS  - First Come First Served
 *   2. SSTF  - Shortest Seek Time First
 *   3. SCAN  - Elevator algorithm
 *
 * For each algorithm the program prints the total number of cylinders
 * the disk arm had to travel (the "seek distance") to service the
 * whole request sequence, starting from a fixed initial head
 * position.
 *
 * Usage:
 *     simarm <number-of-requests>
 *
 * Example:
 *     simarm 64
 *
 * Build with the accompanying Makefile ("make"), which produces the
 * executable "simarm".
 */

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

namespace {

const int MIN_CYLINDER = 0;
const int MAX_CYLINDER = 999;
/* Fixed starting position of the disk arm for every algorithm, so
 * that the three algorithms can be compared fairly on identical
 * conditions. */
const int INITIAL_HEAD = 50;

/* Returns a vector of "n" random cylinder numbers in the range
 * [MIN_CYLINDER, MAX_CYLINDER]. */
std::vector<int> generate_requests(int n) {
    std::vector<int> requests(n);
    for (int i = 0; i < n; i++) {
        requests[i] = MIN_CYLINDER + std::rand() % (MAX_CYLINDER - MIN_CYLINDER + 1);
    }
    return requests;
}

/*
 * First Come First Served: service the requests in the exact order
 * they were generated.
 */
long fcfs_total_distance(const std::vector<int> &requests) {
    long total = 0;
    int current = INITIAL_HEAD;

    for (int cylinder : requests) {
        total += std::abs(current - cylinder);
        current = cylinder;
    }

    return total;
}

/*
 * Shortest Seek Time First: always service whichever remaining
 * request is closest to the arm's current position.
 */
long sstf_total_distance(const std::vector<int> &requests) {
    long total = 0;
    int current = INITIAL_HEAD;
    std::vector<bool> visited(requests.size(), false);

    for (size_t serviced = 0; serviced < requests.size(); serviced++) {
        int best_index = -1;
        int best_distance = 0;

        for (size_t i = 0; i < requests.size(); i++) {
            if (visited[i]) {
                continue;
            }
            int distance = std::abs(current - requests[i]);
            if (best_index == -1 || distance < best_distance) {
                best_index = static_cast<int>(i);
                best_distance = distance;
            }
        }

        total += best_distance;
        current = requests[best_index];
        visited[best_index] = true;
    }

    return total;
}

/*
 * SCAN (elevator) algorithm: the arm sweeps upward from its current
 * position toward the highest cylinder, servicing every request it
 * passes along the way, continues to the end of the disk (as a real
 * disk arm would), then reverses direction and sweeps back down,
 * servicing the remaining requests until the last one has been
 * reached.
 */
long scan_total_distance(const std::vector<int> &requests) {
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

} // namespace

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <length-of-sequence>\n";
        return EXIT_FAILURE;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "simarm: length of sequence must be a positive integer\n";
        return EXIT_FAILURE;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<int> requests = generate_requests(n);

    std::cout << "Generated sequence of " << n
              << " cylinder requests (initial head position: " << INITIAL_HEAD << "):\n";
    for (int i = 0; i < n; i++) {
        std::cout << requests[i] << (i == n - 1 ? "\n" : ", ");
    }
    std::cout << "\n";

    std::cout << "FCFS total head movement: " << fcfs_total_distance(requests) << " cylinders\n";
    std::cout << "SSTF total head movement: " << sstf_total_distance(requests) << " cylinders\n";
    std::cout << "SCAN total head movement: " << scan_total_distance(requests) << " cylinders\n";

    return EXIT_SUCCESS;
}
