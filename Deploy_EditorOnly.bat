set BUILDDROP=C:\Users\Cerberus\Dropbox\SquareTapper

for /f "tokens=*" %%a in ('dir /A:D /B /O:-D %BUILDDROP%') do set NEWEST=%%a&& goto :next

:next

set NEWESTFULL=%BUILDDROP%\%NEWEST%

xcopy /s /y .\Resources\lvls\SquareTapperEditor.exe %NEWESTFULL%\BuildPC\lvls
