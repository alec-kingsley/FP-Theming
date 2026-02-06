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
    fprintf(palette_load_c, "#include \"palette_info.h\"\n\n");


    fprintf(palette_load_c, "void build_blue_window_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_frame_passive] = %02x;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_frame_passive]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_frame_active] = %02x;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_frame_active]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_frame_icon] = %02x;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_frame_icon]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_page] = %02x;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_icon] = %02x;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_scroll_bar_icon]);
    fprintf(palette_load_c, "\tpalette[BLUE_WINDOW_PALETTE_OFF + window_normal_text] = %02x;\n", palette[BLUE_WINDOW_PALETTE_OFF + window_normal_text]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_cyan_window_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_frame_passive] = %02x;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_frame_passive]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_frame_active] = %02x;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_frame_active]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_frame_icon] = %02x;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_frame_icon]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_page] = %02x;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_icon] = %02x;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_scroll_bar_icon]);
    fprintf(palette_load_c, "\tpalette[CYAN_WINDOW_PALETTE_OFF + window_normal_text] = %02x;\n", palette[CYAN_WINDOW_PALETTE_OFF + window_normal_text]);
    fprintf(palette_load_c, "}\n\n");
    

    fprintf(palette_load_c, "void build_gray_window_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_frame_passive] = %02x;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_frame_passive]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_frame_active] = %02x;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_frame_active]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_frame_icon] = %02x;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_frame_icon]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_page] = %02x;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_icon] = %02x;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_scroll_bar_icon]);
    fprintf(palette_load_c, "\tpalette[GRAY_WINDOW_PALETTE_OFF + window_normal_text] = %02x;\n", palette[GRAY_WINDOW_PALETTE_OFF + window_normal_text]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_blue_dialog_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_background] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_background]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_icon] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_frame_icon]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_page] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_static_text] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_static_text]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_label] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_label]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_label] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_label]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_label] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_label]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_button] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_default_button] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_default_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_button] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_button] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_button] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_button_shadow] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_button_shadow]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_cluster] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_cluster]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_cluster] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_cluster]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_cluster] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_shortcut_cluster]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_input] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_input]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_input] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_input]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_input_arrow] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_input_arrow]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_button] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_button]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_sides] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_sides]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_barpage] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_barpage]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_history_bar_icon] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_history_bar_icon]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_list] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_normal_list]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_list] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_selected_list]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_focused_list] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_focused_list]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_list_divider] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_list_divider]);

    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_info_pane] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_info_pane]);
    fprintf(palette_load_c, "\tpalette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_cluster] = %02x;\n", palette[BLUE_DIALOG_PALETTE_OFF + dialog_disabled_cluster]);
    fprintf(palette_load_c, "}\n\n");
    

    fprintf(palette_load_c, "void build_cyan_dialog_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_background] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_background]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_icon] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_frame_icon]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_page] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_static_text] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_static_text]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_label] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_label]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_label] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_label]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_label] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_label]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_button] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_default_button] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_default_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_button] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_button] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_button] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_button_shadow] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_button_shadow]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_cluster] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_cluster]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_cluster] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_cluster]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_cluster] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_shortcut_cluster]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_input] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_input]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_input] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_input]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_input_arrow] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_input_arrow]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_button] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_button]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_sides] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_sides]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_barpage] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_barpage]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_history_bar_icon] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_history_bar_icon]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_list] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_normal_list]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_list] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_selected_list]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_focused_list] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_focused_list]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_list_divider] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_list_divider]);

    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_info_pane] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_info_pane]);
    fprintf(palette_load_c, "\tpalette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_cluster] = %02x;\n", palette[CYAN_DIALOG_PALETTE_OFF + dialog_disabled_cluster]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_gray_dialog_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_background] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_background]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_icon] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_frame_icon]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_page] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_static_text] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_static_text]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_label] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_label]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_label] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_label]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_label] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_label]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_button] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_default_button] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_default_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_button] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_button] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_button] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_button_shadow] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_button_shadow]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_cluster] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_cluster]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_cluster] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_cluster]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_cluster] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_shortcut_cluster]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_input] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_input]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_input] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_input]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_input_arrow] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_input_arrow]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_button] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_button]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_sides] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_sides]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_barpage] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_barpage]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_history_bar_icon] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_history_bar_icon]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_list] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_normal_list]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_list] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_selected_list]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_focused_list] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_focused_list]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_list_divider] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_list_divider]);

    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_info_pane] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_info_pane]);
    fprintf(palette_load_c, "\tpalette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_cluster] = %02x;\n", palette[GRAY_DIALOG_PALETTE_OFF + dialog_disabled_cluster]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_menu_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[menu_normal] = %02x;\n", palette[menu_normal]);
    fprintf(palette_load_c, "\tpalette[menu_disabled] = %02x;\n", palette[menu_disabled]);
    fprintf(palette_load_c, "\tpalette[menu_shortcut] = %02x;\n", palette[menu_shortcut]);
    fprintf(palette_load_c, "\tpalette[menu_selected] = %02x;\n", palette[menu_selected]);
    fprintf(palette_load_c, "\tpalette[menu_select_disabled] = %02x;\n", palette[menu_select_disabled]);
    fprintf(palette_load_c, "\tpalette[menu_shortcut_selected] = %02x;\n", palette[menu_shortcut_selected]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_desktop_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[desktop_color] = %02x;\n", palette[desktop_color]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_browser_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[browser_frame_passive] = %02x;\n", palette[browser_frame_passive]);
    fprintf(palette_load_c, "\tpalette[browser_frame_active] = %02x;\n", palette[browser_frame_active]);
    fprintf(palette_load_c, "\tpalette[browser_frame_icon] = %02x;\n", palette[browser_frame_icon]);
    fprintf(palette_load_c, "\tpalette[browser_scroll_bar_page] = %02x;\n", palette[browser_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[browser_scroll_bar_icons] = %02x;\n", palette[browser_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[browser_normal_text] = %02x;\n", palette[browser_normal_text]);
    fprintf(palette_load_c, "\tpalette[browser_selected_text] = %02x;\n", palette[browser_selected_text]);
    fprintf(palette_load_c, "\tpalette[browser_active_item] = %02x;\n", palette[browser_active_item]);
    fprintf(palette_load_c, "\tpalette[browser_inactive_item] = %02x;\n", palette[browser_inactive_item]);
    fprintf(palette_load_c, "\tpalette[browser_focused_item] = %02x;\n", palette[browser_focused_item]);
    fprintf(palette_load_c, "\tpalette[browser_selected_item] = %02x;\n", palette[browser_selected_item]);
    fprintf(palette_load_c, "\tpalette[browser_divider] = %02x;\n", palette[browser_divider]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_clock_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[clock_clockview] = %02x;\n", palette[clock_clockview]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_editor_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[editor_frame_passive] = %02x;\n", palette[editor_frame_passive]);
    fprintf(palette_load_c, "\tpalette[editor_frame_active] = %02x;\n", palette[editor_frame_active]);
    fprintf(palette_load_c, "\tpalette[editor_frame_icon] = %02x;\n", palette[editor_frame_icon]);
    fprintf(palette_load_c, "\tpalette[editor_scroll_bar_page] = %02x;\n", palette[editor_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[editor_scroll_bar_icons] = %02x;\n", palette[editor_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[editor_normal_text] = %02x;\n", palette[editor_normal_text]);
    fprintf(palette_load_c, "\tpalette[editor_selected_text] = %02x;\n", palette[editor_selected_text]);
    fprintf(palette_load_c, "\tpalette[editor_highlight_column] = %02x;\n", palette[editor_highlight_column]);
    fprintf(palette_load_c, "\tpalette[editor_highlight_row] = %02x;\n", palette[editor_highlight_row]);
    fprintf(palette_load_c, "\tpalette[editor_error_messages] = %02x;\n", palette[editor_error_messages]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_help_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[help_frame_passive] = %02x;\n", palette[help_frame_passive]);
    fprintf(palette_load_c, "\tpalette[help_frame_active] = %02x;\n", palette[help_frame_active]);
    fprintf(palette_load_c, "\tpalette[help_frame_icon] = %02x;\n", palette[help_frame_icon]);
    fprintf(palette_load_c, "\tpalette[help_scroll_bar_page] = %02x;\n", palette[help_scroll_bar_page]);
    fprintf(palette_load_c, "\tpalette[help_scroll_bar_icons] = %02x;\n", palette[help_scroll_bar_icons]);
    fprintf(palette_load_c, "\tpalette[help_help_text] = %02x;\n", palette[help_help_text]);
    fprintf(palette_load_c, "\tpalette[help_help_links] = %02x;\n", palette[help_help_links]);
    fprintf(palette_load_c, "\tpalette[help_selected_link] = %02x;\n", palette[help_selected_link]);
    fprintf(palette_load_c, "\tpalette[help_selected_text] = %02x;\n", palette[help_selected_text]);
    fprintf(palette_load_c, "\tpalette[help_html_heading1] = %02x;\n", palette[help_html_heading1]);
    fprintf(palette_load_c, "\tpalette[help_html_heading2] = %02x;\n", palette[help_html_heading2]);
    fprintf(palette_load_c, "\tpalette[help_html_heading3] = %02x;\n", palette[help_html_heading3]);
    fprintf(palette_load_c, "\tpalette[help_html_heading4] = %02x;\n", palette[help_html_heading4]);
    fprintf(palette_load_c, "\tpalette[help_html_heading5] = %02x;\n", palette[help_html_heading5]);
    fprintf(palette_load_c, "\tpalette[help_html_heading6] = %02x;\n", palette[help_html_heading6]);
    fprintf(palette_load_c, "}\n\n");


    fprintf(palette_load_c, "void build_syntax_palette(palette_entry_t *palette) {\n");
    fprintf(palette_load_c, "\tpalette[syntax_whitespace] = %02x;\n", palette[syntax_whitespace]);
    fprintf(palette_load_c, "\tpalette[syntax_comments] = %02x;\n", palette[syntax_comments]);
    fprintf(palette_load_c, "\tpalette[syntax_reserved_words] = %02x;\n", palette[syntax_reserved_words]);
    fprintf(palette_load_c, "\tpalette[syntax_identifiers] = %02x;\n", palette[syntax_identifiers]);
    fprintf(palette_load_c, "\tpalette[syntax_strings] = %02x;\n", palette[syntax_strings]);
    fprintf(palette_load_c, "\tpalette[syntax_numbers] = %02x;\n", palette[syntax_numbers]);
    fprintf(palette_load_c, "\tpalette[syntax_hex_numbers] = %02x;\n", palette[syntax_hex_numbers]);
    fprintf(palette_load_c, "\tpalette[syntax_assembler] = %02x;\n", palette[syntax_assembler]);
    fprintf(palette_load_c, "\tpalette[syntax_symbols] = %02x;\n", palette[syntax_symbols]);
    fprintf(palette_load_c, "\tpalette[syntax_directives] = %02x;\n", palette[syntax_directives]);
    fprintf(palette_load_c, "\tpalette[syntax_tabs] = %02x;\n", palette[syntax_tabs]);
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