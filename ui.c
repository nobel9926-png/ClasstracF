#include<string.h>
#include "ui.h"
//this thing connects this file to ui.h file
//so that we can use the function defined in ui.h in this file

bool Button(
    Rectangle rect,
    const char *label,
    Color normalColor,
    Color hoverColor,
    Font font,
    int fontSize
)  //yo define garya , code aba {}vitra chalxa

{
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, rect);

    bool clicked = hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    DrawRectangleRec(rect, hovered ? hoverColor : normalColor);

   

    Vector2 textSize = MeasureTextEx(font, label, fontSize, 1);
    //yesle chai hamro text le kati space linxa calculate garxa, 
    //ani tyo text size lai textSize ma store garxa
    Vector2 pos = {
    rect.x + (rect.width - textSize.x) / 2,
    rect.y + (rect.height - textSize.y) / 2
    };
    //yesle chai text lai rectangle ko bich ma center garxa
    // ani tyo position pos ma store garxa
    DrawTextEx(font, label, pos, fontSize, 1, WHITE);
    //yesle chai text lai draw garxa, ani tyo text ko color white hunxa

    return clicked;
}

void DrawInputBox(Rectangle rect, const char *text, bool isFocused, Font font) {
    Color borderColor = (Color){ 205, 205, 210, 255 };
    DrawRectangleRec(rect, WHITE);
    DrawRectangleLinesEx(rect, isFocused ? 2 : 1, isFocused ? BLUE : borderColor);
    //yo chai add student wala popup ma duita input box xa 
    //so if user selects 1st box (isfOCUSED true hunxa) vani tyo box ko border blue hunxa
    DrawTextEx(font, text, (Vector2){ rect.x + 8, rect.y + (rect.height - 18) / 2 }, 18, 1, BLACK);
//yesle chai text draw garxa, ani tyo text ko color black hunxa
//input box ko left edge bata 8 pixel ko gap hunxa, ani 
//text box ko height ko bich ma text center hunxa
    

    if (isFocused && ((int)(GetTime() * 2) % 2 == 0)) {
    //getTime() returns the time in seconds since the program started, 
    //tei vayera multiplying by 2 and taking modulo 2 gives us a simple blinking effect
        Vector2 textSize = MeasureTextEx(font, text, 18, 1);
        //yesle chai text ko size measure garxa pixels ma 
        float cursorX = rect.x + 8 + textSize.x + 2;
        //yesle chai input box ma kei type garepaxi cursor kata rakhne calculate garxa
        DrawLine(cursorX, rect.y + 6, cursorX, rect.y + rect.height - 6, BLACK);
        //yesle cursor draw garxa line ko rup ma
    }
}
//yesle chai input box draw garxa, ani tyo box ko color white hunxa
//popup ko lagi ho, ani tyo box ko border black hunxa

void HandleTextInput(char *buffer, int maxLen)
{
    int len = strlen(buffer);

    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 125 && len < maxLen - 1) {
            buffer[len] = (char)key;
            buffer[len + 1] = '\0';
            len++;
        }
        key = GetCharPressed();
        
    }
    if (IsKeyPressed(KEY_BACKSPACE) && len > 0) {
        buffer[len - 1] = '\0';
}
//yesle chai text input handle garxa, ani tyo text ko length calculate garxa
//backspace key press garda text delete garxa









}