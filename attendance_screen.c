#include "attendance_screen.h"
#include "storage.h"
#include "ui.h"
#include <string.h>
#include <stdio.h>

#define ROW_HEIGHT   40
#define LIST_TOP     110
#define LIST_BOTTOM  (WIN_H - 110)
#define VISIBLE_ROWS ((LIST_BOTTOM - LIST_TOP) / ROW_HEIGHT)
//macros define garya

//-----------------------------------------------------------------------------------------------------
static void DrawAddStudentPopup(AddStudentPopup *popup, Student *students, int *studentCount, Font font) {
    DrawRectangle(0, 0, WIN_W, WIN_H, (Color){ 0, 0, 0, 120 });
//background lai transparent black banako , popup focus garya
//static cuz yo function yei file ma matra use garna milxa aba

    Rectangle box = { WIN_W / 2 - 180, WIN_H / 2 - 100, 360, 200 }; 
    //rectangle define
    //popup ko main white box ho yo
    DrawRectangleRec(box, COL_WHITE);
    DrawRectangleLinesEx(box, 2, COL_BORDER);
    //popup exactly center ma open hunxa, ani border thickness 2 hunxa

    DrawTextEx(font, "Add Student", (Vector2){ box.x + 20, box.y + 15 }, 20, 1, COL_TEXT);
    //popup ko title draw garxa, ani tyo text ko color COL_TEXT hunxa

    Rectangle rollBox = { box.x + 20, box.y + 50, box.width - 40, 36 };
    //rectangle define garya rollBox
    Rectangle nameBox = { box.x + 20, box.y + 95, box.width - 40, 36 };

    //aba chai mouse ko behavior track wala part
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, rollBox)) popup->field = 0;
        //condition true vayo vane keyboard input rollbox ma janxa
        else if (CheckCollisionPointRec(mouse, nameBox)) popup->field = 1;
        //similarly condition true -> keyboard input namebox ma janxa
        //yaha samma box haru define vayera mouse track vairako matra xa
    }

    DrawInputBox(rollBox, popup->roll, popup->field == 0, font);
    // roll number ko input box screen ma draw garxa
    // field 0 huda rollBox active hunxa
    DrawInputBox(nameBox, popup->name, popup->field == 1, font);
    // field 1 huda nameBox active hunxa

    if (popup->field == 0) HandleTextInput(popup->roll, sizeof(popup->roll));
    else HandleTextInput(popup->name, sizeof(popup->name));
    //yesle kun textbox active xa tesma matra keyboard type garna dinxa


    Rectangle addBtn    = { box.x + 20, box.y + 145, 150, 40 };
    Rectangle cancelBtn = { box.x + 190, box.y + 145, 150, 40 };
