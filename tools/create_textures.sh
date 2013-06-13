#!/bin/bash

# Run this from the artresources folder to create tx files from png texture files.

eval $( find textures | grep png$ | sed \
    's|\(.*/\)\(.*\)png|$SHARKENGINE_HOME/tools/bin/png2tx \1\2png ../resources/textures/\2tx;|' );