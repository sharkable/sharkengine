import imp
import os
imp.load_source('mod_pbxproj', 'thirdparty/mod_pbxproj/mod_pbxproj.py')
from mod_pbxproj import XcodeProject, PBXFileReference

project_home = os.environ['SHARKENGINE_APP_HOME']
shark_engine_home = os.environ['SHARKENGINE_HOME']
project = XcodeProject.Load(project_home + '/out/ios/SharkengineApp.xcodeproj/project.pbxproj')

PBXFileReference.types['.cc'] = ('sourcecode.cpp.cpp', 'PBXSourcesBuildPhase')
PBXFileReference.types['.tx'] = ('texture.tx', 'PBXResourcesBuildPhase')
PBXFileReference.types['.xml'] = ('markup.xml', 'PBXResourcesBuildPhase')
PBXFileReference.types['.wav'] = ('sound.wav', 'PBXResourcesBuildPhase')

app_group = project.get_or_create_group('App')
project.add_folder(project_home + '/src', app_group)
project.add_folder(project_home + '/resources', app_group)

shark_engine_group = project.get_or_create_group('SharkEngine')
project.add_folder(shark_engine_home + '/core', shark_engine_group)

shark_engine_ios_group = project.get_or_create_group('iOS')
project.add_folder(shark_engine_home + '/platforms/ios/src', shark_engine_ios_group)

project.saveFormat3_2()
