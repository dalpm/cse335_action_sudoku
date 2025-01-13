/**
 * @file Game.cpp
 * @author Doruk Alp Mutlu
 */

#include "pch.h"
#include <algorithm>
#include "ItemVisitor.h"
#include "SpartyFinder.h"
#include "XRayFinder.h"
#include "VisitDigit.h"
#include "Game.h"
#include "Item.h"
#include "Level.h"
#include "Sparty.h"
#include "XRay.h"
#include "Container.h"
#include "VisitGiven.h"
#include "VisitContainer.h"

/// The constant representing how long the game should wait before advancing
const double WAIT_TIME = 5.0;

/**
 * Draw the game using the provided graphics context.
 *
 * @param graphics The graphics context to draw on.
 * @param width The width of the drawing area.
 * @param height The height of the drawing area.
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{

    // Determine the size of the playing area in pixels
    // This is up to you...
    int pixelWidth = mVirtualWidth;
    int pixelHeight = mVirtualHeight;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for (auto item: mItems)
    {
        item->Draw(graphics, mImageManager->GetBitmap(item->GetID()));
    }
    std::string state = std::to_string(mLevel);
    mBanner.SetBannerMessage(state);

    mBanner.DrawLevelIntroBanner(graphics, pixelWidth, pixelHeight);

    if (!mGameStart){
        mScoreboard.Draw(graphics);
    }


    if (BoardIsFull())
    {
        if (IsBoardCorrect())
        {
            mBanner.SetBannerMessage("C");
            mBanner.DrawGameStatusBanner(graphics, pixelWidth, pixelHeight);

        }
        else
        {
            mBanner.SetBannerMessage("I");
            mBanner.DrawGameStatusBanner(graphics, pixelWidth, pixelHeight);
        }
    }

    if (mFull)
    {
        mBanner.SetBannerMessage("F");
        mBanner.DrawIMFullBanner(graphics, pixelWidth, pixelHeight);
    }

    graphics->PopState();
}

/**
 * Loads game levels from XML files.
 *
 * This function loads multiple game levels from XML files located in the "levels"
 * directory. It loads levels with filenames "level0.xml," "level1.xml," "level2.xml,"
 * and "level3.xml" into the game.
 */
void Game::LoadFiles(){
    std::wstring filename0 = L"levels/level0.xml";
    Load(filename0);
    std::wstring filename1 = L"levels/level1.xml";
    Load(filename1);
    std::wstring filename2 = L"levels/level2.xml";
    Load(filename2);
    std::wstring filename3 = L"levels/level3.xml";
    Load(filename3);
}




/**
 * Load the Level from a XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the level from.
 */
void Game::Load(std::wstring filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Level file");
        return;
    }

    if (!mItems.empty())
    {
        Clear();
    }

    std::shared_ptr<Level> level = std::make_shared<Level>(this);

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    level->XmlLevel(root);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"game"){
            level->XmlGame(child);
        }
        else if(name == L"declarations"){
            auto item = child->GetChildren();
            level->XmlDeclarations(item);
        }
        else if(name == L"items"){
            auto item = child->GetChildren();
            level->XmlItems(item);
        }
    }
    mLevels.push_back(level);

    // Insert the stuff into Image Map
    auto items = level->GetItems();
    for (auto item:items){
        auto name = item->GetImage();
        if (name != ""){
            mImageManager->InsertFileName(item->GetID() ,item->GetImage());
        }
    }

}

/**
 * Clear the game data.
 *
 * Deletes all known items in the game.
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Set game items.
 * Clones the provided items and adds them to the game.
 * @param items The items to set in the game.
 */
void Game::SetItems(std::vector<std::shared_ptr<Item>> items){
    for (auto item : items){
        std::shared_ptr<Item> item_to_add = item->Clone();
        item_to_add->SetGame(this);
        mItems.push_back(item_to_add);
    }
}

/**
 * Sets the Sparty character for the game.
 *
 * This function searches for the Sparty character in the game and assigns it
 * as the game's main character (mSparty). It utilizes the SpartyFinder visitor
 * to locate the Sparty character within the game's item list.
 */
void Game::SetSparty(){
    SpartyFinder visitor;
    Accept(&visitor);
    mSparty =  visitor.GetSparty();
}

