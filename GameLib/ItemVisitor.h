/**
 * @file ItemVisitor.h
 * @author Doruk Alp Mutlu
 *
 *
 */

#ifndef PROJECT1_GAMELIB_ITEMVISITOR_H
#define PROJECT1_GAMELIB_ITEMVISITOR_H

class Container;
class Digit;
class Given;
class Scoreboard;
class Sparty;
class Sudoku;
class XRay;
class Banner;

/**
 * The Item (base) visitor class
 */
class ItemVisitor
{
private:

protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}

    /**
     * Visitor method for handling Digit objects.
     *
     * This method is called when visiting a Digit object using a visitor pattern.
     * Override this method in derived classes to perform actions specific to Digit objects.
     *
     * @param digit The Digit object being visited.
     */
    virtual void DigitVisitor(Digit* digit){}

    /**
     * Visitor method for handling Given objects.
     *
     * This method is called when visiting a Given object using a visitor pattern.
     * Override this method in derived classes to perform actions specific to Given objects.
     *
     * @param given The Given object being visited.
     */
    virtual void GivenVisitor(Given* given){}

    /**
     * Visitor method for handling Container objects.
     *
     * This method is called when visiting a Container object using a visitor pattern.
     * Override this method in derived classes to perform actions specific to Container objects.
     *
     * @param container The Container object being visited.
     */
    virtual void ContainerVisitor(Container* container){}

    /**
     * Visitor method for handling Sparty objects.
     *
     * This method is called when visiting a Sparty object using a visitor pattern.
     * Override this method in derived classes to perform actions specific to Sparty objects.
     *
     * @param sparty The Sparty object being visited.
     */
    virtual void SpartyVisitor(Sparty* sparty){}

    /**
     * Visitor method for handling XRay objects.
     *
     * This method is called when visiting a XRay object using a visitor pattern.
     * Override this method in derived classes to perform actions specific to XRay objects.
     *
     * @param xray The XRay object being visited.
     */
    virtual void XRayVisitor(XRay* xray){}

};

#endif //PROJECT1_GAMELIB_ITEMVISITOR_H
