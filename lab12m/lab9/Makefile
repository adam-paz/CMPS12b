# $Id: Makefile,v 1.14 2015-01-30 16:44:06-08 - - $

GCC = gcc -g -O0 -Wall -Wextra -std=gnu11

CSOURCES = inssort.c numsort.c linesort.c
CHEADER = inssort.h
SOURCES  = ${CHEADER} ${CSOURCES} Makefile
EXECBINS = numsort linesort
LISTING  = Listing.ps
SUBMIT   = submit cmps012b-wm.w15 lab9

all : numsort linesort

numsort: numsort.o inssort.o
	${GCC} numsort.o inssort.o -o numsort

linesort: linesort.o inssort.o
	${GCC} linesort.o inssort.o -o linesort


%.o : %.c
	${GCC}  -c $<

ci :
	cid + ${SOURCES}
	- checksource $<

clean :
	- rm -vf core

spotless : clean
	- rm -vf ${EXECBINS}

lis : ${CSOURCES} Makefile
	mkpspdf ${LISTING} ${SOURCES}

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis

