#!/bin/bash

# Function to print in green and centered
print_centered_green() {
    local msg="$1"
    local width=$(tput cols)
    local green="\033[1;32m"
    local reset="\033[0m"
    local figlet_output=$(figlet "$msg")

    while IFS= read -r line; do
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

total_tests=0
failed_tests=0
passed_tests=0

# Use process substitution to avoid subshell for while loop
while IFS= read -r file; do
    ((total_tests++))
    echo -e "\033[1;33mRunning: $file\033[0m"
    start=$(date +%s.%N)

    "$file"
    exit_code=$?

    end=$(date +%s.%N)
    runtime=$(echo "$end - $start" | bc)

    if [ $exit_code -ne 0 ]; then
        echo -e "\033[1;31m❌ $file failed with exit code $exit_code\033[0m"
        ((failed_tests++))
    else
        echo -e "\033[1;32m✅ $file passed\033[0m"
        ((passed_tests++))
    fi

    echo -e "\033[0;36m⏱  Took ${runtime}s\033[0m"
    echo "-------------------------------------"
done < <(find ./bin -type f -executable)

echo -e "\n\033[1;34mSummary:\033[0m"
echo -e "✅ Passed: $passed_tests"
echo -e "❌ Failed: $failed_tests"
echo -e "🔬 Total:  $total_tests"

if [ "$passed_tests" -eq "$total_tests" ]; then
    echo -e "\n\033[1;42m🎉 All tests passed successfully! 🎉\033[0m"
else
    echo -e "\n\033[1;41m⚠ Some tests failed. Review the output above. ⚠\033[0m"
fi
