if [ ! "$1" = "ios" ] && [ ! "$1" = "osx" ]; then
  echo "Error. Usage:"
  echo "    build.sh [ios | osx]"
  exit
fi

mkdir -p $SHARKENGINE_APP_HOME/out/$1/${SE_APP_CODENAME}_${1}.xcodeproj

APP_ORIENTATION_LETTER=${SE_APP_ORIENTATION:0:1}
if [ $APP_ORIENTATION_LETTER ] && \
    ([ $APP_ORIENTATION_LETTER = "L" ] || [ $APP_ORIENTATION_LETTER = "l" ];) then
  ORIENTATION_STRING_1="UIInterfaceOrientationLandscapeLeft"
  ORIENTATION_STRING_2="UIInterfaceOrientationLandscapeRight"
  ORIENTATION_STRING_XIB="Landscape"
else
  ORIENTATION_STRING_1="UIInterfaceOrientationPortrait"
  ORIENTATION_STRING_2="UIInterfaceOrientationPortraitUpsideDown"
  ORIENTATION_STRING_XIB="Portrait"
fi

VERSION=$SE_APP_VERSION_MAJOR.$SE_APP_VERSION_MINOR

sed -e "s/___SHARKENGINE_HOME___/$(echo $SHARKENGINE_HOME | sed -e 's/[\/&]/\\&/g')/g" \
    -e "s/___SHARKSOUND_HOME___/$(echo $SHARKSOUND_HOME | sed -e 's/[\/&]/\\&/g')/g" \
    -e "s/___SHARKENGINE_ORIENTATION_XIB___/$ORIENTATION_STRING_XIB/g" \
    < $SHARKENGINE_HOME/platforms/apple/build/$1/SharkEngine_$1.xcodeproj/project.pbxproj \
    > $SHARKENGINE_APP_HOME/out/$1/${SE_APP_CODENAME}_${1}.xcodeproj/project.pbxproj

sed -e "s/___SHARKENGINE_APP_VERSION___/$VERSION/g" \
    -e "s/___SHARKENGINE_APP_NAME___/$SE_APP_NAME/g" \
    -e "s/___SHARKENGINE_ORIENTATION_1___/$ORIENTATION_STRING_1/g" \
    -e "s/___SHARKENGINE_ORIENTATION_2___/$ORIENTATION_STRING_2/g" \
    -e "s/___SHARKENGINE_ORIENTATION_XIB___/$ORIENTATION_STRING_XIB/g" \
    < $SHARKENGINE_HOME/platforms/apple/build/$1/Info.plist \
    > $SHARKENGINE_APP_HOME/out/$1/Info.plist

python $SHARKENGINE_HOME/platforms/apple/build/setup_project.py $1

if [ $1 = "osx" ]; then
  # Copy entitlements file.
  cp $SHARKENGINE_HOME/platforms/apple/build/osx/SharkEngine.entitlements \
      $SHARKENGINE_APP_HOME/out/osx

  # Generate OS X icon file.
  mkdir $SHARKENGINE_APP_HOME/out/osx/icon.iconset
  cp $SHARKENGINE_APP_HOME/icons/Icon-512.png \
      $SHARKENGINE_APP_HOME/out/osx/icon.iconset/icon_512x512.png
  cp $SHARKENGINE_APP_HOME/icons/Icon-1024.png \
      $SHARKENGINE_APP_HOME/out/osx/icon.iconset/icon_512x512@2x.png
  iconutil -c icns --output $SHARKENGINE_APP_HOME/out/osx/icon.icns \
      $SHARKENGINE_APP_HOME/out/osx/icon.iconset > /dev/null 2>&1
  rm -rf $SHARKENGINE_APP_HOME/out/osx/icon.iconset
else
  # Copy iOS icons and launch images.
  mkdir -p $SHARKENGINE_APP_HOME/out/ios/icons
  cp $SHARKENGINE_APP_HOME/icons/Icon-57.png $SHARKENGINE_APP_HOME/out/ios/icons/IconPhone.png
  cp $SHARKENGINE_APP_HOME/icons/Icon-72.png $SHARKENGINE_APP_HOME/out/ios/icons/IconPad.png
  cp $SHARKENGINE_APP_HOME/icons/Icon-114.png $SHARKENGINE_APP_HOME/out/ios/icons/IconPhone@2x.png
  cp $SHARKENGINE_APP_HOME/icons/Icon-144.png $SHARKENGINE_APP_HOME/out/ios/icons/IconPad@2x.png
  cp $SHARKENGINE_APP_HOME/icons/Launch-320x480.png \
      $SHARKENGINE_APP_HOME/out/ios/icons/LaunchImage.png
  cp $SHARKENGINE_APP_HOME/icons/Launch-640x960.png \
      $SHARKENGINE_APP_HOME/out/ios/icons/LaunchImage@2x.png
  cp $SHARKENGINE_APP_HOME/icons/Launch-640x1136.png \
      $SHARKENGINE_APP_HOME/out/ios/icons/LaunchImage-568h@2x.png
  cp $SHARKENGINE_APP_HOME/icons/Launch-768x1024.png \
      $SHARKENGINE_APP_HOME/out/ios/icons/LaunchImage-Portrait~ipad.png
  cp $SHARKENGINE_APP_HOME/icons/Launch-1536x2048.png \
      $SHARKENGINE_APP_HOME/out/ios/icons/LaunchImage-Portrait@2x~ipad.png  
fi
