#!/bin/bash
for x in test/*.?pp; do bcpp -yb -ylcnc -s -tbnl -bcl "${x}"; done
