/**
 * @file MainFrame.cpp
 * @author Doruk Alp Mutlu
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"
#include <wx/string.h>

/// The default screen width
const int DEFAULT_WIDTH = 1000;

/// The default screen height
const int DEFAULT_HEIGHT = 800;

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Action Sudoku", wxDefaultPosition, wxSize(DEFAULT_WIDTH, DEFAULT_HEIGHT));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    mGameView = new GameView();
    mGameView->LoadEverything();
    mGameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mGameView, 1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );
    auto fileMenu = new wxMenu();
    auto levelsMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelsMenu, L"&Level" );
    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(IDM_SOLVE, L"&Solve", L"Solve The Current Level");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    mGameView->AddMenus(this, menuBar, fileMenu, levelsMenu, helpMenu);
    SetMenuBar( menuBar );

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Action Sudoku",
                 L"Action Sudoku",
                 wxOK,
                 this);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}


