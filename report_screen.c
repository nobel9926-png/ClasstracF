
//------------report_screen.c
// yo file ma chai duita screen handle garya hunxa
//suru ma list of CSV files with delete button ani report view screenn hunxa


#include "report_screen.h"
#include "storage.h"
#include "ui.h"
#include <string.h>
#include <stdio.h>

#define ROW_HEIGHT   36
#define LIST_TOP     110
#define LIST_BOTTOM  (WIN_H - 40)
#define VISIBLE_ROWS ((LIST_BOTTOM - LIST_TOP) / ROW_HEIGHT)
// screen ma ekchoti ma kati ota report dekhna milxa calculate garxa
// macros define garya 

//--------------------------------------------------------------------------------
void DrawReportListScreen(Screen *currentScreen, Font font,
                           int *scrollOffset, char *selectedFile, int *viewScrollOffset) {
    
    DrawRectangle(0, 0, WIN_W, 70, COL_HEADER);
    DrawTextEx(font, "Saved Reports", (Vector2){ 30, 22 }, 26, 1, COL_WHITE);

    Rectangle backBtn = { WIN_W - 120, 15, 90, 40 };
    if (Button(backBtn, "Back", COL_GRAY_BTN, COL_GRAY_HOVER, font, 16)) {
        *currentScreen = SCR_HOME;
    // yetti samma header ani back button banayo
    }

    // tala ko code le everytime reread garxa fram by fram gand it means a
    // report saved (or deleted) a moment ago always shows up right away
    static char files[MAX_REPORTS][256];
    //sabai report ko filename store garna array banaeko
    int fileCount = Storage_ListReports(files, MAX_REPORTS);
    // records folder bata sab report ko naam read garxa

    if (fileCount == 0) {
        DrawTextEx(font, "No reports saved yet.", (Vector2){ 30, LIST_TOP }, 18, 1, COL_TEXT_LIGHT);
        return;
    // report xaina vane, no report saved dekhauxa ani function yei sakinxa
    }

    int maxOffset = fileCount - VISIBLE_ROWS;
    if (maxOffset < 0) maxOffset = 0;
    // report kam xa vane scroll garna pardaina
    *scrollOffset -= (int)GetMouseWheelMove();
    // mouse wheel ghumauda scroll value update garxa
    if (*scrollOffset < 0) *scrollOffset = 0;
    // mathi limit vanda mathi jana didaina
    if (*scrollOffset > maxOffset) *scrollOffset = maxOffset;
    // tala limit vanda tala jana didaina

    char fileToDelete[256] = "";
// yesle delete garne report ko naam temporarily store garxa
    for (int row = 0; row < VISIBLE_ROWS; row++) {
    // visible report haru euta euta gari draw garxa
        int i = row + *scrollOffset;
    // yesle actual file index calculate garxa
        if (i >= fileCount) break;
    // report sakiyo vane loop banda garxa

        float y = LIST_TOP + row * ROW_HEIGHT;
// yo row ko vertical position calculate garxa

        // The row itself (click to view) and the delete button are two
        // separate, non-overlapping rectangles - same trick as the
        // subject tiles, so one click can't trigger both actions.
        Rectangle rowRect = { 30, y, WIN_W - 110, ROW_HEIGHT - 4 };
        // report ko main clickable area banaunxa
        Rectangle delBtn  = { WIN_W - 70, y, 40, ROW_HEIGHT - 4 };
        // delete X button ko area banaunxa

        if (row % 2 == 1) DrawRectangleRec(rowRect, COL_ROW_ALT);
        // odd row lai arko background color dinxa , better ui vanum

        Vector2 mouse = GetMousePosition();
        bool hovered = CheckCollisionPointRec(mouse, rowRect);
        if (hovered) DrawRectangleLinesEx(rowRect, 1, COL_BLUE);
        //yesle mouse ko current position ra hovering track garera border banauxa 

        DrawTextEx(font, files[i], (Vector2){ rowRect.x + 10, rowRect.y + 8 }, 16, 1, COL_TEXT);
        // report ko filename screen ma draw garxa, pixels haru milako xa

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            strncpy(selectedFile, files[i], 255);
        // click gareko report ko naam selectedFile ma copy garxa

            *viewScrollOffset = 0;
        // report open huda scroll top bata start garxa
            *currentScreen = SCR_REPORT_VIEW;
        // report viewing screen open garxa
        }

        if (Button(delBtn, "X", COL_RED, COL_RED_HOVER, font, 14)) {
            strncpy(fileToDelete, files[i], 255);
        //user le  delete garne report ko naam save garxa fileToDeletema
        }
    }

    // Delete after the loop (not while still reading 'files' above)
    if (fileToDelete[0] != '\0') {
    // delete garne filename xa vane matra delete garxa , suru ma check garxa
        Storage_DeleteReport(fileToDelete);
    // selected report lai records folder bata delete garxa
    }
}
//---------------------------------------------------------------------------------

// yo function le CSV ko euta line lai comma ko basis ma xuttai xuttai columns ma split garxa
// static use vako xa, yei file matra yo function use garna milxa

