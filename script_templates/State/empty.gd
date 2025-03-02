extends State

# _begin_state runs when the state first becomes active. If this is a parent state, 
# it runs whenever one of its children becomes active. Initialize all internal
# variables here.
func _begin_state():
	pass

# _end_state runs whenever a state is becoming inactive. If this is a parent state,
# it runs whenever one of its children becomes inactive. Do all cleanup here. Change
# any state specific items (animations, colors, etc.) back to their default values
# before the next state starts.
func _end_state():
	pass

# called every frame. Return the name of the next state to run. If this state 
# should continue, return an empty string.
func _goto_state() -> String:
	return ""

# for all built in functions (_process, _input, etc.), use 
#	if not is_active(): return
# to ensure that this is the active state before starting a process.

# get_context() will return a dictionary that can be used to pass data between states.