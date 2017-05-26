@echo off
REM Can put an absolute path to str8rzr here. or you can set your $PATH environmental variable to include the path of str8rzr
SET straitrazor="str8rzr"
SET numcores=4
SET config="Forenseq.config"

for %%f in (*.fastq) do (
  
REM make directories iff necessary
  if NOT EXIST %%~nf mkdir %%~nf\R1

  %straitrazor% -c %config% -p %numcores%  %%f > %%~nf"\R1\allsequences.txt"

)

SETLOCAL ENABLEDELAYEDEXPANSION
for /r %%f in (*fastq.gz) do (
	set var=%%~nf
	set bn=!var:~0,-6!
	mkdir !bn!\R1 2> NUL
	zcat %%f | %straitrazor% -c %config% -p %numcores% > !bn!"\R1\allsequences.txt"
)

