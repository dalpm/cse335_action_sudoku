/**
 * @file XRay.cpp
 * @author Owen
 */

#include "pch.h"
#include "XRay.h"
#include "Game.h"

/**
 * Add an item to the XRay.
 *
 * @param item The item to add to the XRay.
 */
void XRay::Add(std::shared_ptr<Item> item){
    if (std::find(mXRayContent.begin(), mXRayContent.end(), item) == mXRayContent.end()){
        ++mCapacity;
        mXRayContent.push_back(item);
    }
    else{

    }
}

/**
 * Get an item from the XRay based on its value.
 *
 * @param num The value of the item to retrieve.
 * @return A shared pointer to the item if found, or nullptr if not found.
 */
std::shared_ptr<Item> XRay::GetItem(int num){
    for (auto item : mXRayContent){
        if (num == item->GetValue()){
            return item;
        }
    }
    return nullptr;
}

/**
 * Check if the XRay contains an item with a specific value.
 *
 * @param num The value to check for.
 * @return True if the XRay contains an item with the specified value, false otherwise.
 */
bool XRay::CheckIfContainsNum(int num){
    for (auto item:mXRayContent){
        if (item->GetValue() == num){
            return true;
        }
    }
    return false;
}

/**
 * Remove an item from the XRay.
 *
 * @param item The item to remove from the XRay.
 */
void XRay::Remove(std::shared_ptr<Item> item)
{
    mXRayContent.erase(std::remove(mXRayContent.begin(), mXRayContent.end(), item), mXRayContent.end());
    --mCapacity;
}

/**
 * Check if the XRay contains an item with a specific value.
 *
 * @param itemToSearch The item to search for.
 * @return True if the XRay contains an item with the specified value, false otherwise.
 */
bool XRay::CheckIfContainsParticularNum(std::shared_ptr<Item> itemToSearch){
    for (auto item:mXRayContent){
        if (item == itemToSearch){
            return true;
        }
    }
    return false;
}

/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void XRay::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    long v;
    node->GetAttribute(L"capacity", L"0").ToLong(&v);
    mMaxCapacity = (int)v;

}

/**
 * Constructor
 * @param level Level this is a member of
 */
XRay::XRay(Level *level) : Item(level)
{
}

XRay::XRay(const XRay& other) : Item(other){
    mMaxCapacity = other.mMaxCapacity;
    mCapacity = other.mCapacity;
}


/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> XRay::Clone()
{
    return std::make_shared<XRay>(*this);
}