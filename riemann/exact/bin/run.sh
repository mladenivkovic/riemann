#!/bin/bash

make
if [[ $? -ne 0 ]]; then
    exit 1
fi
echo "############################################################################"
./riemann paramfile.txt ../ic/sod_test.dat
./riemann paramfile.txt ../ic/123problem.dat
./riemann paramfile.txt ../ic/left_blast_wave.dat
./riemann paramfile.txt ../ic/right_blast_wave.dat
./riemann paramfile.txt ../ic/two_shocks.dat
