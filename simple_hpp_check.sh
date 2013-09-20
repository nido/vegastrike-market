#!/bin/bash
for FILE in *.hpp; do
test $((cat "${FILE}" | head -n 2; cat "${FILE}" | tail -n 1) | grep -i H_`echo $FILE | cut -d . -f 1` | wc -l) == 3 || echo $FILE is not good
done
