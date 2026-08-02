#ifndef REPORT_SCREEN_H
#define REPORT_SCREEN_H
//header guard vaihalyo
#include "classtrac.h"


void DrawReportListScreen(Screen *currentScreen, Font font,
                           int *scrollOffset, char *selectedFile, int *viewScrollOffset);
// yesle saved reports ko list screen draw garxa
// report haru dekhaunxa, scroll handle garxa,
// report select garna dinxa ani view screen tira pathauxa

void DrawReportViewScreen(Screen *currentScreen, Font font, const char *selectedFile, int *scrollOffset);
// yesle select gareko report ko full details screen draw garxa
// report ko content display garxa ra
// report vitra mathi tala scroll garna milxa
#endif 