

@echo off
REM Can put an absolute path to cstr8 here. or you can set your $PATH environmental variable to include the path of str8
SET straitrazor="cstr8"
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

for %%f in (*.gz) do (
  SET basename=%%~nf
  
REM make directories iff necessary
  if NOT EXIST %~dp0\%basename% mkdir %basename%\R1

@echo on
  zcat %%f | %straitrazor% -c %config% -p %numcores% > %basename%"\R1\allsequences.txt"
@echo off

)




