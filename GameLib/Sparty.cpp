   /**
 * @file Sparty.cpp
 * @author Owen
 */

#include "pch.h"
#include "Sparty.h"
#include "Level.h"
#include "Game.h"
#include <vector>

/// Character speed in pixels per second
const double MAX_SPEED = 275.00;

/// The time for an eating cycles in seconds
const double EATING_TIME = 2.0;

/// The time for a headbutt cycle in seconds
const double HEADBUTT_TIME = 2.0;

/**
* Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void Sparty::XmlLoad(wxXmlNode* node)
{
    Item::XmlLoad(node);
    long hpx, hpy, mpx, mpy, tx, ty, fr;

    node->GetAttribute(L"front", L"0").ToLong(&fr);

    node->GetAttribute(L"head-pivot-angle", L"0.5").ToDouble(&mHeadPivotAngle);  // Default value of HeadbuttTime
    node->GetAttribute(L"head-pivot-x", L"0").ToLong(&hpx);
    node->GetAttribute(L"head-pivot-y", L"0").ToLong(&hpy);


    node->GetAttribute(L"mouth-pivot-angle", L"0.5").ToDouble(&mMouthPivotAngle);  // Default value of EatingTime
    node->GetAttribute(L"mouth-pivot-x", L"0").ToLong(&mpx);
    node->GetAttribute(L"mouth-pivot-y", L"0").ToLong(&mpy);

    node->GetAttribute(L"target-x", L"0").ToLong(&tx);
    node->GetAttribute(L"target-y", L"0").ToLong(&ty);

    mHeadPointX = (int) hpx;
    mHeadPointY = (int) hpy;
    mMouthPointX = (int) mpx;
    mMouthPointY = (int) mpy;
    mTargetOffsetX = (int) tx;
    mTargetOffsetY = (int) ty;
    mFront = (int) fr;

    mHeadPivot = wxPoint(mHeadPointX, mHeadPointY);
    mMouthPivot = wxPoint(mMouthPointX, mMouthPointY);
    mTargetOffset = wxPoint((int) mTargetOffsetX, (int) mTargetOffsetY);

    mSpeed = MAX_SPEED;


    mImg1 = std::wstring("images/" + node->GetAttribute(L"image1",L"sparty-1.png"));
    mImg2 = std::wstring("images/" + node->GetAttribute(L"image2",L"sparty-2.png"));

}


/**
 * Constructor
 * @param level Level this is a member of
 */
Sparty::Sparty(Level *level) : Item(level)
{
}

/**
 * @brief Copy constructor for the Sparty class.
 *
 * This constructor creates a new Sparty object that is a copy of another Sparty object.
 *
 * @param other The Sparty object to copy.
 */
Sparty::Sparty(const Sparty& other) : Item(other) {
    mFront = other.mFront;
    mWidth = other.mWidth;
    mHeight = other.mHeight;

    mMouthPointX = other.mMouthPointX;
    mMouthPointY = other.mMouthPointY;

    mHeadPointX = other.mHeadPointX;
    mHeadPointY = other.mHeadPointY;

    mMouthPivot = other.mMouthPivot;
    mMouthPivotAngle = other.mMouthPivotAngle;

    mHeadPivot = other.mHeadPivot;
    mHeadPivotAngle = other.mHeadPivotAngle;

    mTargetOffsetX = other.mTargetOffsetX;
    mTargetOffsetY = other.mTargetOffsetY;
    mTargetOffset = other.mTargetOffset;


    mCurrentMouthAngle = other.mCurrentMouthAngle;
    mCurrentHeadAngle = other.mCurrentHeadAngle;

    mSpeed = other.mSpeed;
    mImg1 = other.mImg1;
    mImg2 = other.mImg2;
}


/**
 * Clone this object
 * @return an allocated copy of this object
 */
std::shared_ptr<Item> Sparty::Clone()
{
    return std::make_shared<Sparty>(*this);
}

/**
 * Handle updates in time for sparty
 * @param elapsed Time elapsed since the class call
 */