//yo ta rectangle button define garya , popup ma ADD AND CANCEL wala
    if (Button(addBtn, "Add", COL_GREEN, COL_GREEN_HOVER, font, 18)) {
        if (strlen(popup->roll) > 0 && strlen(popup->name) > 0 && *studentCount < MAX_STUDENTS)
        // Roll, Name empty chaina ra student list full pani chaina bhane matra add garxa
         {
            strncpy(students[*studentCount].rollNo, popup->roll, sizeof(students[0].rollNo) - 1);
            strncpy(students[*studentCount].name, popup->name, sizeof(students[0].name) - 1);
            students[*studentCount].status = ST_NONE;
            (*studentCount)++;
    // Popup bata Roll Number student array ma copy garxa
    // Popup bata Name student array ma copy garxa
    // Naya student ko attendance status default NONE rakxa
    // Student add bhayepaxi total student count 1 le badhauxa
        }
        popup->visible = false;
    // Student add bhayepaxi popup close garxa
        popup->roll[0] = '\0';
        popup->name[0] = '\0';
    //yo chai roll input box and then name input box ma previous text clear garxa
        popup->field = 0;
    // Input focus feri Roll Number box ma reset garxa
    }
    if (Button(cancelBtn, "Cancel", COL_GRAY_BTN, COL_GRAY_HOVER, font, 18)) {
        popup->visible = false;
        popup->roll[0] = '\0';
        popup->name[0] = '\0';
        popup->field = 0;
    // cancel click garda popup close garera sabai input clear ra reset garxa
    }
}
//-----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//yetti mathi samma popup ko kaam haru thyo 
//tala ko ley attendance page ko sab ui ra logic handle garxa
void DrawAttendanceScreen(Screen *currentScreen, Font font,
    Student *students, int *studentCount, AddStudentPopup *popup,
    char *statusMsg, int *scrollOffset,
    const char *activeSubject) {

    //suru ma header vako 
    DrawRectangle(0, 0, WIN_W, 70, COL_HEADER);
    char headerText[80];
    snprintf(headerText, sizeof(headerText), "Attendance - %s", activeSubject);
    //yesma Attendance-%s ley currently kun subject ko record vairako tesko name dekhauxa
    DrawTextEx(font, headerText, (Vector2){ 30, 22 }, 24, 1, COL_WHITE);


    Rectangle backBtn = { WIN_W - 120, 15, 90, 40 };
    if (Button(backBtn, "Back", COL_GRAY_BTN, COL_GRAY_HOVER, font, 16)) {
        *currentScreen = SCR_SUBJECT;
    // back button vaihalyo 
    }

    // ------- tala scrolling logic
    // Mouse wheel moves the list by one row at a time. Clamp so we
    // never scroll past the first or last student.
    int maxOffset = *studentCount - VISIBLE_ROWS;
    //maxoffset = maximum kati samma scroll garna milxa?
    if (maxOffset < 0) maxOffset = 0;
    // Total students ra visible rows ko basis ma maximum scroll limit calculate garxa
    *scrollOffset -= (int)GetMouseWheelMove();
    if (*scrollOffset < 0) *scrollOffset = 0;
    if (*scrollOffset > maxOffset) *scrollOffset = maxOffset;



    //--------tala ko column headers ko lai
    DrawTextEx(font, "Roll No", (Vector2){ 30, LIST_TOP - 28 }, 16, 1, COL_TEXT_LIGHT);
    DrawTextEx(font, "Name",    (Vector2){ 150, LIST_TOP - 28 }, 16, 1, COL_TEXT_LIGHT);
    DrawTextEx(font, "Status",  (Vector2){ 470, LIST_TOP - 28 }, 16, 1, COL_TEXT_LIGHT);
//column heading chai list vanda ali mathi dekhinxa kina ki List_Top - 28 pixels gareko xa

    //--------- student rows haru 
    for (int row = 0; row < VISIBLE_ROWS; row++) {
// visible vako sabai student row draw garne
        int i = row + *scrollOffset;
// scroll anusar actual student index nikalne
        if (i >= *studentCount) break;
// student sakiyepaxi loop stop garne


        float y = LIST_TOP + row * ROW_HEIGHT;
//  row ko vertical position calculate garxa
        if (row % 2 == 1) DrawRectangle(20, y, WIN_W - 40, ROW_HEIGHT, COL_ROW_ALT);
// odd row ma halka gray background halxa, UI ramro banako
        DrawTextEx(font, students[i].rollNo, (Vector2){ 30, y + 10 }, 16, 1, COL_TEXT);
        DrawTextEx(font, students[i].name,   (Vector2){ 150, y + 10 }, 16, 1, COL_TEXT);
// student ko roll number ra name dwar garxa screen ma 

        
        Rectangle pBtn = { 470, y + 4, 32, 32 };
        Rectangle aBtn = { 510, y + 4, 32, 32 };
        Rectangle lBtn = { 550, y + 4, 32, 32 };
// present, absent ra late button ko position banako
        Color pColor = (students[i].status == ST_PRESENT) ? COL_PRESENT : COL_NONE;
        Color aColor = (students[i].status == ST_ABSENT)  ? COL_ABSENT  : COL_NONE;
        Color lColor = (students[i].status == ST_LATE)    ? COL_LATE    : COL_NONE;
// ?: lai ternary operator vaninxa , short form of if else ho
// student index ko status herera color choose garxa

        if (Button(pBtn, "P", pColor, COL_PRESENT, font, 16)) students[i].status = ST_PRESENT;
        if (Button(aBtn, "A", aColor, COL_ABSENT, font, 16))  students[i].status = ST_ABSENT;
        if (Button(lBtn, "L", lColor, COL_LATE, font, 16))    students[i].status = ST_LATE;
// core interaction, button function used
// if P click vayo vane , student[i].status = presnt return garxa , likewise

        
        Rectangle removeBtn = { WIN_W - 70, y + 4, 32, 32 };
// X delete button ko position define garya
        if (Button(removeBtn, "X", COL_RED, COL_RED_HOVER, font, 14)) {
            for (int j = i; j < *studentCount - 1; j++) students[j] = students[j + 1];
            (*studentCount)--;
// delete bhayeko student pachhadi ko sabai lai ek step agadi sarxa
// basically array ma gap narakhya
//student[j+1] ley student mathi copy garxa as yo process ma iterative duplication haru aauxa 
        }
    }


    //------------tala ko buttons , add student , save attendance
    Rectangle addBtn  = { 30, WIN_H - 60, 160, 40 };
    Rectangle saveBtn = { 200, WIN_H - 60, 160, 40 };
//rectangle banako 

    if (Button(addBtn, "+ Add Student", COL_BLUE, COL_BLUE_HOVER, font, 16)) {
        popup->visible = true;
// Add Student button click bhaye popup kholxa
// conditon vaihalyo 
    }
    if (Button(saveBtn, "Save Attendance", COL_GREEN, COL_GREEN_HOVER, font, 16)) {
// Save Attendance button click bhaye save process start garxa
        if (Storage_SaveAttendance(activeSubject, students, *studentCount)) {
//save function 
// Attendance file ma save garne ra success/fail check garxa
//yesle actual ma 3 ta kura pathako xa
            snprintf(statusMsg, 128, "Saved! Check the Reports screen to view it.");
// Save successful bhaye success message statusMsg ma rakhxa
        } else {
            snprintf(statusMsg, 128, "Could not save the file.");
        }
    }

    //------------tala ko status msg actual screen draw
    DrawTextEx(font, statusMsg, (Vector2){ 380, WIN_H - 48 }, 16, 1, COL_TEXT_LIGHT);
// statusMsg variable ma bhayeko text screen ma draw garxa

    if (popup->visible) {
        DrawAddStudentPopup(popup, students, studentCount, font);
// Add Student popup draw garne ra popup ko logic handle garne
// notice DrawAddStudentPopup function use vako xa feri
    
}
    }
//-----------------------------------------------------------------------------------------------