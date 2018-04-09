# Data structures

This repository contains some data structures which I use when coding in C.  
See `.h` files for interface details.

### Buflist

A list of buffers which is useful when e.g. handling network data transfer when payload is parted.

### Array

At this stage only generic array searcher is implemented.

### Doubly linked list

Generic implementation of doubly linked list.

## Running tests

If you would like to run tests then firstly clone this repository with `--recurse-submodules` flag.

Then:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make run-test
```

The tests use [mortie/snow](https://github.com/mortie/snow) test framework.

