#!/bin/bash
g++ Main.cpp Image.cpp `pkg-config --cflags --libs opencv` -lwiringPi

