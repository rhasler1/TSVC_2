
CC=gcc -std=c99
CXX=g++
FC=gfortran
flags = -O3 -mavx2
vecflags = -W -ftree-vectorizer-verbose=3 -ftree-vectorize -fopt-info-vec-optimized
novecflags =
omp_flags=-fopenmp

ifdef VEC_REPORT
vecflags+=-ftree-vectorizer-verbose=1 -fopt-info-vec=gcc.vect -fopt-info-vec-missed=gcc.miss -fno-inline
endif

ieee_math_flags=
fast_math_flags=-ffast-math

ifdef PRECISE_MATH
$(warning No 'precise' math flags for GNU!)
endif

