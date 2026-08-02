#include "subject_screen.h"
#include "ui.h"
#include <string.h>

#define ROW_H        62
#define ROW_GAP      14
#define LIST_TOP     100
#define LIST_BOTTOM  (WIN_H - 80)
#define VISIBLE_ROWS ((LIST_BOTTOM - LIST_TOP) / (ROW_H + ROW_GAP))
#define DEL_W        60
#define DEL_GAP      15
//yo sabai macros define gareko



//"Add Subject" popup draw garne ra Add/Cancel button handle garne
static void DrawAddSubjectPopup(AddSubjectPopup *popup, Subject *subjects, int *subjectCount, Font font) {
    // yesma static chai yo mathi ko function yetai matra use hos vanera ho, aba aru file ma call garna milena
    DrawRectangle(0, 0, WIN_W, WIN_H, (Color){ 0, 0, 0, 120 });
//yesle chai background lai transparent garxa, ani tyo color black hunxa, ani opacity 120 hunxa
//popup open huda background dark hunxa, ani popup ma focus hunxa
    Rectangle box = { WIN_W / 2 - 180, WIN_H / 2 - 80, 360, 160 };
    //popup exactly center ma open hunxa
    DrawRectangleRec(box, COL_WHITE);
    DrawRectangleLinesEx(box, 2, COL_BORDER);
    //2 vaneko border thickness 

    DrawTextEx(font, "Add Subject", (Vector2){ box.x + 20, box.y + 15 }, 20, 1, COL_TEXT);

    Rectangle inputBox = { box.x + 20, box.y + 50, box.width - 40, 36 };
    //input box ko size milako 
    DrawInputBox(inputBox, popup->name, true, font);
    HandleTextInput(popup->name, sizeof(popup->name));
    //yesle keyboard input read garxa, ani tyo input lai popup->name ma store garxa
    //sizeof ley buffer overflow avoid garxa, ani tyo buffer ko size calculate garxa
    Rectangle addBtn    = { box.x + 20, box.y + 100, 150, 40 };
    Rectangle cancelBtn = { box.x + 190, box.y + 100, 150, 40 };

    if (Button(addBtn, "Add", COL_GREEN, COL_GREEN_HOVER, font, 18)) {
        if (strlen(popup->name) > 0 && *subjectCount < MAX_SUBJECTS) {
            strncpy(subjects[*subjectCount].name, popup->name, sizeof(subjects[0].name) - 1);
            (*subjectCount)++;
    //suru ma duita condition check garxa input empty chaina ra subject count limit bhitra cha ki nai vanera, ani yesle chai subject add garxa
    //then naya subject lai subject array ma store garxa 
    //ani subject count lai increment garxa
        }
        popup->visible = false; //popup close garxa
        popup->name[0] = '\0'; //popup ko name lai empty garxa
    }
    if (Button(cancelBtn, "Cancel", COL_GRAY_BTN, COL_GRAY_HOVER, font, 18)) {
        popup->visible = false;
        popup->name[0] = '\0';
    //user le cancel click garyo vane popup close , name empty , subject add hudaina
    }
}



