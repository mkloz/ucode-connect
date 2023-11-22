#!/bin/bash
#non zero for printing output
PRINT_CASES=0
# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No color
YELLOW='\033[33;1m'
# Path to your program executables
PATHFINDER="./pathfinder"

# Directory containing the test files
TEST_DIR="test"

# Initialize variables to count successful and failed tests
SUCCESS_COUNT=0
FAILED_COUNT=0

# Create a function to run the programs and compare their outputs and exit codes
run_and_compare() {
    input_file="$1"
    echo -e "Testing with input file: $input_file"

    # Run the original pathfinder program and capture both output and exit code
    original_output="$($PATHFINDER "$input_file" 2>&1)"

    # Run the test pathfinder program and capture both output and exit code
    test_output="$(cat "$TEST_DIR/tests_expected_output/$(basename "$FILE")")"
    # Compare the outputs using diff
    if [ "$PRINT_CASES" -ne 0 ]; then
      echo -e "${YELLOW} $original_output${NC}"
    fi
    if [ "$original_output" = "$test_output" ]; then
        echo -e "${GREEN}Outputs match.${NC}"
        ((SUCCESS_COUNT++))
    else
        echo -e "${RED}Outputs differ.${YELLOW}"
        diff <(echo "$original_output") <(echo "$test_output")
        echo -e "${NC}"
        ((FAILED_COUNT++))
    fi

    # Clean up temporary files
    rm -f original_output.txt test_output.txt

    echo "--------------------------------------"
}

# Iterate over all files in the test directory
for FILE in "$TEST_DIR/testcases/"*
do
    if [ -f "$FILE" ]; then
        # Check if the file is a regular file and not a directory
        run_and_compare "$FILE"
    fi
done

# Display summary
echo -e "Tests completed. ${GREEN}${SUCCESS_COUNT} successful tests.${NC} ${RED}${FAILED_COUNT} failed tests.${NC}"
