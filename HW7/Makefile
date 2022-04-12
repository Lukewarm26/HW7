# Makefile
# Lucas Eifert
# COSC 3750 Spring 22
# Homework 7
# Modified 04/10/2022
#
# Makefile to compile wytalk program
CC=gcc
CFLAGS=-Wall -ggdb
RM=/bin/rm -f

wytalkC: wytalkC.c
	${CC} ${CFLAGS} wytalkC.c socketfun.c -o wytalkC

wytalkD: wytalkD.c
	${CC} ${CFLAGS} test.c socketfun.c -o wytalkD