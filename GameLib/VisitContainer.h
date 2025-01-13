/**
 * @file VisitContainer.h
 * @author mdoru
 *
 *
 */

#ifndef PROJECT1_GAMELIB_VISITCONTAINER_H
#define PROJECT1_GAMELIB_VISITCONTAINER_H

#include "ItemVisitor.h"

/**
 * VisitContainer is a visitor class designed to find a Container object.
 *
 */
class VisitContainer : public ItemVisitor
{
private:
    /// Flag indicating whether a Container has been visited.
    bool mIsFound = false;

    /// Pointer to the visited Container object.
    Container* mContainer = nullptr;

public:
    /**
     * Visit a Container object and store a reference to it.
     * This method sets mIsFound to true indicating a Container has been visited.
     *
     * @param container Pointer to the Container object being visited.
     */
    virtual void ContainerVisitor(Container* container) { mContainer = container; mIsFound = true; }

    /**
     * Retrieve the found Container object.
     * If no Container object has been visited, this will return nullptr.
     *
     * @return Container* Pointer to the found Container object or nullptr.
     */
    Container* GetContainer(){ return mContainer; }

    /**
     * Check if the container is found
     * If no Container object has been found, this will return false.
     *
     * @return true if the container is found.
     */
    bool GetIsFound(){return mIsFound; }



};

#endif //PROJECT1_GAMELIB_VISITCONTAINER_H
