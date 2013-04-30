mkdir -p $SHARKENGINE_APP_HOME/out/ios/SharkengineApp.xcodeproj
sed "s/___SHARKENGINE_HOME___/$(echo $SHARKENGINE_HOME | sed -e 's/[\/&]/\\&/g')/g" \
  < $SHARKENGINE_HOME/platforms/ios/build/SharkengineApp.xcodeproj/project.pbxproj \
  > $SHARKENGINE_APP_HOME/out/ios/SharkengineApp.xcodeproj/project.pbxproj
cp $SHARKENGINE_HOME/platforms/ios/build/Info.plist $SHARKENGINE_APP_HOME/out/ios
python setup_project.py
