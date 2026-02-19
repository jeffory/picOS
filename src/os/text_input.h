#pragma once
#include <stdbool.h>

// =============================================================================
// Text Input Overlay Widget
//
// Shows a modal text-entry panel centered on screen, drawn over the current
// framebuffer content (calls display_darken() internally).
//
// keyboard:
//   printable chars  — appended to buffer
//   BTN_BACKSPACE    — delete last character
//   BTN_ENTER        — confirm; returns true
//   BTN_ESC          — cancel; returns false
// =============================================================================

// title    — panel title bar text (e.g. "WiFi Settings")
// prompt   — label above the input field (e.g. "Network (SSID):")
// initial  — pre-filled text (may be NULL or empty)
// out      — buffer to receive entered text on confirmation
// out_len  — size of out including NUL terminator
// Returns true if confirmed (Enter), false if cancelled (Esc).
bool text_input_show(const char *title, const char *prompt,
                     const char *initial, char *out, int out_len);
