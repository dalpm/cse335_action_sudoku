/**
 * @file GameView.h
 * @author Doruk Alp Mutlu
 *
 * View class for the game
 */

#ifndef PROJECT1_GAMELIB_GAMEVIEW_H
#define PROJECT1_GAMELIB_GAMEVIEW_H

#include "Game.h"
#include "Scoreboard.h"
#include "Banner.h"
#include <wx/graphics.h>

class Item;

/**
 * The GameView class is responsible for displaying the game interface and managing user interactions.
 */
class GameView : public wxWindow
{
private:
    void OnPaint(wxPaintEvent& event);

    /// An object that describes the game
    Game mGame;

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// the games banner
    Banner mBanner;
public:
    void Initialize(wxFrame*);

    void AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* fileMenu, wxMenu* levelsMenu, wxMenu* helpMenu);

    void OnTimerTick(wxTimerEvent& event);

    void OnSolveLevel(wxCommandEvent& event);

    void OnFileOpenLevel0(wxCommandEvent& event);

    void OnFileOpenLevel1(wxCommandEvent& event);

    void OnFileOpenLevel2(wxCommandEvent& event);

    void OnFileOpenLevel3(wxCommandEvent& event);

    GameView();

    /**
     * Loads all necessary game files.
     * This function acts as a wrapper around the Game's LoadFiles method, ensuring that
     * all game-related files are loaded into memory for gameplay.
     */
    void LoadEverything(){mGame.LoadFiles();}

    /**
     * Stop the timer so the window can close.
     */
    void Stop() {mTimer.Stop();}

    void OnLeftDown(wxMouseEvent &event);

    void OnKeyDown(wxKeyEvent &event);
};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H