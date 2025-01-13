/**
 * @file MainFrame.h
 * @author Doruk Alp Mutlu
 *
 * Main-frame of the application
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

#include "GameView.h"

/**
 * The MainFrame class is responsible for displaying the main application window.
 */
class MainFrame : public wxFrame
{
private:
    /// Pointer to the GameView object for managing game visuals.
    GameView* mGameView;

    void OnExit(wxCommandEvent& event);

    void OnClose(wxCloseEvent& event);

public:
    void Initialize();

    void OnAbout(wxCommandEvent &event);
};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
