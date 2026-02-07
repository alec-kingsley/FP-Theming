#include "palette_info.h"
#include "palette_load.h"
#include <stdint.h>
#include <stdio.h>

void output_palette(palette_entry_t *palette) {
    size_t i;
    printf("[Colors]");

    for (i = 0; i < PALETTE_SIZE; i++) {
        if (i % PALETTE_ENTRIES_PER_LINE == 0) {
            printf("\nPalette_%lu_%lu=", i + 1, i + PALETTE_ENTRIES_PER_LINE);
        }
        printf("#$%02x", palette[i]);
    }
    printf("\n");
}

int main(void) {
    palette_entry_t palette[PALETTE_SIZE];
    size_t i;

    /* write palette */
    for (i = 0; i < PALETTE_SIZE; i++) {
        palette[i] = 0;
    }

    /* create palette */
    build_blue_window_palette(palette);
    build_cyan_window_palette(palette);
    build_gray_window_palette(palette);

    build_blue_dialog_palette(palette);
    build_gray_dialog_palette(palette);
    build_cyan_dialog_palette(palette);

    build_menu_palette(palette);

    build_desktop_palette(palette);

    build_browser_palette(palette);

    build_clock_palette(palette);

    build_editor_palette(palette);

    build_help_palette(palette);

    build_syntax_palette(palette);

    output_palette(palette);

    return 0;
}