#pragma once

#include <stdint.h>
#include <stdbool.h>

// Draw standard OS header (titlebar) with battery/wifi/clock status indicators
void ui_draw_header(const char *title);

// Draw standard OS footer with optional left and right alignment texts
void ui_draw_footer(const char *left_text, const char *right_text);
