# Control of mesh resolution

## Overview

The project implements algorythm for control mesh rezolution in .off files.

## Progect using

* Run `make` to launch the project

## Progect structure

* **meta.h**    - basic structures that used in project;
* **getdat.h**  - reading data;
* **putdat.h**  - writing data;
* **evlib.h**   - some functions for vertices and edges;
* **cmrlib.h**  - here you can find functions that correct mesh resolution;

## Settings:

To choose resolution or deviation of output models, change this defines in [meta.h](https://github.com/vakulin95/Control-of-mesh-resolution/blob/master/meta.h):

```C
#define DEF_DES_RESOL           0.0475
#define DEF_DEVIATION           0.085
#define DEF_DES_RESOL_2         0.2
```

## Info

The description of the implemented algorithm can be found [here](https://github.com/vakulin95/Control-of-mesh-resolution/tree/master/data/article.pdf).
