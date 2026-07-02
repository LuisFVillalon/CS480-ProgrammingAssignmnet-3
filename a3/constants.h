/*
 * constants.h
 *
 * Shared simulation constants.
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
