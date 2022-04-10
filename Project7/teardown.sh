#!/bin/bash

# Patch main.cpp
patch -R main.cpp < fix.patch

# Clean up program
make clean
