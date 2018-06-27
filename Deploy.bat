set FolderName=%time::=.%
set FolderName=%FolderName: =0%
set FolderName=%FolderName:~0,-5%
set FolderName=SquareTapper_%date:/=%_%FolderName%

mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%
xcopy /s .\proj.visualstudio\Cocos2d\ARM\Release\CocosVisualStudio.apk C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%

mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC
xcopy /s .\proj.win32\Release.win32\*.dll C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC
xcopy /s .\proj.win32\Release.win32\SquareTapper.exe C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC

mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\img
xcopy /s .\proj.win32\Release.win32\img C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\img
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\fonts
xcopy /s .\proj.win32\Release.win32\fonts C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\fonts
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\lvls
xcopy /s .\proj.win32\Release.win32\lvls C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\lvls
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\lvls_demo
xcopy /s .\proj.win32\Release.win32\lvls_demo C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\lvls_demo
mkdir C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\gui
xcopy /s .\proj.win32\Release.win32\gui C:\Users\Cerberus\Dropbox\SquareTapper\%FolderName%\BuildPC\gui