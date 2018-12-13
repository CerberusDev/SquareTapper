set FolderName=%time::=.%
set FolderName=%FolderName: =0%
set FolderName=%FolderName:~0,-5%
set FolderName=SquareTapper_%date:/=%_%FolderName%

mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%
xcopy /s .\proj.android\app\build\outputs\apk\release\SquareTapper-release.apk C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%

mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC
xcopy /s .\proj.win32\Release.win32\*.dll C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC
xcopy /s .\proj.win32\Release.win32\SquareTapper.exe C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC

mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\img
xcopy /s .\Resources\img C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\img
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\fonts
xcopy /s .\Resources\fonts C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\fonts
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\lvls
xcopy /s .\Resources\lvls C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\lvls
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\gui
xcopy /s .\Resources\gui C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\gui