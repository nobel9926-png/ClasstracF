// =============================================================
// UI_HELPERS.H
// Small reusable drawing/input helpers used across every screen.
// =============================================================
#ifndef UI_HELPERS_H
#define UI_HELPERS_H

#include "raylib.h"
#include "classtrac_common.h"

bool IsButtonHovered(Rectangle r);
bool IsButtonClicked(Rectangle r);

void DrawRoundedBtn(Rectangle r, Color base, Color hover, const char *label, Font font, float fontSize);
void DrawStatusBtn(Rectangle r, const char *label, Color base, bool active);

// Draws a vertical "..." (kebab / three-dot) menu button centered inside
// `hit`. Shows `backdrop` as a circular hover highlight behind the dots
// (pass a transparent colour, e.g. {0,0,0,0}, for no backdrop) and draws
// the three dots in `dotColor`. Hit-testing is left to the caller via
// IsButtonHovered/IsButtonClicked(hit) so callers can react to the click.
void DrawKebabMenu(Rectangle hit, Color dotColor, Color backdrop);

#endif // UI_HELPERS_H
