import os
import sys

if len(sys.argv) <= 1 or (sys.argv[1] != "ios" and sys.argv[1] != "osx"):
  sys.exit("Error. Usage:\n    setup_project.py [ios | osx]")

target=sys.argv[1]

sharkengine_home = os.environ['SHARKENGINE_HOME']
app_home = os.environ['SHARKENGINE_APP_HOME']
app_codename = os.environ['SE_APP_CODENAME']

import imp
mod_pbxproj_source_path = '/platforms/apple/build/thirdparty/mod_pbxproj/mod_pbxproj.py';
imp.load_source('mod_pbxproj', sharkengine_home + mod_pbxproj_source_path)
from mod_pbxproj import XcodeProject, PBXFileReference

project = XcodeProject.Load(app_home + '/out/' + target + '/' + app_codename + '_' + target + \
                            '.xcodeproj/project.pbxproj')

PBXFileReference.types['.cc'] = ('sourcecode.cpp.cpp', 'PBXSourcesBuildPhase')
PBXFileReference.types['.tx'] = ('texture.tx', 'PBXResourcesBuildPhase')
PBXFileReference.types['.xml'] = ('markup.xml', 'PBXResourcesBuildPhase')
PBXFileReference.types['.wav'] = ('sound.wav', 'PBXResourcesBuildPhase')
PBXFileReference.types['.xm'] = ('mod.xm', 'PBXResourcesBuildPhase')
PBXFileReference.types['.info'] = ('mission.info', 'PBXResourcesBuildPhase')

app_group = project.get_or_create_group('App')
project.add_folder(app_home + '/src', app_group)
if target == "ios":
  project.add_folder(app_home + '/assets', app_group)
else:
  project.add_folder(app_home + '/assets/images', app_group)
  project.add_folder(app_home + '/assets/sounds', app_group)

project.saveFormat3_2()
