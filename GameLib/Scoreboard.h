/**
 * @file Scoreboard.h
 * @author Aleksa
 *
 * Class for the scoreboard
 */

#ifndef PROJECT1_GAMELIB_SCOREBOARD_H
#define PROJECT1_GAMELIB_SCOREBOARD_H

#include "Item.h"


/**
 * class for scoreboard item
 */
class Scoreboard
{
private:
    /// Elapsed time in seconds
    double mElapsedSeconds = 0;

public:
    /**
     * Constructor that initializes the Scoreboard object.
     */
    Scoreboard();

    // Start the timer
    void Start();

    // Reset the timer to zero
    void ResetTimer();

    // Increment the elapsed seconds
    void Tick(double elapsed);

    // Render the timer on the given graphics context
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Get the elapsed seconds.
     *
     * @return Elapsed time in seconds.
     */
    int GetElapsedSeconds() const { return mElapsedSeconds; }

};

#endif //PROJECT1_GAMELIB_SCOREBOARD_H
