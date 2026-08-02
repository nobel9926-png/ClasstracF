#ifndef SUBJECT_SCREEN_H
#define SUBJECT_SCREEN_H
//suruma header guard

#include "classtrac.h"

void DrawSubjectScreen(Screen *currentScreen, Font font,
 Subject *subjects, int *subjectCount, AddSubjectPopup *popup, char *activeSubject,
  int *scrollOffset);
//function prototype ho, aba chai aru file ma call garna milxa

#endif 