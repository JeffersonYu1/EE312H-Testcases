#!/bin/bash

# Fix line endings for patch
dos2unix *.cpp

# Patch main.cpp
patch -i fix.patch

# Build program
make clean all

