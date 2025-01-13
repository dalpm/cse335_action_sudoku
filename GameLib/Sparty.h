/**
 * @file Sparty.h
 * @author Owen
 *
 * Class for Sparty digit grabber item
 */

#ifndef PROJECT1_GAMELIB_SPARTY_H
#define PROJECT1_GAMELIB_SPARTY_H

#include "Item.h"

/**
 * Class for our Sparty searcher
 */
class Sparty : public Item {
private:
    /// The string representing the image path for Sparty's first image (head)
    std::wstring mImg1;

    /// The string representing the image path for Sparty's second image (jaw)
    std::wstring mImg2;

    /// Bitmap for the primary image of Sparty.
    std::shared_ptr<wxBitmap> mImage1;

    /// Bitmap for the mouth image of Sparty.
    std::shared_ptr<wxBitmap> mImage2;

    /// Determines which image (1 or 2) should be drawn in the front.
    int mFront = 0;

    /// Width of the Sparty images.
    double mWidth = 0.0;

    /// Height of the Sparty images.
    double mHeight = 0.0;

    /// Maximum rotation angle for the mouth.
    double mMouthPivotAngle = 0.0;

    /// x point of spartys mouth
    int mMouthPointX = 0;

    /// Y point of spartys mouth
    int mMouthPointY = 0;

    /// Pivot point for the mouth rotation animation.
    wxPoint mMouthPivot;

    /// Maximum rotation angle for the head.
    double mHeadPivotAngle = 0.0;

    /// X head point for sparty
    int mHeadPointX = 0;

    /// Y head point for sparty
    int mHeadPointY = 0;

    /// Pivot point for the head rotation animation.
    wxPoint mHeadPivot;

    /// Offset to determine where Sparty moves when a location is clicked.
    double mTargetOffsetX = 0.0;

    /// Offset to determine where Sparty moves when a location is clicked.
    double mTargetOffsetY = 0.0;

    /// Stores the combined X and Y offset for Sparty's target movement.
    wxPoint mTargetOffset;

    /// Current angle for the mouth animation.
    double mCurrentMouthAngle = 0.0;

    /// Current angle for the head animation.
    double mCurrentHeadAngle = 0.0;

    /// Flag indicating if Sparty is currently in a move action.
    bool mInMove = false;

    /// Collection of eaten game items.
    std::vector<std::shared_ptr<Item>> mEatenItems;

    /// Indicates whether Sparty is currently in an eating state.
    bool mIsEating = false;

    /// Indicates whether Sparty is currently in a reverse eating state.
    bool mIsEatingReverse = false;

    /// Indicates whether Sparty is currently in a headbutting state.
    bool mIsHeadbutting = false;

    /// Indicates whether Sparty is currently in a reverse headbutting state.
    bool mIsHeadbuttingReverse = false;

    /// The target X-coordinate for Sparty's position.
    double mTargetX = 0.0;

    /// The target Y-coordinate for Sparty's position.
    double mTargetY = 0.0;

    /// Spartys speed
    double mSpeed = 0.0;

    /// If the image is set for Sparty
    bool mImageSet = false;

public:

    /// Default constructor (disabled)
    Sparty() = delete;

    /// Constructor
    Sparty(const Sparty &);

    /// Assignment operator
    void operator=(const Sparty &) = delete;

    void XmlLoad(wxXmlNode* node) override;

    Sparty(Level *level);

    /**
     * Accepts an item visitor for interaction.
     *
     * This method is used to accept a visitor object, allowing it to interact with
     * the Sparty item, although no specific action is performed in this case.
     *
     * @param visitor The visitor object to accept.
     */
    void Accept(ItemVisitor* visitor) override {visitor->SpartyVisitor(this); }

    std::shared_ptr<Item> Clone() override;

    void Update(double elapsed) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap>) override;

    void Draw1(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap>);

    /**
     * Animates Sparty's eating behavior.
     */
    void Draw2(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap>);

    /**
     * Animates Sparty's headbutting behavior.
     */
    void Draw3(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap>);

    /**
    * Animates Sparty's head movement to depict a headbutt.
    *
    * This function modifies the current head angle to simulate a headbutt action by Sparty.
    * The rate at which the head moves is controlled by the proportion of `HeadbuttTime` and a set constant (1000 in this context).
    * Once the headbutt action is completed, the angle is capped at `mHeadPivotAngle` to reset it to its original position.
    */
    void AnimateHeadbutt() {mIsHeadbutting = true; }

    /**
     * Initiates Sparty's move action.
     */
    void SpartyMove() {mInMove = true; }

    /**
     * Get the Y-coordinate location for the object's position.
     *
     * This function calculates the Y-coordinate location based on the object's row index
     * and the height of the image.
     *
     * @return The Y-coordinate location of the object's position.
     */
    double GetYLoc() override {return ((this->GetRow() + 1)*this->GetTileHeight() - mImage1->GetHeight()); }

    /**
     * Retrieves the X offset for Sparty's target movement.
     * @return X offset value.
     */
    double GetTargetOffsetX() {return mTargetOffset.x; }

    /**
     * Retrieves the Y offset for Sparty's target movement.
     * @return Y offset value.
     */
    double GetTargetOffsetY() {return mTargetOffset.y; }

    /**
     * Set Target in X coords
     * @param x target in X
     */
    void SetTargetX(double x) {mTargetX = x; }

    /**
     * Set Target in Y coords
     * @param y target in Y
     */
    void SetTargetY(double y) {mTargetY = y; }

    /**
     * Get the target X-coordinate of Sparty's position.
     *
     * @return The target X-coordinate.
     */
    double GetTargetX() {return mTargetX; }

    /**
     * Get the target Y-coordinate of Sparty's position.
     *
     * @return The target Y-coordinate.
     */
    double GetTargetY() {return mTargetY; }

    /**
     * Retrieves the height of Sparty's primary image.
     * @return Image height value.
     */
    double GetHeight() {return mImage1->GetHeight(); }

    void ComputePosition(double elapsed);

    /**
     * Initiates the eating animation for Sparty.
     * Sets the flag indicating that Sparty is currently eating.
     */
    void SpartyEat() {mIsEating = true; }

    void SetSpeed(int value);

    /**
     * Retrieves Sparty's moving status.
     * @return Sparty's moving status.
     */
    bool GetSpartyMoveStatus(){return mInMove;}
};

#endif //PROJECT1_GAMELIB_SPARTY_H
