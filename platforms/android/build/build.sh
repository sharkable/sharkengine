export SHARKENGINE_APP_SOURCE="$(find ${SHARKENGINE_APP_HOME}/src -iname *cc | xargs echo -n)"
ant debug -buildfile $SHARKENGINE_HOME/platforms/android/build/build.xml
