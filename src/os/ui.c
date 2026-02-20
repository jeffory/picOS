#include "ui.h"
#include "../drivers/display.h"
#include "../drivers/keyboard.h"
#include "../drivers/wifi.h"
#include "clock.h"

#include <stdio.h>
#include <string.h>

#define C_HEADER_BG  RGB565(20, 20, 60)
#define C_TEXT       COLOR_WHITE
#define C_TEXT_DIM   COLOR_GRAY
#define C_BATTERY_OK COLOR_GREEN
#define C_BATTERY_LO COLOR_RED
#define C_BORDER     RGB565(60, 60, 100)

void ui_draw_header(const char *title) {
    display_fill_rect(0, 0, FB_WIDTH, 28, C_HEADER_BG);
    display_draw_text(8, 8, title ? title : "", C_TEXT, C_HEADER_BG);

    // Right-side status: lay out right-to-left
    int x = FB_WIDTH - 8;

    // 1. Battery (rightmost)
    int bat = kbd_get_battery_percent();
    if (bat >= 0) {
        char bat_buf[16];
        snprintf(bat_buf, sizeof(bat_buf), "Bat:%d%%", bat);
        int bat_w = (int)strlen(bat_buf) * 6;
        x -= bat_w;
        uint16_t c = (bat > 20) ? C_BATTERY_OK : C_BATTERY_LO;
        display_draw_text(x, 8, bat_buf, c, C_HEADER_BG);
        x -= 12;
    }

    // 2. WiFi
    if (wifi_is_available()) {
        wifi_status_t status = wifi_get_status();
        const char *icon = (status == WIFI_STATUS_CONNECTED) ? "WiFi" : "WiFi!";
        uint16_t c = (status == WIFI_STATUS_CONNECTED) ? C_BATTERY_OK : C_BATTERY_LO;
        
        int icon_w = (int)strlen(icon) * 6;
        x -= icon_w;
        display_draw_text(x, 8, icon, c, C_HEADER_BG);
        x -= 12;
    }

    // 3. Clock
    if (clock_is_set()) {
        char clk_buf[8];
        clock_format(clk_buf, sizeof(clk_buf));
        int clk_w = (int)strlen(clk_buf) * 6;
        x -= clk_w;
        display_draw_text(x, 8, clk_buf, C_TEXT, C_HEADER_BG);
    }

    display_fill_rect(0, 28, FB_WIDTH, 1, C_BORDER);
}

void ui_draw_footer(const char *left_text, const char *right_text) {
    display_fill_rect(0, FB_HEIGHT - 18, FB_WIDTH, 18, C_HEADER_BG);
    display_fill_rect(0, FB_HEIGHT - 18, FB_WIDTH, 1, C_BORDER);
    
    if (left_text && left_text[0]) {
        display_draw_text(8, FB_HEIGHT - 13, left_text, C_TEXT_DIM, C_HEADER_BG);
    }
    
    if (right_text && right_text[0]) {
        int w = display_text_width(right_text);
        display_draw_text(FB_WIDTH - 8 - w, FB_HEIGHT - 13, right_text, C_TEXT_DIM, C_HEADER_BG);
    }
}
