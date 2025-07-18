#!/bin/bash

# Function to print in green and centered
print_centered_green() {
    local msg="$1"
    local width=$(tput cols)
    local green="\033[1;32m"
    local reset="\033[0m"
    local figlet_output=$(figlet "$msg")

    while IFS= read -r line; do
        # Strip ANSI codes from length calculation
        local line_length=${#line}
        local padding=$(( (width - line_length) / 2 ))
        printf "%*s" "$padding" ""
        printf "${green}%s${reset}\n" "$line"
    done <<< "$figlet_output"
}

clear
print_centered_green "TEST Fast-Fourier Transform"
echo
echo "-------------------------------------"
# Find all executable files in ./bin and subdirectories, then run them
find ./bin -type f -executable | while read -r file; do
    echo -e "\033[1;33mRunning: $file\033[0m"
    start=$(date +%s.%N)

    "$file"
    exit_code=$?

    end=$(date +%s.%N)
    runtime=$(echo "$end - $start" | bc)

    if [ $exit_code -ne 0 ]; then
        echo -e "\033[1;31m❌ $file failed with exit code $exit_code\033[0m"
    else
        echo -e "\033[1;32m✅ $file passed\033[0m"
    fi

    echo -e "\033[0;36m⏱  Took ${runtime}s\033[0m"
    echo "-------------------------------------"
done

