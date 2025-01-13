/**
 * @file Item.cpp
 * @author Owen
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

/**
 * Copy constructor for the Item class.
 *
 * Creates a new item object with attributes identical to an existing item.
 *
 * @param other The item object being copied.
 */
Item::Item(const Item& other){
    mLevel = other.mLevel;
    mWidth = other.mWidth;
    mHeight = other.mHeight;
    mRow = other.mRow;
    mCol = other.mCol;
    mID = other.mID;
    mImage = other.mImage;

    mTileHeight = other.mTileHeight;
    mTileWidth = other.mTileWidth;
}

/**
 * Destructor for the Item class.
 *
 * Cleans up resources associated with the item object.
 */
Item::~Item()
{

}

/**
 * Set the display properties for the item.
 *
 * Assigns the tile width and height based on the current level's tile dimensions.
 */
void Item::SetDisplayProperties(){
    mTileWidth = mLevel-> GetTileWidth();
    mTileHeight = mLevel->GetTileHeight();
}

/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* @param node The Xml node we are loading the item from
*/
void Item::XmlLoad(wxXmlNode* node)
{
    long w, h;
    node->GetAttribute(L"width", L"0").ToLong(&w);
    node->GetAttribute(L"height", L"0").ToLong(&h);


    mID = node->GetAttribute(L"id").ToStdString();
    mImage = std::wstring(node->GetAttribute(L"image"));
    mWidth = (int)w;
    mHeight = (int)h;

    SetDisplayProperties();
}

/**
 * The item constructor with a level.
 *
 * @param level the level with the item
 */
Item::Item(Level* level) {
    // Implementation here
    mLevel = level;
}

/**
 * Draw the item on a graphics context using a bitmap.
 *
 * @param graphics Pointer to the graphics context.
 * @param btm Pointer to the bitmap used for drawing.
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm){
    graphics->DrawBitmap(*btm,mCol*mTileWidth,(mRow+1)*mTileHeight - btm->GetHeight(), btm->GetWidth(), btm->GetHeight());
}

double Item::GetYLoc(){
    auto imageManager = mGame->GetIM();
    auto image = imageManager->GetBitmap(this->mID);
    return ((this->GetRow() + 1)*this->GetTileHeight() - image->GetHeight());
}


/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(double x, double y)
{
    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = GetColumn() - x;
    double testY = GetRow() - y + ((double) GetHeight()/(GetTileHeight() * 2.0));

    // Test to see if x, y are in the image
    if (testX > 1.5 || testX < 0.5 || testY < -0.5 || testY > 0.6 )
    {
        return false;
    }

    return true;
    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    //return !mImage->IsTransparent((int)testX, (int)testY);
}