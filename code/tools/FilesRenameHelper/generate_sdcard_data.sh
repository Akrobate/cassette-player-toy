#!/bin/bash

src="./input"
dest="./output"

# Créer le dossier de destination
mkdir -p "$dest"

# Parcourir récursivement les sous-dossiers
find "$src" -mindepth 1 -type d | while read dir; do
    # Chemin relatif du sous-dossier par rapport à la racine
    relpath="${dir#$src/}"
    target="$dest/$relpath"

    echo $relpath
    echo "test"

    mkdir -p "$target"

    i=1
    # Parcourir les fichiers dans ce sous-dossier
    for file in "$dir"/*; do
        [ -f "$file" ] || continue  # ignorer si ce n'est pas un fichier

        ext="${file##*.}"  # extension
        printf -v newname "%04d.%s" "$i" "$ext"

        cp "$file" "$target/$newname"
        i=$((i+1))
    done
done

echo "✅ Copie et renommage terminés dans $dest"