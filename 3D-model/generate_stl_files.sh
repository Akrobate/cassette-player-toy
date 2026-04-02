#!/bin/bash

declare -g PIECES=(
boltJoinMotherBoardPiece
cassette3DPrintPiece
cassetteCncPiece
facadeCornerPiece
facade-left-piece
speakerFacadePiece
cassetteCasePiece
facadeBackPiece
facadeFrontPiece
facadeTopPiece
speakerHolder
)

# Model generation
for piece in "${PIECES[@]}"; do
    echo "Pièce : $piece"
    openscad -o stl_files/$piece.stl pieces/$piece.scad
done