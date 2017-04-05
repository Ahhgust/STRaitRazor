

@echo off
REM Can put an absolute path to str8razor here. or you can set your $PATH environmental variable to include the path of str8
SET straitrazor="str8"
SET numcores=4
SET config="newconfig"

for %%f in (*.fastq) do (
  SET basename=%%~nf
  
REM make directories iff necessary
  if NOT EXIST %~dp0\%basename% mkdir %basename%\R1

@echo on
  %straitrazor% -c %config% -p %numcores%  %%f > %basename%"\R1\allsequences.txt"
@echo off

)




