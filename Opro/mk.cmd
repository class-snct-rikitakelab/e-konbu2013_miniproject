
echo off 
//set path = c:\cygwin\bin\
del /Q *.rxe 
 
make all 

IF EXIST *.rxe sh rxeflash.sh

