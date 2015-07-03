# TILE2EE

This tool allows you to convert MOS and TIS files, provided by Infinity Engine games such as Baldur's Gate and Icewind Dale, from the palette-based format (V1) into the pvrz-based format (V2) as used by the Enhanced Editions of the games, and vice versa.

**Supported conversions:**
* MOS V1 files will be automatically converted into MOS V2.
* MOS V2 files will be automatically converted into MOS V1.
* TIS V1 files will be automatically converted into TIS V2.
* TIS V2 files will be automatically converted into TIS V1.


### USAGE
```
Usage: tile2ee [options] infile [infile2 [...]]

Options:
  -e            Do not halt on errors.
  -s            Be silent.
  -d searchdir  Look for referenced PVRZ files in this directory.
                You can specify this option multiple times to add more
                search directories. (Default: Same directory as input file)
  -o output     Select output file or folder. 
                (Default: Outputs files into same folder as input files and 
                          adds suffix "-0", "-1", ..., if file exists.)
                (Note: Output file works only with single input file.)
  -i index      (MOS only) Start index for PVRZ files. (Default: 1000)
                (Note: Existing PVRZ files will be detected and skipped
                       unless option -w has been specified.)
  -f type       Force type of file conversion. Skips files already matching 
                the desired file format.
                Supported values:
                    0: Auto-convert files (default)
                    1: Convert to palette-based MOS/TIS only.
                    2: Convert to pvrz-based MOS/TIS only.
  -w            (MOS only) Force overwriting of existing PVRZ files.
  -z            (MOS only) Create compressed MOS V1 files (MOSC).
  -j num        Number of parallel threads to speed up the conversion process.
                Valid numbers: 0 (autodetect), 1..256 (Default: 0)
  -q V1[V2]     Set quality levels for encoding V1 and, optionally, V2 files.
                Use '-' as placeholder for default levels.
                Example 1: -q 27 (level 2 for V1 and level 7 for V2)
                Example 2: -q -7 (default level for V1 and level 7 for V2)
                Example 3: -q 2  (level 2 for V1 and default level for V2)
                When creating palette-based MOS/TIS V1 files (Default: 4):
                    Dithering:               levels 5 to 9
                    Posterization:           levels 0 to 2
                    Additional techniques:   levels 4 to 9
                When creating PVRZ-based MOS/TIS V2 files (Default: 9):
                    Iterative cluster fit:   levels 7 to 9
                    Single cluster fit:      levels 3 to 6
                    Range fit:               levels 0 to 2
                    Weight color by alpha:   levels 5 to 9
  -T            (TIS only) Treat unrecognized input files as headerless TIS.
  -I            Show file information and exit.
  -V            Print version number and exit.

Supported input file types: MOS V1, MOS V2, TIS V1, TIS V2.
Note: You can mix and match input files of each supported type.
```


### LICENSE

tile2ee is distributed under the terms and conditions of the MIT license. This license is specified at the top of each source file and must be preserved in its entirety.


### BUILDING TILE2EE
**Dependencies:**
- zlib (http://www.zlib.net/)
- pngquant (https://github.com/pornel/pngquant/)
- libsquish (https://code.google.com/p/libsquish/)

External libraries and include files are assumed to be located in the subfolders "zlib", "squish" and "pngquant". The libraries are providing their own instructions how to compile them. Afterwards call "make" to build tile2ee. **Note:** You'll need a compiler that supports the C++11 standard.

If you want to change paths for the external libraries or include files, you can do so by modifying the file "config.mk" by hand.
