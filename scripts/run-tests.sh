#!/bin/bash
set -euo pipefail

# Directories
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
BUILD_DIR="$PROJECT_DIR/build"

# Terminal Colors
RESET="\033[0m"
BOLD="\033[1m"
GREEN="\033[32m"
RED="\033[31m"
CYAN="\033[36m"

# Check Build Directory
if [ ! -f "$BUILD_DIR/CMakeCache.txt" ]; then
    printf "${RED}✗ Build directory not configured!${RESET}\n"
    printf "    Run scripts/build.sh --tests first.\n"
    exit 1
fi

# Collect test names, in ctest order
mapfile -t TESTS < <(ctest --test-dir "$BUILD_DIR" -N | sed -n 's/^ *Test *#[0-9]*: *//p')

if [ "${#TESTS[@]}" -eq 0 ]; then
    printf "${RED}✗ No tests found!${RESET}\n"
    printf "    Run scripts/build.sh --tests first.\n"
    exit 1
fi

TOTAL=${#TESTS[@]}
PASSED=0
FAILED=0
INDEX=0

# Run each test on its own line
for name in "${TESTS[@]}"; do
    INDEX=$((INDEX + 1))
    label="[$INDEX/$TOTAL] $name"

    printf "${CYAN}%s${RESET}" "$label"

    if output=$(ctest --test-dir "$BUILD_DIR" -R "^${name}\$" --output-on-failure 2>&1); then
        PASSED=$((PASSED + 1))
        printf "\r\033[K${GREEN}✓ %s${RESET}\n" "$label"
    else
        FAILED=$((FAILED + 1))
        printf "\r\033[K${RED}✗ %s${RESET}\n" "$label"
        printf '%s\n' "$output"
    fi
done

# Summary
if [ "$FAILED" -eq 0 ]; then
    printf "${GREEN}${BOLD}✓ All tests passed (%d/%d)${RESET}\n" "$PASSED" "$TOTAL"
else
    printf "${RED}${BOLD}✗ %d of %d tests failed${RESET}\n" "$FAILED" "$TOTAL"
    exit 1
fi