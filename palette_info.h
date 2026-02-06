#ifndef PALETTE_INFO_H
#define PALETTE_INFO_H

#include <stddef.h>
#include <stdint.h>
#define PALETTE_SIZE 240
#define PALETTE_ENTRIES_PER_LINE 40

typedef uint8_t palette_entry_t;

typedef enum {
    BLUE,
    CYAN,
    GRAY,

    main_palette_colors_size
} main_palette_colors_t;

#define BLUE_WINDOW_PALETTE_OFF 7
#define CYAN_WINDOW_PALETTE_OFF 15
#define GRAY_WINDOW_PALETTE_OFF 23

const size_t window_palette_offsets[] = {
    BLUE_WINDOW_PALETTE_OFF, CYAN_WINDOW_PALETTE_OFF, GRAY_WINDOW_PALETTE_OFF};

typedef enum {
    window_frame_passive,
    window_frame_active,
    window_frame_icon,
    window_scroll_bar_page,
    window_scroll_bar_icon,
    window_normal_text,

    window_palette_size
} window_palette_entry_t;

#define BLUE_DIALOG_PALETTE_OFF 64
#define CYAN_DIALOG_PALETTE_OFF 96
#define GRAY_DIALOG_PALETTE_OFF 32

const size_t dialog_palette_offsets[] = {
    BLUE_DIALOG_PALETTE_OFF, CYAN_DIALOG_PALETTE_OFF, GRAY_DIALOG_PALETTE_OFF};

typedef enum {
    dialog_frame_background,
    dialog_frame_icon,
    dialog_scroll_bar_page,
    dialog_scroll_bar_icons,
    dialog_static_text,

    dialog_normal_label,
    dialog_selected_label,
    dialog_shortcut_label,

    dialog_normal_button,
    dialog_default_button,
    dialog_selected_button,
    dialog_disabled_button,
    dialog_shortcut_button,
    dialog_button_shadow,

    dialog_normal_cluster,
    dialog_selected_cluster,
    dialog_shortcut_cluster,

    dialog_normal_input,
    dialog_selected_input,
    dialog_input_arrow,

    dialog_history_button,
    dialog_history_sides,
    dialog_history_barpage,
    dialog_history_bar_icon,

    dialog_normal_list,
    dialog_selected_list,
    dialog_focused_list,
    dialog_list_divider,

    dialog_info_pane,
    dialog_disabled_cluster,

    dialog_palette_size
} dialog_palette_entry_t;

#define MENU_PALETTE_OFF 1

typedef enum {
    menu_normal,
    menu_disabled,
    menu_shortcut,
    menu_selected,
    menu_select_disabled,
    menu_shortcut_selected,

    menu_palette_size
} menu_palette_entry_t;

#define DESKTOP_PALETTE_OFF 0

typedef enum {
    desktop_color,

    desktop_palette_size
} desktop_palette_entry_t;

#define BROWSER_PALETTE_OFF 214

typedef enum {
    browser_frame_passive,
    browser_frame_active,
    browser_frame_icon,
    browser_scroll_bar_page,
    browser_scroll_bar_icons,
    browser_normal_text,
    browser_selected_text,
    browser_active_item,
    browser_inactive_item,
    browser_focused_item,
    browser_selected_item,
    browser_divider,

    browser_palette_size
} browser_palette_entry_t;

#define CLOCK_PALETTE_OFF 226

typedef enum {
    clock_clockview,

    clock_palette_size
} clock_palette_entry_t;

#define EDITOR_PALETTE_OFF 166

typedef enum {
    editor_frame_passive,
    editor_frame_active,
    editor_frame_icon,
    editor_scroll_bar_page,
    editor_scroll_bar_icons,
    editor_normal_text = 198 - EDITOR_PALETTE_OFF,
    editor_selected_text = 207 - EDITOR_PALETTE_OFF,
    editor_highlight_column,
    editor_highlight_row,
    editor_error_messages = 213 - EDITOR_PALETTE_OFF,

    editor_palette_size
} editor_palette_entry_t;

#define HELP_PALETTE_OFF 127

typedef enum {
    help_frame_passive,
    help_frame_active,
    help_frame_icon,
    help_scroll_bar_page,
    help_scroll_bar_icons,
    help_help_text = 159 - HELP_PALETTE_OFF,
    help_help_links,
    help_selected_link,
    help_selected_text,
    help_html_heading1 = 228 - HELP_PALETTE_OFF,
    help_html_heading2,
    help_html_heading3,
    help_html_heading4,
    help_html_heading5,
    help_html_heading6,

    help_palette_size
} help_palette_entry_t;

#define SYNTAX_PALETTE_OFF 199

typedef enum {
    syntax_whitespace,
    syntax_comments,
    syntax_reserved_words,
    syntax_identifiers,
    syntax_strings,
    syntax_numbers,
    syntax_hex_numbers = 211 - SYNTAX_PALETTE_OFF,
    syntax_assembler = 205 - SYNTAX_PALETTE_OFF,
    syntax_symbols,
    syntax_directives = 210 - SYNTAX_PALETTE_OFF,
    syntax_tabs = 212 - SYNTAX_PALETTE_OFF,

    syntax_palette_size
} syntax_palette_entry_t;

typedef struct {
    palette_entry_t entries[window_palette_size];
} window_palette_t;

typedef struct {
    palette_entry_t entries[dialog_palette_size];
} dialog_palette_t;

typedef struct {
    palette_entry_t entries[menu_palette_size];
} menu_palette_t;

typedef struct {
    palette_entry_t entries[desktop_palette_size];
} desktop_palette_t;

typedef struct {
    palette_entry_t entries[syntax_palette_size];
} syntax_palette_t;

typedef struct {
    palette_entry_t entries[help_palette_size];
} help_palette_t;

typedef struct {
    palette_entry_t entries[editor_palette_size];
} editor_palette_t;

typedef struct {
    palette_entry_t entries[clock_palette_size];
} clock_palette_t;

typedef struct {
    palette_entry_t entries[browser_palette_size];
} browser_palette_t;

#endif
