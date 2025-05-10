
declare -g PIECES=(
bolt-join-mother-board-piece
cassette-piece
facade-corner-piece
facade-left-piece
speaker-facade-piece
cassette-case-piece
facade-back-piece
facade-front-piece
facade-top-piece
speaker-holder
)

declare -g COMPONENTS=(
housing-component
mother-board-component
)

# Pieces png generation
for piece in "${PIECES[@]}"; do
    echo "Pièce : $piece"
    openscad --colorscheme="BeforeDawn" --view="axes,scales" -o png_files/pieces/$piece.png pieces/$piece.scad
done

# compoenents png generation
for component in "${COMPONENTS[@]}"; do
    echo "Pièce : $component"
    openscad --colorscheme="BeforeDawn" -o png_files/components/$component.png components/$component.scad
done
