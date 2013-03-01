#!/bin/bash

# Run this from the artresources folder to create tx files from png texture files.

eval $( find textures | grep png$ | \
    sed 's|\(.*\)png|../gameengine/tools/bin/png2tx \1png ../resources/\1tx;|' );
    