/**
 * Set the game state for a specified level.
 * Resets the game and initializes it to the configuration specified by the provided level number.
 *
 * @param num The level number to set the game to.
 */
void Game::SetLevel(int num){
    mBanner.ResetBanner();
    Clear();
    std::shared_ptr<Level> level = mLevels.at(num);
    mTileWidth = level->GetTileWidth();
    mTileHeight = level->GetTileHeight();
    mVirtualWidth = level->GetTileWidth() * level->GetWidth();
    mVirtualHeight = level->GetTileHeight() * level->GetHeight();
    mSolution = level->GetSolution();
    mStartCol = level->GetStartCol();
    mStartRow = level->GetStartRow();
    mLevel = num;
    auto items = level->GetItems();
    SetItems(items);
    SetSparty();
    mGameStart = true;
    mGameEnd = false;
    mScoreboard.ResetTimer();
    mWaitTime = WAIT_TIME;
}

/**
 * Process a visitor for the collection of game items.
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Update game state.
 * Iterates through all game items and updates them based on the elapsed time.
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    mBanner.Update(elapsed);
    for(auto item : mItems)
    {
        item->Update(elapsed);
    }


    if (mFull)
    {
        mBanner.SetBannerMessage("F");
        if (mBanner.GetYLoc() == 0){
            mBanner.SetYLoc(GetHeight());
        }
        else if(mBanner.GetYLoc() < -50){
            mBanner.SetYLoc(0);
            mFull = false;
        }
        else
        {
            mBanner.SetYLoc(mBanner.GetYLoc() - elapsed * 300);
        }
    }


    if(!mBanner.GetBannerVisible())
    {
        mGameStart = false;

    }

    if(!mGameStart && !mGameEnd)
    {
        mScoreboard.Tick(elapsed);
    }

    if(this->BoardIsFull())
    {
        mGameEnd = true;

        if(this->IsBoardCorrect())
        {
            mBanner.SetBannerMessage("C");

            mWaitTime -= elapsed;
            if (mWaitTime < 0){
                if (mLevel == mLevels.size()-1){
                    this->SetLevel(mLevel);
                } else {
                    this->SetLevel(mLevel + 1);
                }
            }
        } else {
            mBanner.SetBannerMessage("I");

            mWaitTime -= elapsed;
            if (mWaitTime < 0){
                this->SetLevel(mLevel);
            }
        }
    }
}

/**
 * Handle mouse left-click events.
 * Determines the player character's (Sparty's) movement based on the click location.
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 */
void Game::OnLeftDown(int x, int y){

    if ((!mGameStart && !mGameEnd)) {
        double oX = (x - mXOffset) / mScale;
        double oY = (y - mYOffset) / mScale;

//        std::cout << "CLICK AT: " << "(" << oX << "," << oY << ")" << std::endl;
        auto coords = GetCellFromCoords(oX, oY);


//        std::cout << "ROW: " << coords.first << " COL: " << coords.second << std::endl;

        this->CellIsOccupied(coords.first, coords.second, nullptr);

        if (oX < 0 || oY < 0 || oX > GetWidth() || oY > GetHeight()){
            return;
        }

        //Setting the target for Sparty in X and Y
        mSparty->SetTargetX(oX);
        mSparty->SetTargetY(oY);

        //Initialize Sparty's movement
        mSparty->SpartyMove();
    }
}

