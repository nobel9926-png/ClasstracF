//----------- MAIN.C
// CLASSTRAC ko main (starting) file
// program yahi bata start hunxa
// starting data initialize garxa,
// ani game loop bhitra screen clear garera
// current active screen draw garxa
// yo process window close nahunjel repeat hunxa

#include "raylib.h"
#include "classtrac.h"
#include "home_screen.h"
#include "subject_screen.h"
#include "attendance_screen.h"
#include "report_screen.h"
#include "storage.h"
#include <string.h>

int main(void) {
    InitWindow(WIN_W, WIN_H, "CLASSTRAC - Attendance Management System");
// Application ko main window create garxa
    SetTargetFPS(60);
//screen lai ek sec ma 60 choti redraw garxa , smooth vako tesaile

    ChangeDirectory(GetApplicationDirectory());
// current working folder lai application ko folder banaune
    Storage_Init();
// Storage system initialize garxa
    Font font = GetFontDefault();
// default font load garya
    Screen currentScreen = SCR_HOME;
// starting screen ma homescreen set garya
    bool exitRequested = false;
// suru ma chai program banda hudaina, if exit button click garema....

    // --------starting subjets , subject screen ma dekhine
    Subject subjects[MAX_SUBJECTS] = {
        { "ICT 101" },
        { "COMP 102" },
        { "MATH 101" },
        { "COM 105" },
        { "AIMC 101" },
        { "Project" },
    };
    int subjectCount = 6;
    AddSubjectPopup subjectPopup = { false, "" };
    char activeSubject[64] = "";

    // -----------Student roster ho , attendance screen ma dekhine
    Student students[MAX_STUDENTS] = {
        { "BIT202601", "RIYA SHRESTHA",        ST_NONE },
        { "BIT202602", "PUKAR RAI",            ST_NONE },
        { "BIT202603", "BISHAN KOIRALA",       ST_NONE },
        { "BIT202604", "BINISH SHRESTHA",      ST_NONE },
        { "BIT202605", "DIPIKA GIRI",          ST_NONE },
        { "BIT202606", "SIDDHARTHA MANANDHAR", ST_NONE },
        { "BIT202607", "SUBHAN KOIRALA",       ST_NONE },
        { "BIT202608", "MD ASIF SERAJ",        ST_NONE },
        { "BIT202609", "PRACHI ADHIKARI",      ST_NONE },
        { "BIT202610", "SNEHA CHAUDHARY",      ST_NONE },
        { "BIT202611", "MANISH KARKI",         ST_NONE },
        { "BIT202612", "NITESH DHAR DWIVEDEE", ST_NONE },
        { "BIT202613", "SUBHA GHIMIRE",        ST_NONE },
        { "BIT202614", "RALEN SHRESTHA",       ST_NONE },
        { "BIT202615", "RUPA CHAULAGHAIN",     ST_NONE },
        { "BIT202616", "PRAPTI SUNUWAR",       ST_NONE },
        { "BIT202617", "ISHU THAPA",           ST_NONE },
        { "BIT202618", "BILISHA KHATRI",       ST_NONE },
        { "BIT202619", "RYAN SHRESTHA",        ST_NONE },
        { "BIT202620", "RITIKA TIMILSINA",     ST_NONE },
        { "BIT202621", "NOBEL DEVKOTA",        ST_NONE },
        { "BIT202622", "MATRIKA YADAV",        ST_NONE },
        { "BIT202623", "SADIKSHYA NEUPANE",    ST_NONE },
    };
    int studentCount = 23;
    AddStudentPopup studentPopup = { false, "", "", 0 };

    char statusMsg[128] = "Mark attendance, then press Save.";
// attendance screen ma dekhaune starting status message
    int subjectScroll = 0;
    int attendanceScroll = 0;
    int reportScroll = 0;
    int reportViewScroll = 0;
// different screen haruko scroll position store garna lai
    char selectedReportFile[256] = "";
// Open garna choose gareko report file ko naam rakhna , initially 0 hunxa

    while (!WindowShouldClose() && !exitRequested) {
        BeginDrawing();
// naya frame draw garna start garne
        ClearBackground(COL_BG);
// purano frame hataera background color fill garna
        switch (currentScreen) {
            case SCR_HOME:
                DrawHomeScreen(&currentScreen, font, &exitRequested);
                break;

            case SCR_SUBJECT:
                DrawSubjectScreen(&currentScreen, font, subjects, &subjectCount,
                     &subjectPopup, activeSubject, &subjectScroll);
                break;

            case SCR_ATTENDANCE:
                DrawAttendanceScreen(&currentScreen, font, students, &studentCount,
                    &studentPopup, statusMsg, &attendanceScroll, activeSubject);
                break;

            case SCR_REPORT_LIST:
                DrawReportListScreen(&currentScreen, font, &reportScroll, selectedReportFile, &reportViewScroll);
                break;

            case SCR_REPORT_VIEW:
                DrawReportViewScreen(&currentScreen, font, selectedReportFile, &reportViewScroll);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}