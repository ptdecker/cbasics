#!/bin/bash
gcc -o bin/$2 src/$1/$2.c && splint -compdef +quiet +skip-sys-headers src/$1/$2.c
