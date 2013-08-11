import os
import sys

if len(sys.argv) <= 1 or (sys.argv[1] != "ios" and sys.argv[1] != "osx"):
  sys.exit("Error. Usage:\n    setup_project.py [ios | osx]")

target=sys.argv[1]

app_home = os.environ['SHARKENGINE_APP_HOME']
sharkengine_home = os.environ['SHARKENGINE_HOME']

import imp
mod_pbxproj_source_path = '/platforms/apple/build/thirdparty/mod_pbxproj/mod_pbxproj.py';
imp.load_source('mod_pbxproj', sharkengine_home + mod_pbxproj_source_path)
from mod_pbxproj import XcodeProject, PBXFileReference

project = XcodeProject.Load(app_home + '/out/' + target + \
                            '/SharkengineApp.xcodeproj/project.pbxproj')

PBXFileReference.types['.cc'] = ('sourcecode.cpp.cpp', 'PBXSourcesBuildPhase')
PBXFileReference.types['.tx'] = ('texture.tx', 'PBXResourcesBuildPhase')
PBXFileReference.types['.xml'] = ('markup.xml', 'PBXResourcesBuildPhase')
PBXFileReference.types['.wav'] = ('sound.wav', 'PBXResourcesBuildPhase')

app_group = project.get_or_create_group('App')
project.add_folder(app_home + '/src', app_group)
project.add_folder(app_home + '/assets', app_group)

project.saveFormat3_2()
