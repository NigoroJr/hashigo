<div align="center">
  <img width=650px src="https://raw.githubusercontent.com/NigoroJr/hashigo/master/misc/logo.png" />
</div>

[![Build Status](https://travis-ci.org/NigoroJr/hashigo.svg)](https://travis-ci.org/NigoroJr/hashigo)

A compiler to translate Ladder Logic to Verilog HDL.

## Description
The objectives of this project is to convert ladder logic to a hardware
description language (HDL) that can be used to program an FPGA. This is a
proof of concept that an FPGA can provide the benefits of relay's parallel
logic alongside the flexibility of reprogramming allowed by the PLC.

## Build and Run
### Requirements
- C++ compiler that supports C++11
- CMake 2.8 or above
- pugixml
- bison
- flex

### Commands

```console
$ git clone https://github.com/NigoroJr/hashigo
$ cd hashigo/build
$ cmake ..
$ make
$ ./src/hashigo <L5X file>
```

## Credits
- All the packages that this program depends on
- https://github.com/imageworks/OpenShadingLanguage
  - CMake module for pugixml

## Authors
Naoki Mizuno