/**
 * Test an x,y click location to see if it clicked
 * on a given in the game.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(double x, double y)
{
    for (auto i = mItems.begin(); i != mItems.end();  i++)
    {
        XRayFinder visitor2;
        Accept(&visitor2);
        auto xray =  visitor2.GetXRay();
        if ((*i)->HitTest(x, y) && !xray->CheckIfContainsParticularNum((*i)))
        {
            VisitDigit visitor;
            (*i)->Accept(&visitor);
            auto isFound = visitor.IsFound();
            if (isFound){
                int cap = xray->GetCapacity();
                int maxCap = xray->GetMaxCapacity();
                if (cap < maxCap){
                    xray->Add(*i);
                    std::uniform_real_distribution<> distribution( xray->GetColumn(), xray->GetColumn() + (((double) xray->GetWidth()) / xray->GetTileWidth())/2.0);
                    (*i)->SetColumn(distribution(GetRandom()));
                    std::uniform_real_distribution<> distribution2( xray->GetRow() - (((double) xray->GetHeight()) / xray->GetTileHeight())/2.0, xray->GetRow());
                    (*i)->SetRow(distribution2(GetRandom()));
                    if (mLevel == ((int)mLevels.size() - 1))
                    {
                        mSparty->SetSpeed((*i)->GetValue());
                    }
                    break;
                }
                else
                {
                    mFull = true;
                }
            }
        }
    }
    return  nullptr;
}



/**
 * Handles the "Space" key press event.
 *
 * This function is called when the "Space" key is pressed. It triggers the
 * Sparty character to perform an action (e.g., SpartyEat) and checks if the
 * character collides with an item on the game board. If a collision occurs,
 * the item is removed from the list of game items.
 */
void Game::OnSpaceDown(){
    if ((!mGameStart && !mGameEnd && !(mSparty->GetSpartyMoveStatus()))) {
        mSparty->SpartyEat();
        auto item = HitTest(mSparty->GetColumn(), mSparty->GetRow());
    }

}

/**
 * Check if a given column and row position is within the boundaries of the game board.
 *
 * @param col The column index to check.
 * @param row The row index to check.
 * @return True if the position is within the game board, false otherwise.
 */
bool Game::InGameBoard(int col, int row) {
    return (col >= mStartCol) && (col < mStartCol + mSolution[0].size()) &&
        (row >= mStartRow) && (row < mStartRow + mSolution.size());
}

/**
 * Attempts to automatically position VisitDigit items on the game board.
 *
 * This function iterates through the VisitDigit items in the game, attempting to
 * find a suitable position for each item based on its assigned value. It searches
 * for the value in the solution matrix and looks for an unoccupied cell to place
 * the item. If a suitable position is found, the item's column and row are updated,
 * ensuring it's correctly positioned on the board.
 */
void Game::Solve() {
    std::vector<std::shared_ptr<Item>> placedItems;
    std::vector<std::shared_ptr<Item>> unplacedItems;

    // Separate items into placed and unplaced
    for (auto& item : mItems) {
        VisitDigit visitor;
        item->Accept(&visitor);
        if (visitor.IsFound()) {
            if (this->InGameBoard((int)item->GetColumn(), (int)item->GetRow())) {
                placedItems.push_back(item);
            } else {
                unplacedItems.push_back(item);
            }
        }
    }

    // Try placing unplaced items
    for (auto& item : unplacedItems) {
        int value = item->GetValue();
        bool positionFound = false;

        // Search for the value in mSolution
        for (size_t i = 0; i < mSolution.size() && !positionFound; i++) {
            for (size_t j = 0; j < mSolution[i].size() && !positionFound; j++) {
                if (value == mSolution[i][j]) {
                    int col = mStartCol + j;
                    int row = mStartRow + i;

                    if (this->InGameBoard(col, row) && !this->CellIsOccupied(col, row, item)) {
                        item->SetColumn((double)col);
                        item->SetRow((double)row);
                        positionFound = true;
                    }
                }
            }
        }

        // If the correct position was occupied, find an unoccupied cell and place the item there
        if (!positionFound) {
            for (size_t i = 0; i < mSolution.size() && !positionFound; i++) {
                for (size_t j = 0; j < mSolution[i].size() && !positionFound; j++) {
                    int col = mStartCol + j;
                    int row = mStartRow + i;
                    if (this->InGameBoard(col, row) && !this->CellIsOccupied(col, row, item)) {
                        item->SetColumn((double)col);
                        item->SetRow((double)row);
                        positionFound = true;
                    }
                }
            }
        }
    }
}





/**
 * Checks if a grid cell is occupied by an item.
 *
 * This function determines whether the specified grid cell (column, row) is occupied
 * by an item other than the one provided as an exception. It iterates through the items
 * in the game and checks if any item matches the given cell coordinates. If an item
 * matching the cell is found and it is either a VisitDigit or a VisitGiven, the cell
 * is considered occupied.
 *
 * @param col The column index of the grid cell.
 * @param row The row index of the grid cell.
 * @param exceptionItem A shared pointer to an item that should be excluded from the check.
 * @return True if the cell is occupied by an item other than the exception item; otherwise, false.
 */
