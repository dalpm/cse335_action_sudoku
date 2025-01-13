/**
 * @file GameApp.h
 * @author mdoru
 *
 *
 */

#ifndef PROJECT1__GAMEAPP_H
#define PROJECT1__GAMEAPP_H

#include <wx/wx.h>

/**
 * The GameApp class is responsible for initializing and managing the game application.
 */
class GameApp : public wxApp
{
private:

public:
    bool OnInit() override;

};

#endif //PROJECT1__GAMEAPP_H
