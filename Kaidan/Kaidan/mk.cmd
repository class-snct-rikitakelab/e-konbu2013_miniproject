
echo off 
//set path = c:\cygwin\bin\
del /Q *.rxe 

//make clean 
make clean all 

IF EXIST *.rxe sh rxeflash.sh