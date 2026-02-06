# Theming for the FP Pascal IDE

The FP Pascal IDE has the functionality for theming, however it is not officially documented as far
as I can tell.

Yes, I recognize that it's ironic that I wrote this in C.

## How Themes Work

Themes are loaded from your `fp.ini` file from the following lines:

```ini
[Colors]
Palette_1_40=<byte> * 40
Palette_41_80=<byte> * 40
Palette_81_120=<byte> * 40
Palette_121_160=<byte> * 40
Palette_161_200=<byte> * 40
Palette_201_240=<byte> * 40
```

where `<byte>` is either `#` followed by a decimal value ranging from 0-255,
or `#$` followed by a hexadecimal value of the same range.

Example: `#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00#$00`

The values from this correspond to your terminal's 16-color palette, with the first 4 bits representing the highlight and the next 4 bits representing the text color.

The "Palette" contains many sub-palettes, described in `palette_info.h`. Each enum and field within
each enum has a name taken from the FPC source code.

## Pre-Made Themes

The `themes/` folder contains some pre-made themes.

`bunnyworks.fp.ini` comes from [here](https://mooncore.eu/bunny/txt/fpidecol.htm)

`cyberfilth.fp.ini` comes from [here](https://github.com/cyberfilth/FP-IDE-theme/tree/main)

Both of the above links document some of the color coding with more detail than the enum names in this repo.

## Editing Themes

To edit a theme, first run

`make palette_read`

Then, run `./palette_read <theme>` with the theme you want to edit.

After this, you can edit the newly generated `palette_load.c` file however you wish.

Once you're done making changes, run `make palette_gen` and run `./palette_gen`.
This will output a new `[Colors]` section to `stdout`, which you can paste in your `fp.ini` file.

## Source Code References

Function to read palette: [strtopalette](https://gitlab.com/freepascal.org/fpc/source/-/blob/92ebf40f04c5b9b6b41ffd153d553c0a082c5c97/packages/ide/fpini.pas#L278)

Files that define sub-palettes: [fpmopts.inc](https://gitlab.com/freepascal.org/fpc/source/-/blob/main/packages/ide/fpmopts.inc),
[colorsel.inc](https://gitlab.com/freepascal.org/fpc/source/-/blob/main/packages/fv/src/colorsel.inc)

