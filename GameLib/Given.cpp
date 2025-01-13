/**
 * @file Given.cpp
 * @author Doruk Alp Mutlu
 */

#include "pch.h"
#include "Given.h"

/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Given::XmlLoad(wxXmlNode* node)
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
Given::Given(Level *level) : Item(level)
{
}

Given::Given(const Given& other) : Item(other){
    mValue = other.mValue;
}

/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> Given::Clone()
{
    return std::make_shared<Given>(*this);
}


