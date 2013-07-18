export SHARKENGINE_APP_SOURCE="$(find ${SHARKENGINE_APP_HOME}/src -iname *cc | xargs echo -n)"

if [ ! -d "$SHARKENGINE_APP_HOME/out/android" ]; then
  mkdir -p $SHARKENGINE_APP_HOME/out/android
  cp -r $SHARKENGINE_HOME/platforms/android/build/* $SHARKENGINE_APP_HOME/out/android
fi

VERSION_CODE=$((VERSION_MAJOR * 1000 + VERSION_MINOR))
VERSION=$VERSION_MAJOR.$VERSION_MINOR

sed -e "s/___SHARKENGINE_APP_VERSION_CODE___/$VERSION_CODE/g" \
    -e "s/___SHARKENGINE_APP_VERSION___/$VERSION/g" \
    -e "s/___SHARKENGINE_APP_NAME___/$APP_NAME/g" \
    < $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml \
    > $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml2
mv $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml2 \
    $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml

if [ "$1" = "build" ]; then
  export SE_BUILD_OPTION=""
else
  export SE_BUILD_OPTION="install"
fi
ant debug $SE_BUILD_OPTION -buildfile $SHARKENGINE_APP_HOME/out/android/build.xml
