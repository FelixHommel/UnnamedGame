#!/bin/sh

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd $SCRIPT_DIR/..

cmake --preset code-coverage
cmake --build --preset code-coverage
ctest --test-dir ./build/code-coverage/src/test/ --preset test-all

mkdir -p ./build/code-coverage/coverage-data
lcov --directory ./build/code-coverage/src/test/CMakeFiles/Test.dir/ --capture --ignore-errors mismatch --output-file ./build/code-coverage/coverage-data/coverage.raw.info
lcov --ignore-errors unused --remove ./build/code-coverage/coverage-data/coverage.raw.info "*/*deps/*/" "/usr/*" "*/test/*" --output-file ./build/code-coverage/coverage-data/coverage.filtered.info

mkdir -p ./build/code-coverage/coverage-report
genhtml ./build/code-coverage/coverage-data/coverage.filtered.info --output-directory ./build/code-coverage/coverage-report

SUMMARY=$(
    lcov --summary ./build/code-coverage/coverage-data/coverage.filtered.info |
        grep "lines......" |
        awk '{print $2}' |
        tr -d '%'
)

COVERAGE=$(printf "%.0f" "$SUMMARY")
LINE_COVERAGE_REQ=80
LINE_COVERAGE_MIN=70
JSON_OUTPUT_LOCATION="./build/code-coverage/coverage-report/coverage-badge.json"

if [ "$COVERAGE" -ge $LINE_COVERAGE_REQ ]; then
    COLOR="green"
elif [ "$COVERAGE" -ge $LINE_COVERAGE_MIN ]; then
    COLOR="yellow"
else
    COLOR="red"
fi

echo "{\"schemaVersion\":1, \"label\":\"coverage\",\"message\":\"${COVERAGE}%\",\"color\":\"${COLOR}\"}" > $JSON_OUTPUT_LOCATION
