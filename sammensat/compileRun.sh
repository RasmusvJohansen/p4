#!/bin/bash
g++ Main.cpp Image.cpp -o a.out `pkg-config --cflags --libs opencv` -lwiringPi
./a.out