bool Game::CellIsOccupied(int col, int row, std::shared_ptr<Item> exceptionItem) {
    //std::pair<int, int> xy = GetCoordsFromCell(col, row);

    for (auto item : mItems) {
        if (item == exceptionItem) continue;
        // Assuming your item class has methods GetColumn and GetRow.
        // If the item's column and row don't match the given col and row, continue to the next item.
        if (item->GetColumn() != col || item->GetRow() != row) {
            continue;
        }

        // Check if the item is a VisitDigit.
        VisitDigit visitor;
        item->Accept(&visitor);
        bool digitIsFound = visitor.IsFound();

        // Check if the item is a VisitGiven.
        VisitGiven visitor2;
        item->Accept(&visitor2);
        bool givenIsFound = visitor2.IsFound();

        // If either of the conditions is true, the cell is occupied.
        if (digitIsFound || givenIsFound) {
            //std::cout << "OCCUPIED" << std::endl;
            return true;
        }
    }
    // If no item meets the conditions, the cell is not occupied.
    //std::cout << "NOT OCCUPIED" << std::endl;
    return false;
}

/**
 * Spits out a number into the game world at the current Sparty position.
 *
 * This function checks if the specified number is available in the XRay view of the game.
 * If the number is found, it retrieves the associated item and attempts to place it at the
 * current Sparty position if the cell is unoccupied.
 *
 * @param num The number to be spat out into the game world.
 * @return True if the number was successfully placed, or false if it couldn't be placed.
 */
bool Game::SpitNumber(int num){
    if ((!mGameStart && !mGameEnd && !(mSparty->GetSpartyMoveStatus()))) {
        // check if num in XRay
        XRayFinder visitor2;
        Accept(&visitor2);
        auto xray =  visitor2.GetXRay();

        if (xray->CheckIfContainsNum(num)){
            auto item = xray->GetItem(num);

            double colSparty = mSparty->GetTargetX() / ((double) GetTileWidth());
            double rowSparty = mSparty->GetTargetY()/ ((double) GetTileHeight());

//        std::cout << colSparty << "  " << rowSparty;

            //just for now may need another function
            mSparty->SpartyEat();

            double colNum = floor(colSparty);
            double rowNum = floor(rowSparty);
            if (!CellIsOccupied((int)colNum, (int)rowNum, nullptr)){
                item->SetColumn(colNum);
                item->SetRow(rowNum);
                xray->Remove(item);
                return true;
            }
        }
        return true;
    }
    return false;
}



/**
 * Converts screen coordinates to grid cell coordinates.
 *
 * Given screen coordinates (x, y), this function calculates and returns the
 * corresponding grid cell coordinates (column, row). It divides the provided
 * x and y values by the tile width and height, respectively, and floors the
 * results to determine the grid cell.
 *
 * @param x The x-coordinate in screen coordinates.
 * @param y The y-coordinate in screen coordinates.
 * @return A pair of integers representing the grid cell coordinates (column, row).
 */
std::pair<int, int> Game::GetCellFromCoords(double x, double y) {
    // Determine the column and row based on the x and y
    int col = std::floor(x / mTileWidth);    // Implicit truncation
    int row = std::floor(y / mTileHeight);   // Implicit truncation

    return {col, row};
}

/**
 * Checks if the game board is completely occupied.
 *
 * This function examines each cell on the game board and determines if all cells
 * are occupied. It returns true if all cells are occupied and false otherwise.
 *
 * @return True if the game board is completely occupied; otherwise, false.
 */
bool Game::BoardIsFull() {
    for (size_t i = 0; i < mSolution.size(); i++) {
        for (size_t j = 0; j < mSolution[i].size(); j++) {
            int col = mStartCol + j;
            int row = mStartRow + i;

            if (!this->CellIsOccupied(col, row, nullptr)) {
                return false;  // If any cell is not occupied, board is not full.
            }
        }
    }
    return true;  // All cells are occupied.
}

