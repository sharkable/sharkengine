export SHARKENGINE_BUILD_TARGET=$1
SHARKENGINE_BUILD_INSTALL=$2

export SHARKENGINE_APP_SOURCE="$(find ${SHARKENGINE_APP_HOME}/src -iname *cc | xargs echo -n)"

if [ ! -d "$SHARKENGINE_APP_HOME/out/android" ]; then
  mkdir -p $SHARKENGINE_APP_HOME/out/android
  cp -r $SHARKENGINE_HOME/platforms/android/build/* $SHARKENGINE_APP_HOME/out/android
fi

VERSION_CODE=$((SE_APP_VERSION_MAJOR * 1000 + SE_APP_VERSION_MINOR))
VERSION=$SE_APP_VERSION_MAJOR.$SE_APP_VERSION_MINOR

sed -e "s/___SHARKENGINE_APP_VERSION_CODE___/$VERSION_CODE/g" \
    -e "s/___SHARKENGINE_APP_VERSION___/$VERSION/g" \
    -e "s/___SHARKENGINE_APP_NAME___/$SE_APP_NAME/g" \
    < $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml \
    > $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml2
mv $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml2 \
    $SHARKENGINE_APP_HOME/out/android/AndroidManifest.xml

cp $SHARKENGINE_APP_HOME/icons/Icon-36.png \
    $SHARKENGINE_APP_HOME/out/android/res/drawable-ldpi/ic_launcher.png
cp $SHARKENGINE_APP_HOME/icons/Icon-48.png \
    $SHARKENGINE_APP_HOME/out/android/res/drawable-mdpi/ic_launcher.png
cp $SHARKENGINE_APP_HOME/icons/Icon-72.png \
    $SHARKENGINE_APP_HOME/out/android/res/drawable-hdpi/ic_launcher.png
cp $SHARKENGINE_APP_HOME/icons/Icon-96.png \
    $SHARKENGINE_APP_HOME/out/android/res/drawable-xhdpi/ic_launcher.png

ant $SHARKENGINE_BUILD_TARGET $SHARKENGINE_BUILD_INSTALL -buildfile \
    $SHARKENGINE_APP_HOME/out/android/build.xml
