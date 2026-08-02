#ifndef UI_H
#define UI_H
//guard le chai duplications definitions of header files avoid garxa , also avoids compiler errors
#include "raylib.h"
#include <stdbool.h>


bool Button(
    Rectangle rect,
    const char *label,
    Color normalColor,
    Color hoverColor,
    Font font,
    int fontSize
);

void DrawInputBox(
    Rectangle rect,
    const char *text,
    bool isFocused,
     Font font
);

void HandleTextInput(char *buffer, int maxLen);



#endif 