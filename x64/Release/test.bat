REM
radix.exe
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 2 10
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 2 10
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe A 10 16
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 A 10
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 10 B
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 37 10
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 1 10
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 2 -2 10
IF NOT ERRORLEVEL 1 GOTO err

REM
radix.exe 0 10 2 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /b output.txt toutputs/toutput.txt
IF ERRORLEVEL 1 GOTO err

REM
radix.exe -21474836472123 10 2 > output.txt
IF ERRORLEVEL 1 GOTO err
FC /b output.txt toutputs/toutput1.txt
IF ERRORLEVEL 1 GOTO err

ECHO Program testing succeeded :-) 
EXIT
  
:err
ECHO Program testing failed :-( 
EXIT