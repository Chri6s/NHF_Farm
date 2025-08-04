#!/bin/bash

# Create lib directories
mkdir -p ./lib
mkdir -p ./lib/temp

# Function to check if directory is non-empty
is_non_empty() {
    [ -d "$1" ] && [ "$(ls -A $1)" ]
}

# SDL2
if is_non_empty ./lib/SDL2; then
    read -p "SDL2 already exists. Overwrite? (Y/N): " overwrite_sdl2
else
    overwrite_sdl2="Y"
fi
if [ "$overwrite_sdl2" = "Y" ] || [ "$overwrite_sdl2" = "y" ]; then
    mkdir -p ./lib/SDL2
    curl -L -o SDL2.zip https://github.com/libsdl-org/SDL/releases/download/release-2.30.8/SDL2-devel-2.30.8-VC.zip
    unzip SDL2.zip -d ./lib/temp
    cp -r ./lib/temp/SDL2-2.30.8/* ./lib/SDL2
    rm SDL2.zip
fi

# SDL2_image
if is_non_empty ./lib/SDL2_image; then
    read -p "SDL2_image already exists. Overwrite? (Y/N): " overwrite_sdl2_image
else
    overwrite_sdl2_image="Y"
fi
if [ "$overwrite_sdl2_image" = "Y" ] || [ "$overwrite_sdl2_image" = "y" ]; then
    mkdir -p ./lib/SDL2_image
    curl -L -o SDL2_image.zip https://github.com/libsdl-org/SDL_image/releases/download/release-2.8.2/SDL2_image-devel-2.8.2-VC.zip
    unzip SDL2_image.zip -d ./lib/temp
    cp -r ./lib/temp/SDL2_image-2.8.2/* ./lib/SDL2_image
    rm -rf ./lib/temp/SDL2_image-2.8.2
    rm SDL2_image.zip
fi

# SDL2_ttf
if is_non_empty ./lib/SDL2_ttf; then
    read -p "SDL2_ttf already exists. Overwrite? (Y/N): " overwrite_sdl2_ttf
else
    overwrite_sdl2_ttf="Y"
fi
if [ "$overwrite_sdl2_ttf" = "Y" ] || [ "$overwrite_sdl2_ttf" = "y" ]; then
    mkdir -p ./lib/SDL2_ttf
    curl -L -o SDL2_ttf.zip https://github.com/libsdl-org/SDL_ttf/releases/download/release-2.22.0/SDL2_ttf-devel-2.22.0-VC.zip
    unzip SDL2_ttf.zip -d ./lib/temp
    cp -r ./lib/temp/SDL2_ttf-2.22.0/* ./lib/SDL2_ttf
    rm -rf ./lib/temp/SDL2_ttf-2.22.0
    rm SDL2_ttf.zip
fi

# Clean up
rm -rf ./lib/temp

# Remove all .txt files to reduce bloat (e.g. licenses, readmes)
find ./lib -type f -iname "*.txt" -delete


echo "SDL2, SDL2_image, and SDL2_ttf successfully installed and temp files cleaned!"

read -p "Do you want to generate Doxygen documentation? (Y/N): " gen_doc
if [ "$gen_doc" = "Y" ] || [ "$gen_doc" = "y" ]; then
    if command -v doxygen >/dev/null 2>&1 && command -v dot >/dev/null 2>&1; then
        doxygen Doxyfile
        echo "Doxygen documentation generated."
    else
        echo "Doxygen and/or Graphviz (dot) is not installed. Please install both to generate documentation."
        echo "To install required packages, run: 'sudo apt update && sudo apt install doxygen graphviz'"
    fi
else
    echo "Skipping Doxygen documentation generation."
fi