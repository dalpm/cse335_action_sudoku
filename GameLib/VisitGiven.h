/**
 * @file VisitGiven.h
 * @author Joe Cook
 *
 *
 */

#ifndef PROJECT1_GAMELIB_VISITGIVEN_H
#define PROJECT1_GAMELIB_VISITGIVEN_H

#include "ItemVisitor.h"
#include "Given.h"

/**
 * @class VisitGiven
 * A visitor class designed to handle the visitation of a Given object.
 *
 * This class provides functionality to visit a Given and store information
 * about the visitation status and the specific Given object that was visited.
 */
class VisitGiven : public ItemVisitor
{
private:
    /// Flag indicating whether a Given has been visited.
    bool mIsFound = false;

    /// Pointer to the visited Given object.
    Given* mGiven = nullptr;

public:
    /**
     * Method to visit a Given object and record the visitation details.
     *
     * @param given Pointer to the Given object that needs to be visited.
     */
    virtual void GivenVisitor(Given* given) {mGiven = given; mIsFound = true; }

    /**
     * Indicates the visitation status of a Given object.
     *
     * @return true if a Given object has been visited, false otherwise.
     */
    bool IsFound() {return mIsFound; }
};

#endif //PROJECT1_GAMELIB_VISITGIVEN_H
