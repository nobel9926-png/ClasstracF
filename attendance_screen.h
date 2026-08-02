#ifndef ATTENDANCE_SCREEN_H
#define ATTENDANCE_SCREEN_H

#include "classtrac.h"

void DrawAttendanceScreen(Screen *currentScreen, Font font,
    Student *students, int *studentCount,
    AddStudentPopup *popup,
    char *statusMsg, int *scrollOffset,
    const char *activeSubject);



                           

#endif 