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

BUILD_TESTS=OFF

for arg in "$@"; do
    case "$arg" in
        --tests) BUILD_TESTS=ON
                 ;;
        *)       printf "${RED}✗ Unknown option: %s${RESET}\n" "$arg"
                 exit 1 ;;
    esac
done

# Run a build step silently.
# If it fails, show its output and exit.
run_step()
{
    local message="$1"
    shift

    printf "\r\033[K${CYAN}%s${RESET}" "$message"

    local output
    if ! output=$("$@" 2>&1); then
        printf "\r\033[K${RED}✗ %s${RESET}\n" "$message"
        printf '%s\n' "$output"
        exit 1
    fi

    printf "\r\033[K${GREEN}✓ %s${RESET}\n" "$message"
}

# Generating Project
run_step "[1/3] Generating..." \
    cmake -G Ninja -S "$PROJECT_DIR" -B "$BUILD_DIR" \
    -DGLPP_BUILD_TESTS="$BUILD_TESTS"

# Compiling Project
run_step "[2/3] Compiling..." \
    cmake --build "$BUILD_DIR"

# Finished
printf "\r\033[K${GREEN}${BOLD}✓ [3/3] GLnoBS build finished!${RESET}\n"
printf "    Output: ${BOLD}%s/libglpp.a${RESET}\n" "$BUILD_DIR"