void DrawSubjectScreen(Screen *currentScreen, Font font,
 Subject *subjects, int *subjectCount, AddSubjectPopup *popup, char *activeSubject, int *scrollOffset) 
 {

    DrawRectangle(0, 0, WIN_W, 70, COL_HEADER);
    DrawTextEx(font, "Select Subject", (Vector2){ 30, 22 }, 26, 1, COL_WHITE);
    //mathi header ko lagi rectangle banauxa, 70 pixel ko hunxa
    Rectangle backBtn = { WIN_W - 120, 15, 90, 40 };
    if (Button(backBtn, "Back", COL_GRAY_BTN, COL_GRAY_HOVER, font, 16)) {
        *currentScreen = SCR_HOME;
    }
    

  //aba Scrolling logics 
    int maxOffset = *subjectCount - VISIBLE_ROWS;
    if (maxOffset < 0) maxOffset = 0; //no negative scroll offset
    *scrollOffset -= (int)GetMouseWheelMove();//yesle mouse wheel read garxa
    if (*scrollOffset < 0) *scrollOffset = 0;
    if (*scrollOffset > maxOffset) *scrollOffset = maxOffset;
    //maxOffset = kati samma tala scroll garna milxa calculate garxa
    //scrollOffset = list ko kun index bata display suru garne


    int deleteIndex = -1; 
    // suru ma chai no subject is marked for deletion, so deleteIndex = -1

    for (int row = 0; row < VISIBLE_ROWS; row++) {
    //yesle chai visible rows ko lagi loop garxa, ani tyo row ma subject display garxa    
        int i = row + *scrollOffset;
    //row ko index(numbering) calculate garera i ma store garxa    
        if (i >= *subjectCount) break; //aba subject sakiyo vane loop break garxa

        float y = LIST_TOP + row * (ROW_H + ROW_GAP);
    //subject buttons row ko y position calculate garera milauxa

        Rectangle tile   = { 30, y, WIN_W - 30 - 30 - DEL_W - DEL_GAP, ROW_H };
        //yesle subject wala rectangle define garera tile ma 
        //window width - 30 (left margin) - 30 (right margin) - DEL_W (delete button width) - DEL_GAP (gap between subject and delete button) calculate garxa
        Rectangle delBtn = { tile.x + tile.width + DEL_GAP, y, DEL_W, ROW_H };
        //delete button ko rectangle define garxa


        // aba chai popup khulda dubject buttons draw hunxa tara clickable hudaina
        // basically popup lai screen ma lock garya 
        if (!popup->visible) {
            //popup visible xa ki xaina
            if (Button(tile, subjects[i].name, COL_BLUE, COL_BLUE_HOVER, font, 20)) {
            //button function call garera use garya , button click ako xa ki nai check garxa
                strncpy(activeSubject, subjects[i].name, 63);
        //selected subject ko name lai activeSubject ma store garxa
                *currentScreen = SCR_ATTENDANCE;
        //user le jun subject select garxa teskai attendance screen ma janxa
            }
            if (Button(delBtn, "X", COL_RED, COL_RED_HOVER, font, 16)) {
                deleteIndex = i;
    //delete button X click garyo vane deleteIndex ma subject ko index store garxa
    //deleteIndex lai loop baata bahira use garera subject delete garxa
            }
        } else {
            DrawRectangleRec(tile, COL_BLUE);
            Vector2 textSize = MeasureTextEx(font, subjects[i].name, 20, 1);
            DrawTextEx(font, subjects[i].name,
                       (Vector2){ tile.x + (tile.width - textSize.x) / 2, tile.y + (tile.height - textSize.y) / 2 },
                       20, 1, COL_WHITE);
            DrawRectangleRec(delBtn, COL_RED);
            Vector2 xSize = MeasureTextEx(font, "X", 16, 1);
            DrawTextEx(font, "X",
                       (Vector2){ delBtn.x + (delBtn.width - xSize.x) / 2, delBtn.y + (delBtn.height - xSize.y) / 2 },
                       16, 1, COL_WHITE);
        }
    //yo line haru chai popup khulda , paxadi dim background ma subject buttons
    //haru draw garxa , maunally draw gareko
    //tini haru clickable hudaina 
    }

    //pahila chai user le X click garda delete garna khojeko 
    //subject ko index store garthyo , aba chai deleteIndex check garera subject delete garxa
    if (deleteIndex >= 0) {
        for (int j = deleteIndex; j < *subjectCount - 1; j++) subjects[j] = subjects[j + 1];
        (*subjectCount)--;
    //yo loop chai array lai left shift garna ho 
    //yesle chai deleteIndex bata last subject samma loop garxa, ani tyo subject lai left shift garxa
    //ani subject count lai decrement garxa
    }

    
    //aba tala ko add subject popup button 
    Rectangle addBtn = { 30, WIN_H - 60, 160, 40 };//rectangle define

    if (!popup->visible) {
        if (Button(addBtn, "+ Add Subject", COL_GREEN, COL_GREEN_HOVER, font, 16)) {
            popup->visible = true;
    //yedi button click vayo vane popup visible true hunxa, ani popup open hunxa
        }
    } else {
        //popup visible xa vane add subject button dim hunxa, ani clickable hudaina
        DrawRectangleRec(addBtn, COL_GREEN);
        //notice hamile button() function call gareko xaina
        const char *label = "+ Add Subject";
        //yesle chai add subject button ko label define garxa
        Vector2 textSize = MeasureTextEx(font, label, 16, 1);
        //Add subject text size calc garera button ko bich ma rakhxa
        DrawTextEx(font, label,
                   (Vector2){ addBtn.x + (addBtn.width - textSize.x) / 2, addBtn.y + (addBtn.height - textSize.y) / 2 },
                   16, 1, COL_WHITE);
    //yesle chai add subject button ko text draw garxa, ani tyo text ko color white hunxa
    }

    if (popup->visible) {
        DrawAddSubjectPopup(popup, subjects, subjectCount, font);
    }
   //yesle chai popup visible xa vane DrawAddSubjectPopup() call garxa, ani popup draw hunxa 
}

    




