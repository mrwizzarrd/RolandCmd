@echo off
REM ---Clean Old Build---
if exist RolandCmd.exe del RolandCmd.exe
cd src
if exist main.o del main.o
if exist parser.o del parser.o
if exist util.o del util.o
if exist usr.o del usr.o
if exist error.o del error.o
if exist command.o del command.o
if exist history.o del history.o
if exist file.o del file.o

REM --Compile New Build into Object Files---
gcc -I..\include -c main.c -o main.o
gcc -I..\include -c util.c -o util.o
gcc -I..\include -c parser.c -o parser.o
gcc -I..\include -c usr.c -o usr.o
gcc -I..\include -c command.c -o command.o
gcc -I..\include -c error.c -o error.o
gcc -I..\include -c history.c -o history.o
gcc -I..\include -c file.c -o file.o

REM --Compile Object Files into Executable--
gcc main.o util.o parser.o usr.o command.o error.o history.o -o ..\RolandCmd.exe

REM ---Clean Up Object Files---
del main.o
del parser.o
del util.o
del usr.o
del error.o
del command.o
del history.o
del file.o
cd ..

echo Build Complete