void Sparty::Update(double elapsed)
{
   if(mIsEating){
       mCurrentMouthAngle += EATING_TIME * elapsed;
       if (mCurrentMouthAngle > mMouthPivotAngle){
           mIsEatingReverse = true;
           mIsEating = false;
       }
   }
   else if(mIsEatingReverse){
       mCurrentMouthAngle -= EATING_TIME * elapsed;
       if (mCurrentMouthAngle < 0){
           mIsEatingReverse = false;
           mCurrentMouthAngle = 0;
       }
   }

    if(mIsHeadbutting){
        mCurrentHeadAngle += HEADBUTT_TIME * elapsed;
        if (mCurrentHeadAngle > mHeadPivotAngle){
            mIsHeadbuttingReverse = true;
            mIsHeadbutting = false;
        }
    }
    else if(mIsHeadbuttingReverse){
        mCurrentHeadAngle -= HEADBUTT_TIME * elapsed;
        if (mCurrentHeadAngle < 0){
            mIsHeadbuttingReverse = false;
            mCurrentHeadAngle = 0;
        }
    }

   if(mInMove){
       ComputePosition(elapsed);
   }
}



/**
 * Draws the Sparty character on the screen.
 *
 * This function renders the Sparty character images onto the game window using
 * the wxGraphicsContext. Depending on the orientation of the Sparty (indicated by mFront),
 * the order of the images drawn will change. If mFront is 1, image2 will be drawn
 * before image1, indicating that Sparty might be facing the front. Otherwise, image1
 * is drawn before image2.
 *
 * @param graphics The graphics context used for drawing onto the window.
 * @param btm The bitmap image representation of Sparty. Note: This parameter is unused in the current function.
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm)
{
    if(!mImageSet){
        auto imageManager = GetGame()->GetIM();
        imageManager->InsertBitmapSparty(mImg1);
        imageManager->InsertBitmapSparty(mImg2);
        mImage1 = imageManager->GetBitmapSparty(mImg1);
        mImage2 = imageManager->GetBitmapSparty(mImg2);
        mImageSet = true;
    }
    if (mIsEating || mIsEatingReverse)
    {
        if(mFront == 2)
        {
            Draw1(graphics, btm);
            Draw2(graphics, btm);
        }
        else
        {
            Draw2(graphics, btm);
            Draw1(graphics, btm);
        }
    }
    else if (mIsHeadbutting || mIsHeadbuttingReverse)
    {
        Draw3(graphics, btm);
    }
    else
    {
        if(mFront == 2)
        {
            Draw1(graphics, btm);
            Draw2(graphics, btm);
        }
        else
        {
            Draw2(graphics, btm);
            Draw1(graphics, btm);
        }
    }

}
/**
 * Sparty function that draws the image1, larger part of spartys head
 *
 * @param graphics The graphics context used for drawing onto the window.
 * @param btm bitmap of sparty
 */
void Sparty::Draw1(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm)
{
    graphics->DrawBitmap(*mImage1,
                         this->GetColumn() * (this->GetTileWidth()),
                         ((this->GetRow() + 1) * this->GetTileHeight() - mImage1->GetHeight()),
                         mImage1->GetWidth(),
                         mImage1->GetHeight());
}

/**
 * Animates Sparty's mouth movement to depict eating.
 *
 * This function is responsible for drawing Sparty's mouth movement to depict eating. It considers the
 * `mIsEating` and `mIsEatingReverse` flags to determine whether to apply a rotation transformation to
 * the mouth image for animation. If one of these flags is true, it rotates the mouth image and draws it
 * accordingly. Otherwise, it simply draws the mouth image at the current position.
 *
 * @param graphics The graphics context to draw on.
 * @param btm The bitmap used for drawing.
 */
void Sparty::Draw2(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm)
{
   if (mIsEating || mIsEatingReverse){
       graphics->PushState();

       graphics->Translate(mMouthPivot.x+this->GetColumn()*(this->GetTileWidth()), mMouthPivot.y+((this->GetRow()+1)*this->GetTileHeight() - mImage2->GetHeight()));
       graphics->Rotate(mCurrentMouthAngle);
       graphics->Translate(-mMouthPivot.x-this->GetColumn()*(this->GetTileWidth()), -mMouthPivot.y-((this->GetRow()+1)*this->GetTileHeight() - mImage2->GetHeight()));

       graphics->DrawBitmap(*mImage2, this->GetColumn()*(this->GetTileWidth()), ((this->GetRow() + 1)*this->GetTileHeight()) - mImage2->GetHeight(), mImage2->GetWidth(), mImage2->GetHeight());
       graphics->PopState();
   }else{
       graphics->DrawBitmap(*mImage2, this->GetColumn()*(this->GetTileWidth()), ((this->GetRow() + 1)*this->GetTileHeight() - mImage2->GetHeight()), mImage2->GetWidth(), mImage2->GetHeight());
   }
}

