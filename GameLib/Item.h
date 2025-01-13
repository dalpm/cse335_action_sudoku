/**
 * @file Item.h
 * @author Owen
 *
 * Base class for any item in our game
 */

#ifndef PROJECT1_GAMELIB_ITEM_H
#define PROJECT1_GAMELIB_ITEM_H

#include <string>
#include "ItemVisitor.h"

class Game;
class Level;

/**
 * Base class for any item in our game
 */
class Item
{
private:

    /// A pointer to the level to which the item belongs.
    Level* mLevel = nullptr;

    /// A pointer to the game to which the item belongs.
    Game* mGame = nullptr;

    /// The unique identifier of the item.
    std::string mID;

    /// The width of the item.
    int mWidth = 0;

    /// The height of the item.
    int mHeight = 0;

    /// The row position of the item within the game.
    double mRow = 0;

    /// The column position of the item within the game.
    double mCol = 0;

    /// The image associated with the item.
    std::wstring mImage;

    /// The width of a tile for this item.
    int mTileWidth = 0;

    /// The height of a tile for this item.
    int mTileHeight = 0;

protected:
    Item(Level* level);

public:
    /// Default constructor (disabled)
    Item() = delete;

    Item(const Item &);

    ~Item();


    virtual void XmlLoad(wxXmlNode *node);

    void SetDisplayProperties();


    /**
     * Set the row position of the item within the game.
     *
     * @param r The new row position to set.
     */
    void SetRow(double r){mRow = r;}

    /**
     * Set the column position of the item within the game.
     *
     * @param c The new column position to set.
     */
    void SetColumn(double c){mCol = c;}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) = 0;

    /**
     * The virtual Clone function
     * @return
     */
    virtual std::shared_ptr<Item> Clone() = 0;

    /**
     * Draw this item
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm);

    /**
     * Set the associated game for this item.
     *
     * @param game The game to be associated with.
     */
    void SetGame(Game* game) { mGame = game; }

    /**
     * Retrieve the game associated with this item.
     *
     * @return Pointer to the associated game.
     */
    Game* GetGame() { return mGame; }

    /**
     * Retrieves the current X-location of Sparty.
     * @return X-location based on the column and tile width.
     */
    double GetXLoc(){return this->GetColumn()*(this->GetTileWidth());}

    /**
     * Retrieves the current Y-location of Sparty.
     * @return Y-location based on the row, tile height, and image height.
     */
    virtual double GetYLoc();


    /**
     * Retrieve the image associated with this item.
     *
     * @return The image of the item.
     */
    std::wstring GetImage(){return mImage;}

    /**
     * Retrieve the unique identifier of this item.
     *
     * @return The ID of the item.
     */
    std::string GetID(){return mID;}

    /**
     * Retrieve the column position of this item.
     *
     * @return The column position of the item.
     */
    double GetColumn() const{return mCol;}

    /**
     * Retrieve the row position of this item.
     *
     * @return The row position of the item.
     */
    double GetRow() const {return mRow; }

    /**
     * Fetches the width.
     *
     * @return The width value.
     */
    int GetWidth() const {return mWidth; }

    /**
     * Fetches the height.
     *
     * @return The height value.
     */
    int GetHeight() const {return mHeight; }

    /**
     * Retrieve the tile width associated with this item.
     *
     * @return The tile width.
     */
    double GetTileWidth() const {return mTileWidth; }

    /**
     * Retrieve the tile height associated with this item.
     *
     * @return The tile height.
     */
    double GetTileHeight() const {return mTileHeight; }

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Fetches the value. This is a virtual function and may be overridden by derived classes.
     *
     * @return The value, which defaults to -1 if not overridden.
     */
    virtual int GetValue() {return -1; };

    virtual bool HitTest(double x, double y);
};

#endif //PROJECT1_GAMELIB_ITEM_H
