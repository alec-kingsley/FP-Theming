# Theming for the FP Pascal IDE

The FP Pascal IDE has the functionality for theming, however it is undocumented so far as I can tell.

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

The "Palette" contains many sub-palettes, described in `palette_info.h`.

## Pre-Made Themes

The `themes/` folder contains some pre-made themes.

`bunnyworks.fp.ini` comes from [here](https://mooncore.eu/bunny/txt/fpidecol.htm)

`cyberfilth.fp.ini` comes from [here](https://github.com/cyberfilth/FP-IDE-theme/tree/main)

## Source Code References

Function to read palette: [strtopalette](https://gitlab.com/freepascal.org/fpc/source/-/blob/92ebf40f04c5b9b6b41ffd153d553c0a082c5c97/packages/ide/fpini.pas#L278)

Files that define sub-palettes: [fpmopts.inc](https://gitlab.com/freepascal.org/fpc/source/-/blob/main/packages/ide/fpmopts.inc),
[colorsel.inc](https://gitlab.com/freepascal.org/fpc/source/-/blob/main/packages/fv/src/colorsel.inc)