/**
 * Sparty function that draws the headbutting
 *
 * @param graphics The graphics context used for drawing onto the window.
 * @param btm bitmap of sparty
 */
void Sparty::Draw3(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<wxBitmap> btm)
{
    if (mIsHeadbutting || mIsHeadbuttingReverse)
    {
        graphics->PushState();

        graphics->Translate(mHeadPivot.x+this->GetColumn()*(this->GetTileWidth()), mHeadPivot.y+((this->GetRow()+1)*this->GetTileHeight() - mImage2->GetHeight()));
        graphics->Rotate(mCurrentHeadAngle);
        graphics->Translate(-mHeadPivot.x-this->GetColumn()*(this->GetTileWidth()), -mHeadPivot.y-((this->GetRow()+1)*this->GetTileHeight() - mImage2->GetHeight()));

        graphics->DrawBitmap(*mImage1, this->GetColumn()*(this->GetTileWidth()), ((this->GetRow() + 1)*this->GetTileHeight()) - mImage1->GetHeight(), mImage1->GetWidth(), mImage1->GetHeight());
        graphics->DrawBitmap(*mImage2, this->GetColumn()*(this->GetTileWidth()), ((this->GetRow() + 1)*this->GetTileHeight()) - mImage2->GetHeight(), mImage2->GetWidth(), mImage2->GetHeight());
        graphics->PopState();
   } else
   {
       graphics->DrawBitmap(*mImage1, this->GetColumn()*(this->GetTileWidth()), ((this->GetRow() + 1)*this->GetTileHeight() - mImage1->GetHeight()), mImage1->GetWidth(), mImage1->GetHeight());
       graphics->DrawBitmap(*mImage2, this->GetColumn()*(this->GetTileWidth()), ((this->GetRow() + 1)*this->GetTileHeight() - mImage2->GetHeight()), mImage2->GetWidth(), mImage2->GetHeight());
   }
}

/**
 * Compute a position for the Sparty.
 * @param elapsed the amount of time elapsed to compute position
 */
void Sparty::ComputePosition(double elapsed)
{
    if (mInMove){

        double distX = mTargetX - GetXLoc() - GetTargetOffsetX();

        double distY = mTargetY -GetYLoc() - GetTargetOffsetY() - GetHeight() / 2.0;

        double magnitude = sqrt(distX * distX + distY * distY);

        double dirX =  distX / magnitude;

        double dirY =  distY / magnitude;

        double yTravelled = (dirY * elapsed * mSpeed);

        double xTravelled = (dirX * elapsed * mSpeed);

        if (distX > xTravelled || distX < -xTravelled){
            double newRow = GetRow() + yTravelled / GetTileHeight();
            double newColumn = GetColumn() + xTravelled / GetTileWidth();
            if (newRow - mImage1->GetHeight() / (2.0 * (double) GetTileHeight()) < -1 ){
                newRow = mImage1->GetHeight() / (2.0 * (double) GetTileHeight()) -1;
                mInMove = false;
            }
            if (newRow > ((double) GetGame()->GetHeight()) / ((double) GetTileHeight()) - ((double) mImage1->GetHeight()) / (2.0 * (double) GetTileHeight())){
                newRow = ((double) GetGame()->GetHeight()) / ((double) GetTileHeight()) - ((double) mImage1->GetHeight()) / (2.0 * (double) GetTileHeight());
                mInMove = false;
            }

            if (newColumn < 0) {
                newColumn = 0;
                mInMove = false;
            }

            SetRow(newRow);
            SetColumn(newColumn);
        }
        else {
            mInMove = false;
        }
    }
}

/**
 * Set the speed of Sparty based on a numerical value.
 *
 * @param value The numerical value representing the speed. Should be within [0, MaxNum].
 */
void Sparty::SetSpeed(int value){
    mSpeed = (((double) value) / GetGame()->GetMaxSudokuVal()) * MAX_SPEED + MAX_SPEED;
}