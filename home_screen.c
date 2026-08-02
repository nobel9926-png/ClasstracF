#include "home_screen.h"
#include "ui.h" //button call garna lai

//----------------------------------------------------------------------------------------------
void DrawHomeScreen(Screen *currentScreen, Font font, bool *exitRequested)
{
const char *title = "CLASSTRAC";
    const char *subtitle = "Attendance Management System";

    Vector2 titleSize = MeasureTextEx(font, title, 48, 2);
    //yesle chai title le kati space linxa calculate garxa, 
    //ani tyo text size lai titleSize ma store garxa
    DrawTextEx(font, title, (Vector2){ (WIN_W - titleSize.x) / 2, 180 }, 48, 2, COL_TEXT);
    //48 vanya font size ho, 2 vanya spacing ho, COL_TEXT vanya color ho

    Vector2 subSize = MeasureTextEx(font, subtitle, 20, 1);
    DrawTextEx(font, subtitle, (Vector2){ (WIN_W - subSize.x) / 2, 240 }, 20, 1, COL_TEXT_LIGHT);

    Rectangle startBtn   = { WIN_W / 2 - 100, 330, 200, 50 };
    //yesle chai button ko rectangle define garxa, ani tyo rectangle lai startBtn ma store garxa
    Rectangle reportsBtn = { WIN_W / 2 - 100, 400, 200, 50 };
    //format Rectangle rect = { x, y, width, height }; 
    Rectangle exitBtn    = { WIN_W / 2 - 100, 470, 200, 50 };

    if (Button(startBtn, "Start", COL_BLUE, COL_BLUE_HOVER, font, 20)) {
        *currentScreen = SCR_SUBJECT;
    }
    if (Button(reportsBtn, "Reports", COL_GRAY_BTN, COL_GRAY_HOVER, font, 20)) {
        *currentScreen = SCR_REPORT_LIST;
    }
    if (Button(exitBtn, "Exit", COL_RED, COL_RED_HOVER, font, 20)) {
        *exitRequested = true;
    }
}
//----------------------------------------------------------------------------------------------


