/**
 * @file GameView.cpp
 * @author Doruk Alp Mutlu
 */

#include "pch.h"
#include "GameView.h"
#include "Sparty.h"

#include <wx/dcbuffer.h>
#include <wx/wx.h>
#include "ids.h"

/// Frame duration in milliseconds
const int FRAME_DURATION = 30;

/**
 * Initialize the game view class.
 * @param parent The parent window for this class
 */
void GameView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,wxDefaultPosition, wxDefaultSize,wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mGame.SetLevel(1);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);

    mTimer.SetOwner(this);
    mTimer.Start(FRAME_DURATION);
    mStopWatch.Start();

    Bind(wxEVT_TIMER, &GameView::OnTimerTick, this);
        //mTimer.Start(1000); // Trigger every 1000 ms (1 second)
}

/**
 * Add menus specific to the view.
 *
 * @param mainFrame The main frame that owns the menu bar.
 * @param menuBar The menu bar to add menus to.
 * @param fileMenu The file menu, so we can add to it if we wish.
 * @param levelsMenu The levels menu to add level options to.
 * @param helpMenu The help menu to add help-related options to.
 */
void GameView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar, wxMenu* fileMenu, wxMenu* levelsMenu, wxMenu* helpMenu)
{
    // Options added to the view menu
    levelsMenu->Append(IDM_LEVEL0, L"&Level 0", L"");
    levelsMenu->Append(IDM_LEVEL1, L"&Level 1", L"");
    levelsMenu->Append(IDM_LEVEL2, L"&Level 2", L"");
    levelsMenu->Append(IDM_LEVEL3, L"&Level 3", L"");
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileOpenLevel0, this, IDM_LEVEL0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileOpenLevel1, this, IDM_LEVEL1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileOpenLevel2, this, IDM_LEVEL2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnFileOpenLevel3, this, IDM_LEVEL3);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnSolveLevel, this, IDM_SOLVE);
}


/**
 * Paint event, draws the window.
 *
 * Documentation:
 * https://facweb.cse.msu.edu/cbowen/cse335/wx/wxgraphics/transforms/
 * https://facweb.cse.msu.edu/cbowen/cse335/wx/wxgraphics/creating/
 *
 * @param event Paint event object
 */
void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.Update(elapsed);
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

}

/**
 * Refresh the timer on tick
 * @param event The event for this class
 */
void GameView::OnTimerTick(wxTimerEvent& event)
{
    Refresh();
}

/**
 * Menu handler for File>Solve
 * @param event Mouse event
 */
void GameView::OnSolveLevel(wxCommandEvent &event)
{
    mGame.Solve();
    mGame.IsBoardCorrect();
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void GameView::OnFileOpenLevel0(wxCommandEvent& event)
{
    auto sb = mGame.GetScoreboard();
    sb.ResetTimer();
    mGame.SetScoreboard(sb);
    mGame.SetLevel(0);
    Refresh();
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void GameView::OnFileOpenLevel1(wxCommandEvent& event)
{
    auto sb = mGame.GetScoreboard();
    sb.ResetTimer();
    mGame.SetScoreboard(sb);
    mGame.SetLevel(1);
    Refresh();
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void GameView::OnFileOpenLevel2(wxCommandEvent& event)
{
    auto sb = mGame.GetScoreboard();
    sb.ResetTimer();
    mGame.SetScoreboard(sb);
    mGame.SetLevel(2);
    Refresh();
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void GameView::OnFileOpenLevel3(wxCommandEvent& event)
{
    auto sb = mGame.GetScoreboard();
    sb.ResetTimer();
    mGame.SetScoreboard(sb);
    mGame.SetLevel(3);
    Refresh();
}

/**
 * Default constructor for GameView.
 */
GameView::GameView(){
}

/**
 * Handle the left mouse button down event
 * @param event The mouse click event
 */
void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());
    Refresh();
}

/**
 * Handle the key down for number keys 0-8
 * @param event They key click event
 */
void GameView::OnKeyDown(wxKeyEvent &event)
{
    int keyCode = event.GetKeyCode();
    if(keyCode >=  48 && keyCode <= 56)
    {
        int keyVal = keyCode - 48;
        mGame.SpitNumber(keyVal);
        Refresh();
        mGame.IsBoardCorrect();
    }
    else if(keyCode == 66 || keyCode == 98)
    {
        mGame.OnKeyHeadButtDown();
        mGame.HitContainer();
        Refresh();
    }
    else if(keyCode == 32)
    {
        mGame.OnSpaceDown();
        Refresh();
    }
}