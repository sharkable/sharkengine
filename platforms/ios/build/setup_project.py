import os

project_home = os.environ['SHARKENGINE_APP_HOME']
sharkengine_home = os.environ['SHARKENGINE_HOME']

import imp
mod_pbxproj_source_path = '/platforms/ios/build/thirdparty/mod_pbxproj/mod_pbxproj.py';
imp.load_source('mod_pbxproj', sharkengine_home + mod_pbxproj_source_path)
from mod_pbxproj import XcodeProject, PBXFileReference

project = XcodeProject.Load(project_home + '/out/ios/SharkengineApp.xcodeproj/project.pbxproj')

PBXFileReference.types['.cc'] = ('sourcecode.cpp.cpp', 'PBXSourcesBuildPhase')
PBXFileReference.types['.tx'] = ('texture.tx', 'PBXResourcesBuildPhase')
PBXFileReference.types['.xml'] = ('markup.xml', 'PBXResourcesBuildPhase')
PBXFileReference.types['.wav'] = ('sound.wav', 'PBXResourcesBuildPhase')

app_group = project.get_or_create_group('App')
project.add_folder(project_home + '/src', app_group)
project.add_folder(project_home + '/resources', app_group)

shark_engine_group = project.get_or_create_group('SharkEngine')
project.add_folder(sharkengine_home + '/core', shark_engine_group)

shark_engine_ios_group = project.get_or_create_group('iOS')
project.add_folder(sharkengine_home + '/platforms/ios/src', shark_engine_ios_group)

project.saveFormat3_2()
