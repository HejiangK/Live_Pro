#!/bin/bash
sed -i "2i /home/ubuntu/Live_Pro/libs/ffmpeg/lib"
sed -i "3i /home/ubuntu/Live_Pro/libs/curl/lib"
make clean
make
ldconfig
