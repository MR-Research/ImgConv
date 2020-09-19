# Imgconv

Image convolution tool written in C

## Features

 - Wide image format compatibility.
 - Arbitrary image and filter size.
 - Low computational complexity.
 - Grayscale conversion.
 - No external dependencies.

## Installation

 - Clone the repository.
```bash
git clone https://github.com/MrRobot-oss/ImgConv.git
```
 - (Optional) open the project file in KDevelop using the .kdev4 file
 - Compile using math library tag.
```bash
gcc main.c -o imgconv -lm
```
 - Copy the binary to your standard binary path.

## Usage

```bash
imgconv source filter res filtersize
```
## Parameters

 1. source: The source image, supported formats are the same as stb image (JPG, PNG, TGA, BMP, PSD, GIF, HDR, PIC).
 2. filter: Filter file path, should be a plain text file, where each element is separated by a space, and each row is separated by newline (\n).
 3. res:  Output image file path, the image should be in jpg format.
 4. filtersize: Size of the filter, should be an odd number.

## Limitations
The following are the current limitations of the program:
 - The program by default crops the resulting image, to account for the data loss due to the convolution process.
 - Grayscale conversion is performed by default.
 - Supported color channels is 3.
 - Output image is jpg.
 - Only odd number square filters are supported at the moment.

## Known issues
No known issues have been reported so far. If you encounter an issue, please post a new issue so it can be verified and fixed.

## TODO

 - Support more output image formats.
 - Add support for arbitrary number of channels.
 - Make grayscale conversion optional.
 - File sanitization and memory management improvements.
 - Support for UNIX-style argument parsing.
 - Support for standard input/output.
 - Bindings to other programming languages.
 - Make binary/release version available.
 - Makefile script for easier compilation/installation.

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
This program is distributed under the MIT license, you can read more about it here: [MIT](https://choosealicense.com/licenses/mit/).
The [stb libraries](https://github.com/nothings/stb), developed by [nothings](https://github.com/nothings)  are based on public domain code (licensed under the MIT license).
