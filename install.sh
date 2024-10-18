#!/bin/bash

# Create lib directory
mkdir -p NHF_Farm/lib/SDL2
mkdir -p NHF_Farm/lib/SDL2_image

# Download SDL2
curl -L -o SDL2.zip https://www.libsdl.org/release/SDL2-2.28.4.zip
unzip -q SDL2.zip -d NHF_Farm/lib/SDL2
rm SDL2.zip

# Download SDL2_image
curl -L -o SDL2_image.zip https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.6.3.zip
unzip -q SDL2_image.zip -d NHF_Farm/lib/SDL2_image
rm SDL2_image.zip

echo "SDL2 és SDL2_image sikeresen telepítve!"
