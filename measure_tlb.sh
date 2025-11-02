#!/bin/bash

REPEATS=100000
OUTPUT="tlb_results.txt"
TRIALS=10

echo "# NUMPAGES AverageAccessTime_ns" > "$OUTPUT"

for ((NUMPAGES=1; NUMPAGES<=4096; NUMPAGES*=2)); do
    TOTAL=0.0

    for ((i=1; i<=TRIALS; i++)); do
        RESULT=$(./tlb "$NUMPAGES" "$REPEATS" | sed -n '5p' | awk '{print $3}')

        if [[ -z "$RESULT" || "$RESULT" == *[!0-9.]* ]]; then
            echo "Warning: failed to get result for NUMPAGES=$NUMPAGES on trial $i"
            continue
        fi

        TOTAL=$(echo "$TOTAL + $RESULT" | bc -l)
    done

    AVERAGE=$(echo "$TOTAL / $TRIALS" | bc -l)
    echo "$NUMPAGES $AVERAGE" >> "$OUTPUT"
    echo "NUMPAGES=$NUMPAGES → Avg = $AVERAGE ns"
done