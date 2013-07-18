export SHARKENGINE_APP_SOURCE="$(find ${SHARKENGINE_APP_HOME}/src -iname *cc | xargs echo -n)"
cp -r $SHARKENGINE_HOME/platforms/android/build $SHARKENGINE_APP_HOME/out/android
if [ "$1" = "build" ]
then
  export SE_BUILD_OPTION=""
else
  export SE_BUILD_OPTION="install"
fi
ant debug $SE_BUILD_OPTION -buildfile $SHARKENGINE_APP_HOME/out/android/build.xml
