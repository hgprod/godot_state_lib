#"/Applications/Godot 4_3.app/Contents/MacOS/Godot" --doctool ./ --gdextension-docs
scons platform=macos target=template_debug
scons platform=macos target=template_release
scons platform=macos target=editor

scons platform=windows target=template_debug
scons platform=windows target=template_release
scons platform=windows target=editor

#scons platform=linux target=template_debug
#scons platform=linux target=template_release
#scons platform=linux target=editor

#scons platform=android target=template_debug
#scons platform=android target=template_release
#scons platform=android target=editor

scons platform=ios target=template_debug
scons platform=ios target=template_release

#scons platform=web target=template_debug
#scons platform=web target=template_release
