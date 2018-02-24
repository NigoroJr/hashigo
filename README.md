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

In order to use this program, you will need to:

1. have access to an Rockwell's RSLogix5000 IDE to generate an L5X file
2. write the part that transforms your Ladder Logic to a `hshg` file

Academic paper can be found
[here](http://www.users.miamioh.edu/jamiespa/html_papers/escs_17.pdf).

## Build and Run

Ubuntu 16.04 is the recommenned environment to run this program. Development
was also done on macOS.

### Requirements
- C++ compiler that supports C++11
- CMake 2.8 or above
- pugixml
- bison
- flex

### Running

```
Usage:
  hashigo <L5X file> <template directory>
```

```console
$ sudo apt-get install bison flex libpugixml-dev
$ git clone https://github.com/NigoroJr/hashigo
$ cd hashigo/build
$ cmake ..
$ make
$ ./src/hashigo ../samples/CarWash.L5X ../templates/
```

## Credits
- All the packages that this program depends on
- https://github.com/imageworks/OpenShadingLanguage
  - CMake module for pugixml

## Authors
Naoki Mizuno
