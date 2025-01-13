/**
 * @file Digit.h
 * @author Owen
 *
 * Class for digit items
 */

#ifndef PROJECT1_GAMELIB_DIGIT_H
#define PROJECT1_GAMELIB_DIGIT_H

#include "Item.h"
#include "VisitDigit.h"

/**
 * Class for digit items
 */
class Digit : public Item
{
private:
    /// The digit Item's integer value (0-8)
    int mValue = 0;

public:
    /// Default constructor (disabled)
    Digit() = delete;

    /**
     * Default copy constructor (disabled)
     *
     * @param other the filler digit used to disable
     */
    Digit(const Digit &);

    /// Assignment operator
    void operator=(const Digit &) = delete;


    void XmlLoad(wxXmlNode* node) override;

    Digit(Level *level);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override {
        visitor->DigitVisitor(this);
    }

    std::shared_ptr<Item> Clone() override;

    /**
     * Retrieves the value of the digit.
     *
     * @return The value of the digit.
     */
    int GetValue() override {return mValue;}


};

#endif //PROJECT1_GAMELIB_DIGIT_H
