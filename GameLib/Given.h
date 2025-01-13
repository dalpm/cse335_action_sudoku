/**
 * @file Given.h
 * @author Doruk Alp Mutlu
 *
 *
 */

#ifndef PROJECT1_GAMELIB_GIVEN_H
#define PROJECT1_GAMELIB_GIVEN_H

#include "Item.h"

/**
 * The Given class is a subclass of the Item class and is used to represent items with a specific value.
 */
class Given : public Item
{
private:

    /// The value of the given
    int mValue = 0;

public:

    /// Default constructor (disabled)
    Given() = delete;

    /**
     * Copy constructor (disabled)
     * @param other The Given object to copy from.
     */
    Given(const Given &);

    /// Assignment operator
    void operator=(const Given &) = delete;

    Given(Level *level);

    void XmlLoad(wxXmlNode* node) override;


    std::shared_ptr<Item> Clone() override;

    /**
     * Get the value of the given cell.
     *
     * @return The value of the cell.
     */
    int GetValue() override {return mValue;}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->GivenVisitor(this);}

};

#endif //PROJECT1_GAMELIB_GIVEN_H
