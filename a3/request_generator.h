/*
 * request_generator.h
 *
 * Generates random cylinder request sequences.
 */

#ifndef SIMARM_REQUEST_GENERATOR_H
#define SIMARM_REQUEST_GENERATOR_H

#include <vector>

namespace simarm {

/* Returns a vector of "n" random cylinder numbers in the range
 * [MIN_CYLINDER, MAX_CYLINDER]. "n" comes from the command-line argument
 * passed to simarm */
std::vector<int> generate_requests(int n);

} // namespace simarm

#endif // SIMARM_REQUEST_GENERATOR_H
