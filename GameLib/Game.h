/**
 * @file Game.h
 * @author Doruk Alp Mutlu
 *
 *
 */



#ifndef PROJECT1_GAMELIB_GAME_H
#define PROJECT1_GAMELIB_GAME_H

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <random>

#include "Item.h"
#include "Level.h"
#include "ImageManager.h"
#include "Scoreboard.h"
#include "Banner.h"

class ItemVisitor;
/**
 * Main class representing the game's state and operations.
 */

class Game
{
private:
    /// Current game level.
    int mLevel = 0;

    /// Collection of game items.
    std::vector<std::shared_ptr<Item>> mItems;

    /// Collection of game levels.
    std::vector<std::shared_ptr<Level>> mLevels;

    /// Manager for images used in the game.
    std::shared_ptr<ImageManager> mImageManager = std::make_shared<ImageManager>(this);

    /// The games scoreboard
    Scoreboard mScoreboard;

    /// the games banner
    Banner mBanner;

    /// Horizontal rendering offset.
    double mXOffset = 0.0;

    /// Vertical rendering offset.
    double mYOffset = 0.0;

    /// Rendering scale factor.
    double mScale = 1.0;

    /// Hardcoded virtual game screen width.
    int mVirtualWidth = 0;

    /// Hardcoded virtual game screen height.
    int mVirtualHeight = 0;

    /// Width of each tile in the game.
    int mTileWidth = 0;

    /// Height of each tile in the game.
    int mTileHeight = 0;

    /// The sparty that belongs to the game
    Sparty* mSparty = nullptr;

    /// Random number generator
    std::mt19937 mRandom;

    /// A 2D vector representing the solution grid of the game.
    std::vector<std::vector<int>> mSolution;

    /// The starting column index for some operations or references.
    int mStartCol = 0;

    /// The starting row index for some operations or references.
    int mStartRow = 0;

    /// A flag indicating whether a certain condition or feature is fully achieved or active.
    bool mFull = false;

    /// True if it is the start of a game
    bool mGameStart = true;

    /// True if it is the end of a game
    bool mGameEnd = false;

    /// How long the game should wait before advancing to the next level
    double mWaitTime = 0.0;

public:
    void OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height);

    void Load(std::wstring filename);

    void Clear();

    /**
     * Get height
     * @return height value
     */
    int GetHeight() {return mVirtualHeight;}

    /**
     * Get width
     * @return width value
     */
    int GetWidth() {return mVirtualWidth;}

    /**
     * Retrieves the game's scoreboard.
     * @return The current scoreboard.
     */
    Scoreboard GetScoreboard() { return mScoreboard; }

    /**
     * Sets the game's scoreboard.
     * @param sb The new scoreboard to set.
     */
    void SetScoreboard(Scoreboard sb) { mScoreboard = sb; }

    /**
     * Loads necessary files for the game.
     */
    void LoadFiles();

    void SetItems(std::vector<std::shared_ptr<Item>> items);

    void SetSparty();

    void SetLevel(int num);

    /**
     * Get the random number generator
     * @return Pointer to the random number generator
     */
    std::mt19937 &GetRandom() {return mRandom;}


    /**
     * Retrieves the width of each tile in the game.
     * @return Width of a tile.
     */
    int GetTileWidth(){return mTileWidth;}

    /**
     * Retrieves the height of each tile in the game.
     * @return Height of a tile.
     */
    int GetTileHeight(){return mTileHeight;}

    /**
     * Retrieves the ImageManager's IM.
     * @return Pointer to the ImageManager's IM.
     */
    ImageManager* GetIM(){return mImageManager->GetIM();}

    /**
     * Computes the maximum value on the sudoku board,
     * used in setting Sparty's speed.
     * @return max value on the sudoku grid as double
     */
    double GetMaxSudokuVal(){return (double)mSolution.size() - 1.0; }


    void Accept(ItemVisitor* visitor);

    void Update(double elapsed);

    void OnLeftDown(int x, int y);

    void OnSpaceDown();

    std::shared_ptr<Item> HitTest(double x, double y);

    void Solve();

    bool SpitNumber(int num);

    bool BoardIsFull();

    bool IsBoardCorrect();

    bool CellIsOccupied(int col, int row, std::shared_ptr<Item> exceptionItem);

    std::shared_ptr<Item> GetItemAtCell(int col, int row);

    void OnKeyHeadButtDown();

    void HitContainer();

    void RepositionItem(Container* container, std::shared_ptr<Item> item);

    std::pair<int, int> GetCellFromCoords(double x, double y);

    bool InGameBoard(int col, int row);
};

#endif //PROJECT1_GAMELIB_GAME_H
