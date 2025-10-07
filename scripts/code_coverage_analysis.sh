#!/bin/sh

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd $SCRIPT_DIR/..

cmake --preset code-coverage
cmake --build --preset code-coverage
ctest --test-dir build/code-coverage/test/ --preset test-all

mkdir -p ./build/code-coverage/coverage-data
lcov --directory ./build/code-coverage/test/CMakeFiles/Test.dir/ --capture --ignore-errors mismatch --output-file ./build/code-coverage/coverage-data/coverage.raw.info
lcov --ignore-errors unused --remove ./build/code-coverage/coverage-data/coverage.raw.info "*/*deps/*/" "/usr/*" "*/test/*" --output-file ./build/code-coverage/coverage-data/coverage.filtered.info

mkdir -p ./build/code-coverage/coverage-report
genhtml ./build/code-coverage/coverage-data/coverage.filtered.info --output-directory ./build/code-coverage/coverage-report
