/**
 * @file Background.h
 * @author Doruk Alp Mutlu
 *
 *
 */

#ifndef PROJECT1_GAMELIB_BACKGROUND_H
#define PROJECT1_GAMELIB_BACKGROUND_H

#include "Item.h"

/**
 * Represents the background of the game. Extends the item class
 */
class Background: public Item
{
public:
    /// Default constructor (disabled)
    Background() = delete;

    /// Copy constructor (disabled)
    Background(const Background &);

    /// Assignment operator
    void operator=(const Background &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    Background(Level *level);

    /**
     * The visitor function for backgrounds
     *
     * @param visitor the current visitor
     */
    void Accept(ItemVisitor* visitor) override {}

    /// Clone
    std::shared_ptr<Item> Clone() override;

};

#endif //PROJECT1_GAMELIB_BACKGROUND_H
