#!/bin/bash

# Create lib directory
mkdir -p lib/SDL2
mkdir -p lib/SDL2_image

# Download SDL2
curl -L -o SDL2.zip https://www.libsdl.org/release/SDL2-2.28.4.zip
mkdir -p lib/temp
unzip -q SDL2.zip -d lib/temp -vvv
mv lib/temp/SDL2-2.28.4/* lib/SDL2
rmdir lib/temp/SDL2-2.28.4
rm SDL2.zip

# Download SDL2_image
curl -L -o SDL2_image.zip https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.6.3.zip
unzip -q SDL2_image.zip -d lib/temp
mv lib/temp/SDL2_image-2.6.3/* lib/SDL2_image
rmdir lib/temp/SDL2_image-2.6.3
rmdir temp
rm SDL2_image.zip

echo "SDL2 és SDL2_image sikeresen telepítve!"
