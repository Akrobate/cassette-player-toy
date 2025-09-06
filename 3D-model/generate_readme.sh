#!/bin/bash

PNG_FILES_PATH=./png_files
OUTPUT_FILE=IMAGES.md

echo "# Aperçu des rendus OpenSCAD" > $OUTPUT_FILE
echo "" >> $OUTPUT_FILE

# Pièces
if [ -d "$PNG_FILES_PATH/pieces" ]; then
    echo "## Pièces" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
    for img in "$PNG_FILES_PATH/pieces"/*.png; do
        file=$(basename "$img")
        name="${file%.*}"
        echo "### $name" >> $OUTPUT_FILE
        echo "![${name}](png_files/pieces/${file})" >> $OUTPUT_FILE
        echo "" >> $OUTPUT_FILE
    done
fi

# Composants
if [ -d "$PNG_FILES_PATH/components" ]; then
    echo "## Composants" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
    for img in "$PNG_FILES_PATH/components"/*.png; do
        file=$(basename "$img")
        name="${file%.*}"
        echo "### $name" >> $OUTPUT_FILE
        echo "![${name}](png_files/components/${file})" >> $OUTPUT_FILE
        echo "" >> $OUTPUT_FILE
    done
fi

# Main
if [ -f "$PNG_FILES_PATH/main.png" ]; then
    echo "## Assemblage principal" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
    echo "![main](png_files/main.png)" >> $OUTPUT_FILE
    echo "" >> $OUTPUT_FILE
fi

echo "Fichier Markdown généré : $OUTPUT_FILE"
