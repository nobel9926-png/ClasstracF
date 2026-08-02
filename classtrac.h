//yo chai header file banauna, every screen ma chaine components 
//colors, enums, size, buttons , struct haru lai reuse garna milxa
//before starting any aru file, first include this header file in that file
#ifndef CLASSTRAC_H
#define CLASSTRAC_H
//yesle duplications definitions of header files avoid garxa , also avoids compiler errors

#include "raylib.h"
#include <stdbool.h>
//stdbool le boolean values support garxa, true or false

typedef enum {
    SCR_HOME,
    SCR_SUBJECT,
    SCR_ATTENDANCE,
    SCR_REPORT_LIST,
    SCR_REPORT_VIEW
} Screen;
//screen enum le chai different screens haru define garxa, jasko use aru file ma garna milxa
//main.c le Draw...Screen() use garxa screen call garna ko lagi

typedef enum { ST_NONE = 0,
     ST_PRESENT,
      ST_ABSENT,
       ST_LATE
 } AttStatus;
//attendance status define garya

typedef struct {
    char rollNo[16];
    char name[40];
    AttStatus status;
} Student;

typedef struct {
    char name[32];
} Subject;
//data structure haru define garna ko lagi ho

typedef struct {
    bool visible;
    char roll[16];
    char name[40];
    int  field;   
} AddStudentPopup;
// Small popup used for "add student" (roll + name, two fields)
// 0 = roll box is focused, 1 = name box is focused

typedef struct {
    bool visible;
    char name[32];
} AddSubjectPopup;
// Small popup used for "add subject" (just one field)

#define WIN_W          900
#define WIN_H          640
#define MAX_SUBJECTS   15
#define MAX_STUDENTS   45
#define MAX_REPORTS    100
#define RECORDS_DIR    "records"
//yo chai windows screen limits haru 

#define COL_BG          (Color){ 244, 244, 246, 255 }
#define COL_HEADER      (Color){ 45, 48, 58, 255 }
#define COL_TEXT        (Color){ 35, 35, 40, 255 }
#define COL_TEXT_LIGHT  (Color){ 120, 120, 125, 255 }
#define COL_WHITE       (Color){ 255, 255, 255, 255 }
#define COL_BORDER      (Color){ 205, 205, 210, 255 }
#define COL_ROW_ALT     (Color){ 235, 237, 240, 255 }

#define COL_BLUE        (Color){ 40, 95, 175, 255 }
#define COL_BLUE_HOVER  (Color){ 28, 75, 145, 255 }
#define COL_GREEN       (Color){ 40, 150, 85, 255 }
#define COL_GREEN_HOVER (Color){ 28, 120, 65, 255 }
#define COL_RED         (Color){ 190, 45, 60, 255 }
#define COL_RED_HOVER   (Color){ 150, 30, 45, 255 }
#define COL_GRAY_BTN    (Color){ 130, 133, 140, 255 }
#define COL_GRAY_HOVER  (Color){ 105, 108, 115, 255 }

#define COL_PRESENT     (Color){ 40, 150, 85, 255 }
#define COL_ABSENT      (Color){ 190, 45, 60, 255 }
#define COL_LATE        (Color){ 210, 140, 15, 255 }
#define COL_NONE        (Color){ 190, 190, 195, 255 }
//yo chai colors haru define garna ko lagi ho, jasko use aru file ma garna milxa 
//(Color){ R, G, B, A } color format ho, R=Red, G=Green, B=Blue, A=Alpha (transparency)
//eg R ko number dherai vayo vane red dominant dekhinxa


#endif 
//last ma header file lai end garya

