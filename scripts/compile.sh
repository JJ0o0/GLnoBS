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
    printf "    Run scripts/build.sh first.\n"
    exit 1
fi

# Compiling Project
printf "${CYAN}[1/2] Compiling...${RESET}"

if ! output=$(cmake --build "$BUILD_DIR" 2>&1); then
    printf "\r\033[K${RED}✗ [1/2] Compilation failed!${RESET}\n"
    printf '%s\n' "$output"
    exit 1
fi

printf "\r\033[K${GREEN}✓ [1/2] Compilation completed${RESET}\n"

# Finished
printf "${GREEN}${BOLD}✓ [2/2] GLnoBS compiled successfully!${RESET}\n"
