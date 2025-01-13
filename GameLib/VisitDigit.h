/**
 * @file VisitDigit.h
 * @author mdoru
 *
 *
 */

#ifndef PROJECT1_GAMELIB_VISITDIGIT_H
#define PROJECT1_GAMELIB_VISITDIGIT_H

#include "ItemVisitor.h"

/**
 * @class VisitDigit
 * A visitor class to handle the visitation of a Digit.
 *
 * This class provides a mechanism to visit a Digit and record
 * the visitation status and the visited Digit object.
 */
class VisitDigit : public ItemVisitor
{
private:
    /// Flag indicating whether a Given has been visited.
    bool mIsFound = false;

    /// Pointer to the visited Given object.
    Digit* mDigit = nullptr;

public:
    /**
     * Visits a Digit object and records the visitation.
     *
     * @param digit Pointer to the Digit object to be visited.
     */
    virtual void DigitVisitor(Digit* digit) {mDigit = digit; mIsFound = true; }

    /**
     * Checks if a Digit has been visited.
     *
     * @return true if a Digit has been visited, false otherwise.
     */
    bool IsFound() {return mIsFound; }
};

#endif //PROJECT1_GAMELIB_VISITDIGIT_H
