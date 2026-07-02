// Generates a random sequence of disk cylinder requests used to drive and
// compare the different disk scheduling algorithms.
#include "request_generator.h"

#include <cstdlib>

#include "constants.h"

namespace simarm {

// Generates n random cylinder requests uniformly distributed over
// [MIN_CYLINDER, MAX_CYLINDER].
std::vector<int> generate_requests(int n) {
    std::vector<int> requests(n);
    for (int i = 0; i < n; i++) {
        requests[i] = MIN_CYLINDER + std::rand() % (MAX_CYLINDER - MIN_CYLINDER + 1);
    }
    return requests;
}

} // namespace simarm
