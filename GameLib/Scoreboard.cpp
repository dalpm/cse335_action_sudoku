/**
 * @file Scoreboard.cpp
 * @author Aleksa
 */


#include "pch.h"
#include "Scoreboard.h"


/// Size of the scoreboard text in virtual pixels
const int SCOREBOARD_TEXT_SIZE = 64;

/// Top left corner of the scoreboard in virtual pixels. (X)
const int TOP_X = 10;

/// Top left corner of the scoreboard in virtual pixels. (Y)
const int TOP_Y = 10;

/// The amount of seconds in a minute
const int ONE_MINUTE = 60;

/**
 * Constructor that initializes the Scoreboard object.
 */
Scoreboard::Scoreboard() : mElapsedSeconds(0)
{
}

/**
 * Starts the scoreboard timer.
 */
void Scoreboard::Start()
{
    mElapsedSeconds = 0;
    // You might want to start a wxTimer here if you're using one.
}

/**
 * Resets the scoreboard timer to 0.
 */
void Scoreboard::ResetTimer()
{
    mElapsedSeconds = 0; // Reset time
}

/**
 * Update the elapsed time based on the given time duration.
 *
 * @param elapsed The time duration to add to the current elapsed time.
 */
void Scoreboard::Tick(double elapsed)
{
    mElapsedSeconds += elapsed;
}

/**
 * Draw the scoreboard on the screen.
 *
 * @param graphics The graphics context to draw on.
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    // The scoreboard's top left position
    wxPoint ScoreboardTopLeft(TOP_X, TOP_Y);

    // Format the elapsed time
    int min = mElapsedSeconds / ONE_MINUTE;
    int sec = (int) mElapsedSeconds % ONE_MINUTE;
    wxString timeString = wxString::Format("%02d:%02d", min, sec);

    // Set the font and color
    wxFont font(wxSize(0,SCOREBOARD_TEXT_SIZE),
                wxFONTFAMILY_DEFAULT,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font,wxColour(*wxWHITE));

    graphics->DrawText(timeString, ScoreboardTopLeft.x, ScoreboardTopLeft.y);

}