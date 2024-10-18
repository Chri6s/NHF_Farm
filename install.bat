@echo off
setlocal

:: Create lib directory
mkdir NHF_Farm\lib\SDL2
mkdir NHF_Farm\lib\SDL2_image

:: Download SDL2
curl -L -o SDL2.zip https://www.libsdl.org/release/SDL2-devel-2.28.4-VC.zip
tar -xf SDL2.zip --strip-components=1 -C NHF_Farm\lib\SDL2
del SDL2.zip

:: Download SDL2_image
curl -L -o SDL2_image.zip https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.6.3-VC.zip
tar -xf SDL2_image.zip --strip-components=1 -C NHF_Farm\lib\SDL2_image
del SDL2_image.zip

echo SDL2 és SDL2_image sikeresen telepítve.
pause
