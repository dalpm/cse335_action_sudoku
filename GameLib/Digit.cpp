/**
 * @file Digit.cpp
 * @author Owen
 */

#include "pch.h"
#include "Digit.h"
#include "Game.h"


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Digit::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    long v;
    node->GetAttribute(L"value", L"0").ToLong(&v);

    mValue = (int)v;

}

/**
 * Constructor
 * @param level Level this is a member of
 */
Digit::Digit(Level *level) : Item(level)
{
}

Digit::Digit(const Digit& other) : Item(other){
    mValue = other.mValue;
}

/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> Digit::Clone()
{
    return std::make_shared<Digit>(*this);
}
