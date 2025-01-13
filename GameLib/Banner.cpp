/**
 * @file Banner.cpp
 * @author Owen
 */

#include "pch.h"

#include "Banner.h"

/// How long the banner should display on the screen when the level starts @return CONSTANT
const double BANNER_DISPLAY_TIME = 3.0;

/// Padding for text (width) @return CONSTANT
const int WIDTH_PADDING = 50;

/// Padding for text (height) @return CONSTANT
const int HEIGHT_PADDING = 40;

/// Intro banner font spacing @return CONSTANT
const int INTRO_TOP_BOTTOM_PADDING = 10;

/// Padding for the im full banner @return CONSTANT
const int IM_FULL_BANNER_PADDING = 15;

/// Outline size for the im full banner @return CONSTANT
const int IM_FULL_BANNER_OUTLINE = 5;

/// The size of the outline for the intro banner @return CONSTANT
const int INTRO_BANNER_OUTLINE = 1;

/// The title font @return CONSTANT
const wxFont TITLE_FONT(wxSize(0, 85), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

/// The  message font @return CONSTANT
const wxFont MESSAGE_FONT(wxSize(0, 50), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

/// The im full font @return CONSTANT
const wxFont IM_FULL_FONT(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

/// Light green color @return CONSTANT
const wxColour LIGHT_GREEN(50, 180, 50);

/// Black color @return CONSTANT
const wxColour BLACK(0, 0, 0);

/// Default message for levels @return CONSTANT
const wxString LEVEL_MESSAGE ="space: Eat\n0-8: Regurgitate\nB: Headbutt";

/// The level complete string @return CONSTANT
const wxString LEVEL_COMPLETE = "Level Complete!";

/// The level incorrect string @return CONSTANT
const wxString INCORRECT = "Incorrect!";

/// The im full string @return CONSTANT
const wxString IM_FULL = "I'm Full!";

/// The error message (default case) @return CONSTANT
const wxString ERROR_MESSAGE = "ERROR!";

/**
 * Update the banner's display state based on elapsed time.
 *
 * This function is called to update the display state of the banner. It increments
 * the elapsed time and checks if it exceeds the predefined banner display time.
 * If the time limit is reached, the banner's visibility is set to false.
 *
 * @param elapsed The elapsed time since the last update.
 */
void Banner::Update(double elapsed)
{
    mTime += elapsed;
    if (mTime > BANNER_DISPLAY_TIME)
    {
        mBannerShouldDisplay = false;
    }
}

/**
 * Draw the Banner on the screen.
 *
 * @param graphics The graphics context to draw on.
 * @param width Width of the drawing area.
 * @param height Height of the drawing area.
 */
void Banner::DrawLevelIntroBanner(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    if (mBannerShouldDisplay){
        wxString bannerString = mMessageString;
        wxString titleString = mTitleString;

        // Measure text extents for title
        graphics->SetFont(TITLE_FONT, LIGHT_GREEN);
        double titleWidth, titleHeight;
        graphics->GetTextExtent(titleString, &titleWidth, &titleHeight);

        // Measure text extents for banner (only a single line for now)
        graphics->SetFont(MESSAGE_FONT, BLACK);
        double bannerLineWidth, bannerLineHeight;
        graphics->GetTextExtent("TEST", &bannerLineWidth, &bannerLineHeight);

        // Compute the total width and height needed for the banner box
        int lineCount = bannerString.Freq('\n') + 1;
        double totalWidth = std::max(titleWidth, bannerLineWidth) + WIDTH_PADDING;
        double totalHeight = titleHeight + bannerLineHeight * lineCount + HEIGHT_PADDING;

        // Compute the positions for the rectangle
        double rectX = computeCenteredX(width, totalWidth);
        double rectY = (height - totalHeight) / 2.0;

        // Draw rectangle
        graphics->SetBrush(*wxWHITE_BRUSH);
        graphics->SetPen(wxPen(*wxBLACK, INTRO_BANNER_OUTLINE));
        graphics->DrawRectangle(rectX, rectY, totalWidth, totalHeight);

        // Draw title
        graphics->SetFont(TITLE_FONT, LIGHT_GREEN);
        graphics->DrawText(titleString, computeCenteredX(width, titleWidth), rectY + INTRO_TOP_BOTTOM_PADDING);

        // Draw banner message, handling newline
        graphics->SetFont(MESSAGE_FONT, BLACK);
        size_t start = 0;
        size_t newlinePos;
        double currentY = rectY + titleHeight + INTRO_TOP_BOTTOM_PADDING;
        while ((newlinePos = bannerString.find("\n", start)) != wxString::npos)
        {
            wxString line = bannerString.SubString(start, newlinePos - 1);
            double lineWidth, lineHeight;
            graphics->GetTextExtent(line, &lineWidth, &lineHeight);
            graphics->DrawText(line, computeCenteredX(width, lineWidth), currentY);
            currentY += bannerLineHeight;
            start = newlinePos + 1;
        }
        if (start < bannerString.size())
        {
            wxString lastLine = bannerString.substr(start);
            double lastLineWidth, lastLineHeight;
            graphics->GetTextExtent(lastLine, &lastLineWidth, &lastLineHeight);
            graphics->DrawText(lastLine, computeCenteredX(width, lastLineWidth), currentY);
        }
    }
}

/**
 * Draw the game status Banner on the screen.
 *
 * @param graphics The graphics context to draw on.
 * @param width Width of the drawing area.
 * @param height Height of the drawing area.
 */
void Banner::DrawGameStatusBanner(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxString bannerString = mMessageString;

    double wid, hit;
    graphics->SetFont(TITLE_FONT, LIGHT_GREEN);
    graphics->GetTextExtent(bannerString, &wid, &hit);
    graphics->DrawText(bannerString, (width-wid)/2, (height-hit)/2);
}

/**
 * Set message of banner.
 *
 * @param state - changes message based on which banner is required.
 */
void Banner::SetBannerMessage(std::string state)
{
    switch(state[0])
    {
        case '0': case '1': case '2': case '3':
            mTitleString = "Level " + state + " Begin\n";
            mMessageString = LEVEL_MESSAGE;
            break;
        case 'C':
            mMessageString = LEVEL_COMPLETE;
            break;
        case 'I':
            mMessageString = INCORRECT;
            break;
        case 'F':
            mMessageString = IM_FULL;
            break;
        default:
            mMessageString =  ERROR_MESSAGE;
            break;
    }
}

/**
 * Draws a full banner with a specified message on the given graphics context.
 *
 * This function first draws a black rectangle as the background of the banner.
 * Over this, a slightly smaller white rectangle is drawn, followed by the banner message
 * in bold red text.
 *
 * @param graphics The graphics context on which the banner is drawn.
 * @param width The width of the area where the banner should be drawn.
 * @param height The height of the area where the banner should be drawn (currently unused).
 */
void Banner::DrawIMFullBanner(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxString bannerString = mMessageString;

    // Get banner text size
    graphics->SetFont(IM_FULL_FONT, *wxRED);
    double bannerTextWidth, bannerTextHeight;
    graphics->GetTextExtent(bannerString, &bannerTextWidth, &bannerTextHeight);

    // Calculate the dimensions and positions dynamically
    double rectWidth = bannerTextWidth + IM_FULL_BANNER_PADDING;  // Some padding
    double rectHeight = bannerTextHeight + IM_FULL_BANNER_PADDING;  // Some padding
    double rectX = (width - rectWidth) / 2.0;
    double textX = rectX + (rectWidth - bannerTextWidth) / 2.0;
    double textY = mYLocFull + (rectHeight - bannerTextHeight) / 2.0;

    // Draw the rectangle and text
    graphics->SetPen(wxPen(*wxBLACK, IM_FULL_BANNER_OUTLINE));
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->DrawRectangle(rectX, mYLocFull, rectWidth, rectHeight);

    graphics->DrawText(bannerString, textX, textY);
}
