#!/bin/bash

declare -g PIECES=(
bolt-join-mother-board-piece
cassette-3D-print-piece
cassette-cnc-piece
facade-corner-piece
facade-left-piece
speaker-facade-piece
cassette-case-piece
facade-back-piece
facade-front-piece
facade-top-piece
speaker-holder
)

# Model generation
for piece in "${PIECES[@]}"; do
    echo "Pièce : $piece"
    openscad -o stl_files/$piece.stl pieces/$piece.scad
done