/**
 * Checks if the current state of the game board matches the solution.
 *
 * This function verifies whether the current game board, when compared to the
 * stored solution, is correct. It first checks if the board is full, as an
 * incomplete board cannot be a correct solution. Then, it iterates through the
 * cells on the board and compares the values of items at each cell to the values
 * in the solution matrix.
 *
 * @return True if the current board matches the solution; otherwise, false.
 */
bool Game::IsBoardCorrect() {
    // If the board is not full, the solution cannot be correct.
    if (!BoardIsFull()) {
        return false;
    }

    for (size_t i = 0; i < mSolution.size(); i++) {
        for (size_t j = 0; j < mSolution[i].size(); j++) {
            int col = mStartCol + j;
            int row = mStartRow + i;

            auto item = this->GetItemAtCell(col, row);

            if (item == nullptr || item->GetValue() != mSolution[i][j]) {
                return false;  // Mismatch found.
            }
        }
    }
    return true;  // All cells match the solution.
}

/**
 * Retrieves the item at the specified cell coordinates.
 *
 * This function searches through the items in the game and returns the item
 * located at the specified column and row, if one exists. It checks if the item
 * is either a VisitDigit or a VisitGiven before returning it.
 *
 * @param col The column index of the cell.
 * @param row The row index of the cell.
 * @return A shared pointer to the item at the specified cell coordinates if found,
 *         or nullptr if no relevant item is found.
 */
std::shared_ptr<Item> Game::GetItemAtCell(int col, int row) {
    for (auto& item : mItems) {
        if (item->GetColumn() == col && item->GetRow() == row) {
            // Check if the item is a VisitDigit.
            VisitDigit digitVisitor;
            item->Accept(&digitVisitor);
            bool digitIsFound = digitVisitor.IsFound();

            // Check if the item is a VisitGiven.
            VisitGiven givenVisitor;
            item->Accept(&givenVisitor);
            bool givenIsFound = givenVisitor.IsFound();

            if (digitIsFound || givenIsFound) {
                return item;  // Return the item if it's either a VisitDigit or a VisitGiven.
            }
        }
    }
    return nullptr;  // No relevant item found at the given cell.
}

/**
 * Game function the calls the headbutt animation
 */
void Game::OnKeyHeadButtDown()
{
    if ((!mGameStart && !mGameEnd && !(mSparty->GetSpartyMoveStatus()))) {
        mSparty->AnimateHeadbutt();
    }

}

/**
 * Handle the interaction of Sparty with container items.
 * Checks if Sparty hits any container items and processes their contents.
 */
void Game::HitContainer()
{
    for (auto i = mItems.begin(); i != mItems.end(); ++i)
    {
        VisitContainer visitor;
        (*i)->Accept(&visitor);
        if (visitor.GetIsFound())
        {
            auto container = visitor.GetContainer();
//            std::cout << mSparty->GetColumn() << " " << mSparty->GetRow() << std::endl;
//            std::cout << container->GetColumn() << " " << container->GetRow() << std::endl;
            if ((*i)->HitTest(mSparty->GetColumn(), mSparty->GetRow()))
            {
                while (true)
                {
                    auto item = container->GetItem();
                    if (item == nullptr)
                    {
                        break;
                    }
                    mItems.insert(mItems.end() - 1, item);
                    RepositionItem(container, item);
                    container->Remove(item);
                }
            }
        }
    }
}

/**
 * Reposition an item after it has been taken out of a container.
 * The item is placed within the container's vicinity.
 *
 * @param container Pointer to the container.
 * @param item Shared pointer to the item to be repositioned.
 */
void Game::RepositionItem(Container* container, std::shared_ptr<Item> item){
    std::uniform_real_distribution<> distribution(container->GetColumn() - (((double) container->GetWidth()) / container->GetTileWidth()), container->GetColumn() + (((double) container->GetWidth()) / container->GetTileWidth()));
    item->SetColumn(distribution(GetRandom()));
    std::uniform_real_distribution<> distribution2(container->GetRow() - 1.5 * (((double) container->GetHeight()) / container->GetTileHeight()), container->GetRow() - (((double) container->GetHeight()) / container->GetTileHeight()));
    item->SetRow(distribution2(GetRandom()));
}


// void Game::NextState() {


