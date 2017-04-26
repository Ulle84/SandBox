@echo off

astyle.exe --options=AStyleOptions.txt *.cpp *.h *.hpp

set DATEEXE=AStyleGnuDate.exe
for /f "tokens=*" %%I in ('%DATEEXE% +20%%y-%%m-%%d_%%H-%%M-%%S') do @set DateAndTime=%%I

md %DateAndTime%
move *.orig %DateAndTime%