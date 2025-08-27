

#!/bin/bash

input_folder="./input"

mp3_files=$(find "$input_folder" -type f -name "*.mp3")

output_folder="./output"
count=1

for mp3_file in $mp3_files; do
	cp "$mp3_file" "$output_folder/$(printf "%04d" $count).mp3"
    count=$((count+1))
    echo $count
    echo "$mp3_file"
done



