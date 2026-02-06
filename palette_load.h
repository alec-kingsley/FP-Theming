#ifndef PALETTE_LOAD_H
#define PALETTE_LOAD_H

#include "palette_info.h"

void build_blue_window_palette(palette_entry_t *palette);
void build_gray_window_palette(palette_entry_t *palette);
void build_cyan_window_palette(palette_entry_t *palette);

void build_blue_dialog_palette(palette_entry_t *palette);
void build_gray_dialog_palette(palette_entry_t *palette);
void build_cyan_dialog_palette(palette_entry_t *palette);

void build_menu_palette(palette_entry_t *palette);

void build_desktop_palette(palette_entry_t *palette);

void build_browser_palette(palette_entry_t *palette);

void build_clock_palette(palette_entry_t *palette);

void build_editor_palette(palette_entry_t *palette);

void build_help_palette(palette_entry_t *palette);

void build_syntax_palette(palette_entry_t *palette);

#endif
