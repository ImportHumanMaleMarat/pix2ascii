#!/bin/bash

if [ ! -d "./example_out" ]; then
	mkdir ./example_out
fi
./bin/pix2ascii -o ./example_out/pop.ascii  ./example_in/pop.gif 0 7 4
./bin/pix2ascii -o ./example_out/king.ascii  ./example_in/king.png 4 7 0
./bin/pix2ascii -o ./example_out/ghost.ascii ./example_in/ghost.gif 3 0 4 7
./bin/pix2ascii -o ./example_out/girl.ascii  ./example_in/girl.gif 0 4 7

chmod 555 ./example_out/pop.ascii ./example_out/king.ascii ./example_out/ghost.ascii ./example_out/girl.ascii

