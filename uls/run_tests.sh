#!/bin/bash
#non zero for printing output
PRINT_CASES=0

# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No color
YELLOW='\033[33;1m'
# Path to your program executables
ULS="./uls"
LS="ls"

# Directory containing the test files
TEST_DIR="test"

# Initialize variables to count successful and failed tests
SUCCESS_COUNT=0
FAILED_COUNT=0

for i in {0..7}
do
  for j in {0..7}
  do
    for k in {0..7}
    do
      eval touch "$TEST_DIR/chmod/chmod$i$j$k.txt"
      eval mkdir "-p $TEST_DIR/chmod/chmod$i$j$k"
      eval chmod "$i$j$k $TEST_DIR/chmod/chmod$i$j$k.txt $TEST_DIR/chmod/chmod$i$j$k"
    done
  done
done

# Create a function to run the programs and compare their outputs and exit codes
run_and_compare() {
    args="$1"
    echo -e "Testing with args: $args"

    # Run the original uls program and capture both output and exit code
    original_output="$(eval $ULS "$args" 2>&1)"

    # Run the test uls program and capture both output and exit code
    test_output="$(eval $LS "$args" 2>&1)"
    # Compare the outputs using diff
    if [ "$PRINT_CASES" -ne 0 ]; then
      echo -e "${YELLOW}$original_output${NC}"
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
run_and_compare "$TEST_DIR/chmod";
run_and_compare "-l $TEST_DIR/chmod";

run_and_compare "";
run_and_compare "-l";

run_and_compare "$TEST_DIR";
run_and_compare "-l $TEST_DIR";

run_and_compare "$TEST_DIR/dir1 $TEST_DIR/dir3";
run_and_compare "-l $TEST_DIR/dir1 $TEST_DIR/dir3";

run_and_compare "$TEST_DIR/dir3 $TEST_DIR/dir1 $TEST_DIR/file1";
run_and_compare "-l $TEST_DIR/dir3 $TEST_DIR/dir1 $TEST_DIR/file1";

run_and_compare "$TEST_DIR/dir1";
run_and_compare "-l $TEST_DIR/dir1";

run_and_compare "$TEST_DIR/file2 $TEST_DIR/file1";
run_and_compare "-l $TEST_DIR/file2 $TEST_DIR/file1";


run_and_compare "$TEST_DIR/dir3";
run_and_compare "-l $TEST_DIR/dir3";
# Display summary
echo -e "Tests completed. ${GREEN}${SUCCESS_COUNT} successful tests.${NC} ${RED}${FAILED_COUNT} failed tests.${NC}"
