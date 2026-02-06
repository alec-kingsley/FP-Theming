#include "palette_info.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void file_read_until(FILE *file, const char *str) {
    int c;
    const size_t len = strlen(str);
    size_t str_idx = 0;

    while (str_idx < len) {
        c = fgetc(file);
        if (c == EOF) {
            printf("ERROR: failed to find %s in file\n", str);
            exit(1);
        }
        if (c == str[str_idx]) {
            str_idx++;
        } else {
            str_idx = 0;
        }
    }
    str_idx = 0;
}

static uint8_t invalid_digit_error(char c) {
    printf("ERROR: invalid digit: %c\n", c);
    exit(1);
    return 0;
}

static uint8_t number_from_hex_digit(char c) {
    return ('0' <= c && c <= '9')   ? c - '0'
           : ('a' <= c && c <= 'f') ? c - 'a' + 10
           : ('A' <= c && c <= 'F') ? c - 'A' + 10
                                    : invalid_digit_error(c);
}

static uint8_t number_from_dec_digit(char c) {
    return ('0' <= c && c <= '9') ? c - '0' : invalid_digit_error(c);
}

static uint8_t file_read_number(FILE *file) {
    uint8_t base = 10;
    int c = fgetc(file);
    uint8_t number = 0;
    if (c == EOF) {
        return 0;
    }
    if (c == '$') {
        base = 16;
    } else {
        number = number_from_dec_digit(c);
    }
    while (c = fgetc(file), c != EOF && !isspace(c) && c != '#') {
        number *= base;
        number
            += base == 16 ? number_from_hex_digit(c) : number_from_dec_digit(c);
    }
    return number;
}

static void palette_read(palette_entry_t *palette, FILE *ini_file) {
    char palette_line_label[32];
    size_t i;
    file_read_until(ini_file, "[Colors]\n");
    for (i = 0; i < PALETTE_SIZE; i++) {
        if (i % PALETTE_ENTRIES_PER_LINE == 0) {
            sprintf(palette_line_label, "Palette_%lu_%lu=#", i + 1,
                    i + PALETTE_ENTRIES_PER_LINE);
            file_read_until(ini_file, palette_line_label);
        }
        palette[i] = file_read_number(ini_file);
    }
    fclose(ini_file);
}

