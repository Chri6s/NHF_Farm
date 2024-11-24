@echo off

REM Create lib directory
mkdir lib\SDL2
mkdir lib\SDL2_image
mkdir lib\SDL2_ttf
mkdir lib\temp

REM Download SDL2
powershell -Command "Invoke-WebRequest -Uri https://github.com/libsdl-org/SDL/releases/download/release-2.30.8/SDL2-devel-2.30.8-VC.zip -OutFile SDL2.zip"
powershell -Command "Expand-Archive -Path SDL2.zip -DestinationPath lib\temp"
xcopy /E /I lib\temp\SDL2-2.30.8\* lib\SDL2
del SDL2.zip

REM Download SDL2_image
powershell -Command "Invoke-WebRequest -Uri https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip -OutFile SDL2_image.zip"
powershell -Command "Expand-Archive -Path SDL2_image.zip -DestinationPath lib\temp"
xcopy /E /I lib\temp\SDL2_image-2.8.2\* lib\SDL2_image
rmdir /S /Q lib\temp\SDL2_image-2.8.2
del SDL2_image.zip

REM Download SDL2_ttf
powershell -Command "Invoke-WebRequest -Uri https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-VC.zip -OutFile SDL2_ttf.zip"
powershell -Command "Expand-Archive -Path SDL2_ttf.zip -DestinationPath lib\temp"
xcopy /E /I lib\temp\SDL2_ttf-2.22.0\* lib\SDL2_ttf
rmdir /S /Q lib\temp\SDL2_ttf-2.22.0

REM Clean up
rmdir /S /Q lib\temp
del SDL2_ttf.zip

echo SDL2, SDL2_image, and SDL2_ttf successfully installed!
