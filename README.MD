# Control of mesh resolution

## Overview

The project implements algorythm for control mesh rezolution in .off files. It was developed to correct resolution in [Princeton Shape Benchmark](http://shape.cs.princeton.edu/benchmark/) as a part of my university graduation work.


This program can work in two different modes:
1. Correct resolution for one file - Data located in [input](https://github.com/vakulin95/Control-of-mesh-resolution/tree/master/data/input) and [output](https://github.com/vakulin95/Control-of-mesh-resolution/tree/master/data/output) folders.
2. Create new database whith corrected mesh resolution from [Princeton Shape Benchmark](http://shape.cs.princeton.edu/benchmark/).

## Project using

* Run `make` to built and make new data base with corrected resolution;
* Run `make one` to built and try algorythm on one file;
* Run `make built` to just built project;
* Run `make_one` to launch program to try algorythm for one file;
* Run `make_base` to launch program and make data base with corrected resolution;

## Progect structure

* [**meta.h**](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/meta.h)    - basic structures that used in project;
* [**getdat.h**](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/getdat.h)  - reading data;
* [**putdat.h**](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/putdat.h)  - writing data;
* [**evlib.h**](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/evlib.h)   - some functions for vertices and edges;
* [**cmrlib.h**](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/cmrlib.h)  - here you can find functions that correct mesh resolution;

## Settings

### Resolution or deviation:

[meta.h](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/meta.h):
```C
#define DEF_DES_RESOL           0.0475
#define DEF_DEVIATION           0.085
#define DEF_DES_RESOL_2         0.2
```

### Path for input and output files:

[meta.h](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/meta.h):
```C
#define IN_DATA                 "data/input/m1300.off"
#define DEF_IN_PATH             "/Princeton/Shape/Benchmark/db/"
#define DEF_OUT_PATH            "/output/database/"
```
Use define `IN_DATA` to choose file in [data/input](https://github.com/vakulin95/Control-of-mesh-resolution/tree/master/data/input) folder when you start program for one file.

## Info

The description of the implemented algorithm can be found [here](https://github.com/vakulin95/Control-of-mesh-resolution/tree/master/data/article.pdf). Also when program works in database mode, in the output folder located #info.dat file. You can find program result in this file.
