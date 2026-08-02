// =============================================================
// UI_HELPERS.C
// =============================================================
#include "ui_helpers.h"

bool IsButtonHovered(Rectangle r) {
    Vector2 m = GetMousePosition();
    return CheckCollisionPointRec(m, r);
}

bool IsButtonClicked(Rectangle r) {
    return IsButtonHovered(r) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

void DrawRoundedBtn(Rectangle r, Color base, Color hover, const char *label, Font font, float fontSize) {
    Color c = IsButtonHovered(r) ? hover : base;
    DrawRectangleRounded(r, 0.12f, 8, c);
    Vector2 ts = MeasureTextEx(font, label, fontSize, 1);
    DrawTextEx(font, label,
        (Vector2){r.x + r.width/2 - ts.x/2, r.y + r.height/2 - ts.y/2},
        fontSize, 1, COL_WHITE);
}

void DrawStatusBtn(Rectangle r, const char *label, Color base, bool active) {
    Color bg = active ? base : (Color){210,210,215,255};
    Color border = active ? base : (Color){180,180,185,255};
    DrawRectangleRounded(r, 0.25f, 8, bg);
    if (!active) DrawRectangleRoundedLines(r, 0.25f, 8, border);
    Vector2 ts = MeasureTextEx(GetFontDefault(), label, 16, 1);
    DrawText(label, (int)(r.x + r.width/2 - ts.x/2),
             (int)(r.y + r.height/2 - ts.y/2), 16,
             active ? COL_WHITE : COL_TEXT_MID);
}

void DrawKebabMenu(Rectangle hit, Color dotColor, Color backdrop) {
    Vector2 center = { hit.x + hit.width / 2.0f, hit.y + hit.height / 2.0f };
    float radius = (hit.width < hit.height ? hit.width : hit.height) / 2.0f;

    if (IsButtonHovered(hit)) {
        DrawCircleV(center, radius, backdrop);
    }

    const float dotR = 2.4f;
    const float gap  = 7.0f;
    DrawCircleV((Vector2){center.x, center.y - gap}, dotR, dotColor);
    DrawCircleV(center,                               dotR, dotColor);
    DrawCircleV((Vector2){center.x, center.y + gap}, dotR, dotColor);
}