static int SplitCsvLine(const char *line, char cols[][64], int maxCols) {
    int colCount = 0;
    // ahile samma kati ota column split vayo vanera count garxa
    int charIndex = 0;
       // current column vitra character kun index ma rakhne vanera track garxa
    for (int i = 0; line[i] != '\0' && colCount < maxCols; i++) {
    // line ko harek character euta euta gari read garxa
        if (line[i] == ',') {
        // comma bhetiyo vane current column finish garera next column ma janxa
            cols[colCount][charIndex] = '\0';
        // current string ko end ma null character halera string complete garxa
            colCount++;
        // next column ma jana column count badhaunxa
            charIndex = 0;
        //naya column start garda index feri 0 bata start hunxaa
        } else if (charIndex < 63) {
        // current column full navaye samma character copy garxa
            cols[colCount][charIndex] = line[i];
        // character current column ma copy garxa
            charIndex++;
            // character current column ma copy garxa
        }
    }
    cols[colCount][charIndex] = '\0';
    colCount++;
     // last column string lai properly end garera , teslai pani count ma include garxa
    return colCount;
    // total kati ota columns split vayo tyo return garxa
}
//ecxel file ma csv load huda kheri , columns haru xuttyaune kaam
//-------------------------------------------------------------------------------------

// yo function le selected report ko sabai attendance records screen ma display garxa
void DrawReportViewScreen(Screen *currentScreen, Font font, const char *selectedFile, int *scrollOffset) {

    DrawRectangle(0, 0, WIN_W, 70, COL_HEADER);

    DrawTextEx(font, selectedFile, (Vector2){ 30, 22 }, 20, 1, COL_WHITE);
       // open gareko report ko filename header ma dekhaunxa
    Rectangle backBtn = { WIN_W - 120, 15, 90, 40 };

   
    if (Button(backBtn, "Back", COL_GRAY_BTN, COL_GRAY_HOVER, font, 16)) {
        *currentScreen = SCR_REPORT_LIST;
     // back button click vayo vane report list screen ma janxa
    }

    
    static char lines[MAX_STUDENTS + 5][256];
// report file ko sabai lines temporarily store garna array

    int lineCount = Storage_ReadReport(selectedFile, lines, MAX_STUDENTS + 5);
     //yesle selected report file read garera sabai lines array ma store garxa

    if (lineCount == 0) return;
    // report empty xa vane function yehi bata end garxa

    float colRollX = 30, colNameX = 150, colStatusX = 420;
     // Roll No, Name ra Status column ko x position define garxa

    float listTop = LIST_TOP;
    float rowH = 38;
     // yesle list start hune position ra row height define garxa

    int dataCount = lineCount - 1;
     // CSV ko first line header ho, teslai data count bata hataunxa

    float dataTop = listTop + rowH;
    float dataBottom = WIN_H - 20;
    // student data start ra end hune position

    int visibleRows = (int)((dataBottom - dataTop) / rowH);
//aba yesle screen ma ekchoti ma kati rows dekhna milxa calculate garxa

    int maxOffset = dataCount - visibleRows;
    if (maxOffset < 0) maxOffset = 0;
    // maximum scroll limit calculate garxa

    *scrollOffset -= (int)GetMouseWheelMove();
    // mouse wheel use garera scroll update garxa

    if (*scrollOffset < 0) *scrollOffset = 0;
    if (*scrollOffset > maxOffset) *scrollOffset = maxOffset;
     //aba  scroll lai valid range vitra matra rakhxa

    
    DrawTextEx(font, "Roll No", (Vector2){ colRollX, listTop }, 16, 1, COL_TEXT_LIGHT);
    DrawTextEx(font, "Name",    (Vector2){ colNameX, listTop }, 16, 1, COL_TEXT_LIGHT);
    DrawTextEx(font, "Status",  (Vector2){ colStatusX, listTop }, 16, 1, COL_TEXT_LIGHT);
//yesle chai table ko heading haru 
   
    for (int row = 0; row < visibleRows; row++) {
     // visible student rows euta euta gari draw garxa

        int i = 1 + row + *scrollOffset;
        if (i >= lineCount) break;
// CSV ko first header line skip garera actual student data read garxa

        
        char cols[3][64] = { "", "", "" };
        // Roll No, Name ra Status store garna temporary array banako

        SplitCsvLine(lines[i], cols, 3);
        // current CSV line lai 3 ota columns ma split garxa

        float y = dataTop + row * rowH;
         // current row ko y position calculate garxa

        // odd rows lai alternate background color dinxa
        if (row % 2 == 1)
            DrawRectangle(20, y, WIN_W - 40, rowH, COL_ROW_ALT);
    // odd rows lai alternate background color dinxa, better ui vanam

        
        Color statusColor = COL_TEXT;
    // default status color

      
        if (strcmp(cols[2], "Present") == 0) statusColor = COL_PRESENT;
        else if (strcmp(cols[2], "Absent") == 0) statusColor = COL_ABSENT;
        else if (strcmp(cols[2], "Late") == 0) statusColor = COL_LATE;
         // attendance status anusar color change garxa tyo grey, green , red wala

        DrawTextEx(font, cols[0], (Vector2){ colRollX, y + 10 }, 16, 1, COL_TEXT);
        DrawTextEx(font, cols[1], (Vector2){ colNameX, y + 10 }, 16, 1, COL_TEXT);
        DrawTextEx(font, cols[2], (Vector2){ colStatusX, y + 10 }, 16, 1, statusColor);
         // Roll No, Name ra Status screen ma draw garxa
    }
}
//--------------------------------------------------------------------------