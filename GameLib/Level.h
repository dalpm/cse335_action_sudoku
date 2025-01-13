/**
 * @file Level.h
 * @author mdoru
 *
 *
 */

#ifndef PROJECT1_GAMELIB_LEVEL_H
#define PROJECT1_GAMELIB_LEVEL_H

#include <vector>
#include <map>
#include <memory>
#include <string>

#include "ItemVisitor.h"
#include "ImageManager.h"

class Item;
class Game;
/**
 * The Level class is responsible for managing game items and declarations specific to a game level.
 */
class Level
{
private:
    /// The starting column of the solution/game baord
    int mStartCol = 0;

    /// The starting row of the solution/game baord
    int mStartRow = 0;

    /// A vector of shared pointers containing the game items for the level.
    std::vector<std::shared_ptr<Item>> mLevelItems;

    /// A map associating item IDs with their respective item declarations.
    std::map<std::string, std::shared_ptr<Item>> mMapDeclarations;

    /// The width of the level in pixels.
    int mLevelWidth = 0;

    /// The height of the level in pixels.
    int mLevelHeight = 0;

    /// The width of a single tile in the level.
    int mLevelTileWidth = 0;

    /// The height of a single tile in the level.
    int mLevelTileHeight = 1.0;

    /// Pointer to the game instance this level is associated with.
    Game* mGame = nullptr;

    /// Pointer to the image manager handling image resources for this level.
    ImageManager* mImageManager = nullptr;

    /// The 2D solution vector
    std::vector<std::vector<int>> mSolution;

public:
    Level(Game* game);

    void XmlDeclarations(wxXmlNode *node);

    void XmlItems(wxXmlNode *node);

    /**
     * Processes XML node for level information.
     * @param node The XML node to process.
     */
    void XmlLevel(wxXmlNode *node);

    /**
     * Processes XML node for game-related data.
     * @param node The XML node to process.
     */
    void XmlGame(wxXmlNode *node);

    /**
     * Retrieves the game items in the level.
     * @return Vector of shared pointers to the game items.
     */
    std::vector<std::shared_ptr<Item>> GetItems(){ return mLevelItems; }

    /**
     * Retrieves the width of the level.
     * @return Width of the level in pixels.
     */

    int GetWidth(){return mLevelWidth;}
    /**
     * Retrieves the height of the level.
     * @return Height of the level in pixels.
     */

    int GetHeight(){return mLevelHeight;}
    /**
     * Retrieves the width of a tile in the level.
     * @return Width of a tile in pixels.
     */

    int GetTileWidth(){return mLevelTileWidth;}

    /**
     * Retrieves the height of a tile in the level.
     * @return Height of a tile in pixels.
     */
    int GetTileHeight(){return mLevelTileHeight;}

    /**
     * Retrieve the solution grid for the game.
     *
     * @return A 2D vector representing the solution grid.
     */
    std::vector<std::vector<int>> GetSolution() {return mSolution; }

    /**
     * Get the starting column index for the game.
     *
     * @return The starting column index.
     */
    int GetStartCol() const { return mStartCol; }

    /**
     * Get the starting row index for the game.
     *
     * @return The starting row index.
     */
    int GetStartRow() const { return mStartRow; }
};

#endif //PROJECT1_GAMELIB_LEVEL_H
