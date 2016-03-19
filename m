#!/bin/bash
clear
clang -std=c99 -Wall -g -o bin/$2 src/$1/$2.c && splint -compdef +quiet +skip-sys-headers +charintliteral +charint -shadow src/$1/$2.c
