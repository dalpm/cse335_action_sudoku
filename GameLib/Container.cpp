/**
 * @file Container.cpp
 * @author Owen
 */

#include "pch.h"
#include "Container.h"
#include "Game.h"


/**
 * Remove an item from the container.
 *
 * This function removes the specified item from the container's list of items.
 *
 * @param item The item to be removed.
 */
void Container::Remove(std::shared_ptr<Item> item)
{
    mItems.erase(std::remove(mItems.begin(), mItems.end(), item), mItems.end());
}

/**
 * Get the first item within the container.
 *
 * This function retrieves the first item within the container, if any.
 *
 * @return A shared pointer to the first item, or nullptr if the container is empty.
 */
std::shared_ptr<Item> Container::GetItem()
{
    if (mItems.size() != 0)
    {
        return mItems[0];
    }
    return nullptr;
}

/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Container::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);

    mFrontImageName = std::wstring(node->GetAttribute(L"front"));
}

/**
 * Constructor
 * @param level Level this is a member of
 */
Container::Container(Level *level) : Item(level)
{
}

Container::Container(const Container& other) : Item(other){
    mFrontImageName = other.mFrontImageName;
    for (auto item : other.mItems)
    {
        std::shared_ptr<Item> item_to_add = item->Clone();
        item_to_add->SetGame(GetGame());
        mItems.push_back(item_to_add);
    }
}


/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> Container::Clone()
{
    return std::make_shared<Container>(*this);
}

/**
 * Add a digit to the container.
 * @param digit The digit item to be added
 */
void Container::AddDigit(std::shared_ptr<Item> digit){
    this->mItems.push_back(digit);
}

/**
 * Draw the container with its items.
 * @param graphics The graphics context for drawing
 * @param btm The bitmap used for drawing
 */
void Container::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm) {
    Item::Draw(graphics, btm);
    auto game = GetGame();
    auto ImageM = game->GetIM();
    // Insert the front image to map
    ImageM->InsertExtraFileName(GetID(), mFrontImageName);
    for (auto item: mItems)
    {
        item->Draw(graphics, ImageM->GetBitmap(item->GetID()));
    }
    // Draw the front image
    Item::Draw(graphics, ImageM->GetBitmapExtra(GetID()));


}

bool Container::HitTest(double x, double y){
    double testX = GetColumn() - x;
    double testY = GetRow() - y;

    // Test to see if x, y are in the image
    double distWidth = (double)GetWidth() / GetTileWidth();
    double distHeight = (double)GetHeight() / GetTileHeight();
    if (testX > distWidth / 2.0 || testX < - distWidth / 5.0 || testY > distHeight / 2.0 || testY < 0)
    {
        return false;
    }

    return true;
}