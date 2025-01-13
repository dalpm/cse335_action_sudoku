/**
 * @file SpartyFinder.h
 * @author Doruk Alp Mutlu
 *
 *
 */

#ifndef PROJECT1_GAMELIB_SPARTYFINDER_H
#define PROJECT1_GAMELIB_SPARTYFINDER_H

#include "ItemVisitor.h"

/**
 * When visiting items in the game, SpartyFinder will capture a reference to a Sparty object,
 * allowing retrieval of this object later.
 */
class SpartyFinder : public ItemVisitor
{
private:
    /// The Sparty found
    Sparty* mSparty = nullptr;

public:

    /**
     * Visit a Sparty object and store a reference to it.
     * @param sparty Pointer to the Sparty object being visited.
     */
    virtual void SpartyVisitor(Sparty* sparty){ mSparty = sparty; }

    /**
     * If no Sparty object has been visited, this will return nullptr.
     *
     * @return Sparty* Pointer to the found Sparty object or nullptr.
     */
    Sparty* GetSparty(){ return mSparty; }
};

#endif //PROJECT1_GAMELIB_SPARTYFINDER_H
