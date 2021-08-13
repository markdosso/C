# SENG 440 Embedded Systems: Discrete Cosine Transform Optimization

## Contributors

University of Victoria, Summer 2021

Team 27

Mark Dosso V00891114
markdosso@uvic.ca

Gordon Chiang V00821614
gchiang@uvic.ca

## Background

This repository contains our team's optimized source code to calculate the 2D Discrete Cosine Transformation (DCT) of an image. The code is designed for ARMv7 Processor rev 1 (v7l) and is intended to be compiled with the arm-linux-gcc package version 4.3.2.

The most optimized algorithm implemented is the `NEON` algorithm, which only runs on ARM systems. The `UNROLLED` algorithm is the most optimized algorithm that does not rely on ARMv7's NEON (vector) instructions. Source code and assembly code is available to view for an algorithm that uses a theoretical hardware-suppoted butterfly operation `btrfly` in the `butterfly/` directory. 

Please see the accompanying report and presentation slides for further information.

## Instructions

- To start, clone this repository.

### Compiling

Example: `make arm ALGO=NEON`

- Use `make` to compile the source code for x86 systems. An algorithm `ALGO` must be specified. `dct.exe` will be compiled.
- Use `make arm` to compile the source code for ARM systems. An algorithm `ALGO` must be specified. *Note: a GCC compiler for ARM must be available on the system. `dct.exe` will be compiled.
- Specify the make variable `ALGO` to select from the compilable DCT algorithm implementations: `NAIVE`, `UNOPTIMIZED`, `PIPELINED`, `UNROLLED`, or `NEON`. *Note: `NEON` will only run on ARM systems.

- Run `make testbench` to compile a test bench that tests the `NEON` algorithm's DCT results against the results from the `NAIVE` algorithm. The `NEON` algorithm's results must be within 2 integers of `NAIVE`'s results. `testbench.exe` will be compiled and only runs on ARM systems. No make variables are required.

### Running

Example: `./dct.exe ./test/320x240.png 320 240`
(`./dct.exe <image_file_path> <width of image> <length of image>`)

- To run `dct.exe` or `testbench.exe`, specify the target image's file path that will undergo DCT along with its dimensions in pixels.
- `dct.exe` will output the image after undergoing DCT by 8-by-8 pixel blocks.

- `testbench.exe` will output whether the `NEON` algorithm's results are within 2 integer difference from `NAIVE` algorithm's results for the input image. Example: `./testbench.exe ./test/320x240.png 320 240`

- The input image must be a grayscale image (each pixel is an 8-bit integer) with dimensions evenly divisible by 8.