static void write_palette_load_c(palette_entry_t *palette) {
    FILE *palette_load_c = fopen("palette_load.c", "w");
    if (palette_load_c == NULL) {
        printf("Failed to open palette_load.c for writing");
        exit(1);
    }

    fprintf(palette_load_c, "#include \"palette_load.h\"\n");
    fprintf(palette_load_c, "#include \"palette_info.h\"\n");


    fprintf(palette_load_c, "void build_blue_window_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_frame_passive] = %i;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_frame_passive]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_frame_active] = %i;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_frame_active]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_frame_icon] = %i;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_frame_icon]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_page] = %i;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_icon] = %i;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_icon]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_normal_text] = %i;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_normal_text]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_cyan_window_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_frame_passive] = %i;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_frame_passive]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_frame_active] = %i;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_frame_active]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_frame_icon] = %i;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_frame_icon]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_page] = %i;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_icon] = %i;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_icon]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_normal_text] = %i;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_normal_text]);
    fprintf(palette_load_c, "}\n\n");
    

    fprintf(palette_load_c, "void build_gray_window_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_frame_passive] = %i;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_frame_passive]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_frame_active] = %i;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_frame_active]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_frame_icon] = %i;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_frame_icon]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_page] = %i;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_icon] = %i;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_icon]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_normal_text] = %i;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_normal_text]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_blue_dialog_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_background] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_background]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_icon] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_icon]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_page] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_static_text] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_static_text]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_label] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_label]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_label] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_label]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_label] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_label]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_button] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_default_button] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_default_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_button] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_button] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_button] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_button_shadow] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_button_shadow]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_cluster] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_cluster]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_cluster] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_cluster]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_cluster] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_cluster]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_input] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_input]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_input] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_input]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_input_arrow] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_input_arrow]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_button] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_sides] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_sides]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_barpage] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_barpage]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_bar_icon] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_bar_icon]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_list] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_list]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_list] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_list]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_focused_list] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_focused_list]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_list_divider] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_list_divider]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_info_pane] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_info_pane]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_cluster] = %i;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_cluster]);
    fprintf(palette_load_c, "}\n\n");
    

    fprintf(palette_load_c, "void build_cyan_dialog_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_background] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_background]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_icon] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_icon]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_page] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_static_text] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_static_text]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_label] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_label]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_label] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_label]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_label] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_label]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_button] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_default_button] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_default_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_button] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_button] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_button] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_button_shadow] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_button_shadow]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_cluster] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_cluster]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_cluster] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_cluster]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_cluster] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_cluster]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_input] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_input]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_input] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_input]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_input_arrow] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_input_arrow]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_button] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_sides] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_sides]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_barpage] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_barpage]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_bar_icon] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_bar_icon]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_list] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_list]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_list] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_list]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_focused_list] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_focused_list]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_list_divider] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_list_divider]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_info_pane] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_info_pane]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_cluster] = %i;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_cluster]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_gray_dialog_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_background] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_background]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_icon] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_icon]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_page] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_static_text] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_static_text]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_label] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_label]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_label] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_label]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_label] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_label]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_button] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_default_button] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_default_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_button] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_button] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_button] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_button_shadow] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_button_shadow]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_cluster] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_cluster]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_cluster] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_cluster]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_cluster] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_cluster]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_input] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_input]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_input] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_input]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_input_arrow] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_input_arrow]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_button] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_sides] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_sides]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_barpage] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_barpage]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_bar_icon] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_bar_icon]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_list] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_list]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_list] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_list]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_focused_list] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_focused_list]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_list_divider] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_list_divider]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_info_pane] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_info_pane]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_cluster] = %i;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_cluster]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_menu_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[menu_normal] = %i;\n", palette[menu_normal]);
    fprintf(palette_load_c, "\tpalette[menu_disabled] = %i;\n", palette[menu_disabled]);
    fprintf(palette_load_c, "\tpalette[menu_shortcut] = %i;\n", palette[menu_shortcut]);
    fprintf(palette_load_c, "\tpalette[menu_selected] = %i;\n", palette[menu_selected]);
    fprintf(palette_load_c, "\tpalette[menu_select_disabled] = %i;\n", palette[menu_select_disabled]);
    fprintf(palette_load_c, "\tpalette[menu_shortcut_selected] = %i;\n", palette[menu_shortcut_selected]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_desktop_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[desktop_color] = %i;\n", palette[desktop_color]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_browser_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[browser_frame_passive] = %i;\n", palette[browser_frame_passive]);
    fprintf(palette_load_c, "\tpalette[browser_frame_active] = %i;\n", palette[browser_frame_active]);
    fprintf(palette_load_c, "\tpalette[browser_frame_icon] = %i;\n", palette[browser_frame_icon]);
    fprintf(palette_load_c, "\tpalette[browser_scroll_bar_page] = %i;\n", palette[browser_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[browser_scroll_bar_icons] = %i;\n", palette[browser_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[browser_normal_text] = %i;\n", palette[browser_normal_text]);
    fprintf(palette_load_c, "\tpalette[browser_selected_text] = %i;\n", palette[browser_selected_text]);
    fprintf(palette_load_c, "\tpalette[browser_active_item] = %i;\n", palette[browser_active_item]);
    fprintf(palette_load_c, "\tpalette[browser_inactive_item] = %i;\n", palette[browser_inactive_item]);
    fprintf(palette_load_c, "\tpalette[browser_focused_item] = %i;\n", palette[browser_focused_item]);
    fprintf(palette_load_c, "\tpalette[browser_selected_item] = %i;\n", palette[browser_selected_item]);
    fprintf(palette_load_c, "\tpalette[browser_divider] = %i;\n", palette[browser_divider]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_clock_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[clock_clockview] = %i;\n", palette[clock_clockview]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_editor_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[editor_frame_passive] = %i;\n", palette[editor_frame_passive]);
    fprintf(palette_load_c, "\tpalette[editor_frame_active] = %i;\n", palette[editor_frame_active]);
    fprintf(palette_load_c, "\tpalette[editor_frame_icon] = %i;\n", palette[editor_frame_icon]);
    fprintf(palette_load_c, "\tpalette[editor_scroll_bar_page] = %i;\n", palette[editor_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[editor_scroll_bar_icons] = %i;\n", palette[editor_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[editor_normal_text] = %i;\n", palette[editor_normal_text]);
    fprintf(palette_load_c, "\tpalette[editor_selected_text] = %i;\n", palette[editor_selected_text]);
    fprintf(palette_load_c, "\tpalette[editor_highlight_column] = %i;\n", palette[editor_highlight_column]);
    fprintf(palette_load_c, "\tpalette[editor_highlight_row] = %i;\n", palette[editor_highlight_row]);
    fprintf(palette_load_c, "\tpalette[editor_error_messages] = %i;\n", palette[editor_error_messages]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_help_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[help_frame_passive] = %i;\n", palette[help_frame_passive]);
    fprintf(palette_load_c, "\tpalette[help_frame_active] = %i;\n", palette[help_frame_active]);
    fprintf(palette_load_c, "\tpalette[help_frame_icon] = %i;\n", palette[help_frame_icon]);
    fprintf(palette_load_c, "\tpalette[help_scroll_bar_page] = %i;\n", palette[help_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[help_scroll_bar_icons] = %i;\n", palette[help_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[help_help_text] = %i;\n", palette[help_help_text]);
    fprintf(palette_load_c, "\tpalette[help_help_links] = %i;\n", palette[help_help_links]);
    fprintf(palette_load_c, "\tpalette[help_selected_link] = %i;\n", palette[help_selected_link]);
    fprintf(palette_load_c, "\tpalette[help_selected_text] = %i;\n", palette[help_selected_text]);
    fprintf(palette_load_c, "\tpalette[help_html_heading1] = %i;\n", palette[help_html_heading1]);
    fprintf(palette_load_c, "\tpalette[help_html_heading2] = %i;\n", palette[help_html_heading2]);
    fprintf(palette_load_c, "\tpalette[help_html_heading3] = %i;\n", palette[help_html_heading3]);
    fprintf(palette_load_c, "\tpalette[help_html_heading4] = %i;\n", palette[help_html_heading4]);
    fprintf(palette_load_c, "\tpalette[help_html_heading5] = %i;\n", palette[help_html_heading5]);
    fprintf(palette_load_c, "\tpalette[help_html_heading6] = %i;\n", palette[help_html_heading6]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_syntax_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[syntax_whitespace] = %i;\n", palette[syntax_whitespace]);
    fprintf(palette_load_c, "\tpalette[syntax_comments] = %i;\n", palette[syntax_comments]);
    fprintf(palette_load_c, "\tpalette[syntax_reserved_words] = %i;\n", palette[syntax_reserved_words]);
    fprintf(palette_load_c, "\tpalette[syntax_identifiers] = %i;\n", palette[syntax_identifiers]);
    fprintf(palette_load_c, "\tpalette[syntax_strings] = %i;\n", palette[syntax_strings]);
    fprintf(palette_load_c, "\tpalette[syntax_numbers] = %i;\n", palette[syntax_numbers]);
    fprintf(palette_load_c, "\tpalette[syntax_hex_numbers] = %i;\n", palette[syntax_hex_numbers]);
    fprintf(palette_load_c, "\tpalette[syntax_assembler] = %i;\n", palette[syntax_assembler]);
    fprintf(palette_load_c, "\tpalette[syntax_symbols] = %i;\n", palette[syntax_symbols]);
    fprintf(palette_load_c, "\tpalette[syntax_directives] = %i;\n", palette[syntax_directives]);
    fprintf(palette_load_c, "\tpalette[syntax_tabs] = %i;\n", palette[syntax_tabs]);
    fprintf(palette_load_c, "}\n");

    fclose(palette_load_c);
}

int main(int argc, char **argv) {
    FILE *ini_file;
    palette_entry_t palette[PALETTE_SIZE];

    if (argc != 2) {
        printf("usage: %s <fp.ini>\n", argv[0]);
        exit(1);
    }

    ini_file = fopen(argv[1], "r");
    if (ini_file == NULL) {
        printf("Failed to open file\n");
        exit(1);
    }

    palette_read(palette, ini_file);

    write_palette_load_c(palette);
    printf("Successfully wrote to palette_load.c\n");

    return 0;
}