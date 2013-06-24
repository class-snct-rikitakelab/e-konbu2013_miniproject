
echo off 

del /Q *.rxe 
make clean

IF EXIST *.rxe sh rxeflash.sh