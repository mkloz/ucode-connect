#!/bin/bash

# Path to your program executable
PROGRAM="./pathfinder"

# Directory containing the test files
TEST_DIR="test/"

echo "Testing without parameters..."
$PROGRAM
echo "--------------------------------------"

echo "Testing with 2 parameters..."
$PROGRAM "ffe" "wf"
echo "--------------------------------------"

echo "Testing with invalid filename parameters..."
$PROGRAM "fake"
echo "--------------------------------------"

# Iterate over all files in the test directory
for FILE in "$TEST_DIR"*
do
    if [ -f "$FILE" ]; then
        # Check if the file is a regular file
        echo "Testing $FILE..."
        $PROGRAM "$FILE"
        echo "--------------------------------------"
    fi
done
