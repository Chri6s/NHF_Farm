#!/bin/bash

# Create lib directory
mkdir -p lib/SDL2
mkdir -p lib/SDL2_image

# Download SDL2
curl -L -o SDL2.zip https://github.com/libsdl-org/SDL/releases/download/release-2.30.8/SDL2-devel-2.30.8-VC.zip
mkdir -p lib/temp
unzip -q SDL2.zip -d lib/temp
mv lib/temp/SDL2-2.30.8/* lib/SDL2
rm SDL2.zip

# Download SDL2_image
curl -L -o SDL2_image.zip https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip
unzip -q SDL2_image.zip -d lib/temp
mv lib/temp/SDL2_image-2.8.2/* lib/SDL2_image
rmdir lib/temp/SDL2_image-2.8.2
rm SDL2_image.zip

# Download SDL2_ttf
curl -L -o SDL2_ttf.zip https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-VC.zip
unzip -q SDL2_ttf.zip -d lib/temp
mv lib/temp/SDL2_ttf-2.22.0/* lib/SDL2_ttf
rmdir lib/temp/SDL2_ttf-2.22.0
rmdir temp
rm SDL2_ttf.zip

echo "SDL2 és SDL2_image sikeresen telepítve!"
