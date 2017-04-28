#!/bin/bash
cd ~/Documents/LaChambre
killall pd
killall wish
killall -9 pd
killall -9 wish

CURRENTDISPLAY=$DISPLAY
 
export DISPLAY=:0.0 && pd -noaudio -lib pof -open pofmainTV.pd &
export DISPLAY=:0.0 && pd -noaudio -lib pof -open pofmain.pd &

export DISPLAY=$CURRENTDISPLAY
pd -open 0LaChambre.pd 

