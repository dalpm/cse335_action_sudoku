/**
 * @file Background.cpp
 * @author Doruk Alp Mutlu
 */

#include "pch.h"
#include "Background.h"

/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Background::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
}

/**
 * Constructor
 * @param level Level this is a member of
 */
Background::Background(Level *level) : Item(level)
{

}

/**
 * Constructor
 * @param other to load other level
 */
Background::Background(const Background& other) : Item(other)
{

}

/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> Background::Clone()
{
    return std::make_shared<Background>(*this);
}
