mkdir -p $SHARKENGINE_APP_HOME/out/ios/SharkengineApp.xcodeproj

sed "s/___SHARKENGINE_HOME___/$(echo $SHARKENGINE_HOME | sed -e 's/[\/&]/\\&/g')/g" \
  < $SHARKENGINE_HOME/platforms/apple/build/ios/SharkengineApp.xcodeproj/project.pbxproj \
  > $SHARKENGINE_APP_HOME/out/ios/SharkengineApp.xcodeproj/project.pbxproj

APP_ORIENTATION_LETTER=${APP_ORIENTATION:0:1}
if [ $APP_ORIENTATION_LETTER ] && \
    ([ $APP_ORIENTATION_LETTER = "L" ] || [ $APP_ORIENTATION_LETTER = "l" ];) then
  ORIENTATION_STRING_1="UIInterfaceOrientationLandscapeLeft"
  ORIENTATION_STRING_2="UIInterfaceOrientationLandscapeRight"
else
  ORIENTATION_STRING_1="UIInterfaceOrientationPortrait"
  ORIENTATION_STRING_2="UIInterfaceOrientationPortraitUpsideDown"
fi

VERSION=$VERSION_MAJOR.$VERSION_MINOR
sed -e "s/___SHARKENGINE_APP_VERSION___/$VERSION/g" \
    -e "s/___SHARKENGINE_APP_NAME___/$APP_NAME/g" \
    -e "s/___SHARKENGINE_ORIENTATION_1___/$ORIENTATION_STRING_1/g" \
    -e "s/___SHARKENGINE_ORIENTATION_2___/$ORIENTATION_STRING_2/g" \
    < $SHARKENGINE_HOME/platforms/apple/build/ios/Info.plist \
    > $SHARKENGINE_APP_HOME/out/ios/Info.plist

python $SHARKENGINE_HOME/platforms/apple/build/setup_project.py
