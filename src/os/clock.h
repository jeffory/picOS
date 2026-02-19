#pragma once

#include <stdbool.h>
#include <stdint.h>

// ── Software wall-clock (NTP-backed) ─────────────────────────────────────────
//
// SNTP calls clock_sntp_set() once via the SNTP_SET_SYSTEM_TIME macro defined
// in lwipopts.h.  Subsequent reads compute the current UTC time from the
// Pico's ms-since-boot counter, so no RTC hardware is required.

// Called by the SNTP_SET_SYSTEM_TIME macro; sec is seconds since Unix epoch.
void clock_sntp_set(unsigned sec);

// Returns true once clock_sntp_set() has been called.
bool clock_is_set(void);

// UTC Unix seconds since epoch (returns 0 if not yet synced).
uint32_t clock_get_epoch(void);

// Fills *h, *m, *s with local time (UTC + tz_offset from config).
// Returns false if not yet synced.
bool clock_get_time(int *h, int *m, int *s);

// Writes "HH:MM" into buf (null-terminated, needs at least 6 bytes).
// Writes "--:--" if not yet synced.
// Returns false if not yet synced.
bool clock_format(char *buf, int len);
