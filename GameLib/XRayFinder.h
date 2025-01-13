/**
 * @file XRayFinder.h
 * @author Connor Sheridan
 *
 * XRay visitor class
 */

#ifndef PROJECT1_GAMELIB_XRAYFINDER_H
#define PROJECT1_GAMELIB_XRAYFINDER_H

#include "ItemVisitor.h"

/**
 * The XRay visitor class
 */
class XRayFinder : public ItemVisitor
{
private:
    /// The XRay found
    XRay* mXRay = nullptr;

public:

    /**
     * Visit a XRay object and store a reference to it.
     * @param xray Pointer to the XRay object being visited.
     */
    virtual void XRayVisitor(XRay* xray){ mXRay = xray; }


    /**
     * If no XRay object has been visited, this will return nullptr.
     *
     * @return XRay* Pointer to the found XRay object or nullptr.
     */
    XRay* GetXRay(){ return mXRay; }
};

#endif //PROJECT1_GAMELIB_XRAYFINDER_H
