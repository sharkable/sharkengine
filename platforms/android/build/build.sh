export SHARKENGINE_APP_SOURCE="$(find ${SHARKENGINE_APP_HOME}/src -iname *cc | xargs echo -n)"
cp -r $SHARKENGINE_HOME/platforms/android/build $SHARKENGINE_APP_HOME/out/android
ant debug -buildfile $SHARKENGINE_APP_HOME/out/android/build.xml
