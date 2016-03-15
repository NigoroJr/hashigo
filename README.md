<div align="center">
  <img width=650px src="https://raw.githubusercontent.com/NigoroJr/hashigo/master/misc/logo.png" />
</div>

[![Build Status](https://travis-ci.org/NigoroJr/hashigo.svg)](https://travis-ci.org/NigoroJr/hashigo)

A compiler to translate Ladder Logic to Verilog HDL.

## Description
TODO

## Installing
### Requirements
- C++ compiler that supports C++11
- CMake 2.8 or above
- pugixml
- bison
- flex

### Testing
- Boost.Test

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
