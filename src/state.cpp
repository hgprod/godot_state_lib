#include "state.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

State::State() {
    _context = Dictionary();
    _active = false;
}

void State::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_context"), &State::get_context);
    ClassDB::bind_method(D_METHOD("set_active", "active"), &State::set_active);
    ClassDB::bind_method(D_METHOD("get_active"), &State::get_active);

    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_active"), "set_active", "get_active");

    GDVIRTUAL_BIND(_begin_state);
    GDVIRTUAL_BIND(_end_state);
    GDVIRTUAL_BIND(_goto_state);
}

void State::set_context(const Dictionary &context) {
    _context = context;
    State *p = get_parent_state();
    if(p != nullptr) p->set_context(context);
}

Dictionary State::get_context() const {
    return _context;
}

void State::set_active(const bool active) {
    _active = active;
    State *p = get_parent_state();
    if(p != nullptr) p->set_active(active);
}

bool State::get_active() const {
    return _active;
}

State* State::get_parent_state() {
    Node *parent = get_parent();
    return dynamic_cast<State*>(parent);
}

StateMachine::StateMachine() {
    _default = "";
    _context = Dictionary();
    _current_state = nullptr;
    set_process(true);
}

void StateMachine::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_context", "context"), &StateMachine::set_context);
    ClassDB::bind_method(D_METHOD("get_context"), &StateMachine::get_context);
    ClassDB::bind_method(D_METHOD("set_default", "name"), &StateMachine::set_default);
    ClassDB::bind_method(D_METHOD("get_default"), &StateMachine::get_default);

    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "context"), "set_context", "get_context");
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "default"), "set_default", "get_default");
}

void StateMachine::set_context(const Dictionary &context) {
    _context = context;
}

Dictionary StateMachine::get_context() const {
    return _context;
}

void StateMachine::set_default(const String &name) {
    _default = name;
}

String StateMachine::get_default() const {
    return _default;
}

void callBeginState(State *state) {
    State *parent = state->get_parent_state();
    if(parent != nullptr) callBeginState(parent);
    GDVIRTUAL_CALL_PTR(state, _begin_state);
//    state->call("_begin_state");
}

void callEndState(State *state) {
    GDVIRTUAL_CALL_PTR(state, _end_state);
//    state->call("_end_state");
    State *parent = state->get_parent_state();
    if(parent != nullptr) callEndState(parent);
}

String callGotoState(State *state) {
//    String next = state->call("_goto_state");
    String next = "";
    GDVIRTUAL_CALL_PTR(state, _goto_state, next);
    if(next == "") {
        State *parent = state->get_parent_state();
        if(parent != nullptr) next = callGotoState(parent);
    }
    return next;
}

void StateMachine::_notification(int p_what) {
    if(p_what == NOTIFICATION_READY) {
        change_state();
    }
    else if (p_what == NOTIFICATION_PROCESS) {
        if(_current_state != nullptr) {
            change_state();
        }
    }
}

State* searchStateName(State* state, const String &name) {
    StringName n_name = state->get_name();
    if(n_name == name) return state;
    TypedArray<Node> children = state->get_children();
    for(int index=0; index < children.size(); index++) {
        Object *child = children[index];
        State *st = dynamic_cast<State*>(child);
        if(st != nullptr) {
            State *obj = searchStateName(st, name);
            if(obj != nullptr) return obj;
        }
    }
    return nullptr;
}

State* StateMachine::find_state(const String &name) {
    TypedArray<Node> children = get_children();
    for(int count=0; count < children.size(); count++) {
        Object* child = children[count];
        State *st = dynamic_cast<State*>(child);
        State *obj = searchStateName(st, name);
        if(obj != nullptr) return obj;
    }
    return nullptr;
}

void StateMachine::change_state() {
    String next = "";
    if(_current_state == nullptr) next = _default;
    else next = callGotoState(_current_state);
    if(next == "") return;

    if(_current_state != nullptr) {
        callEndState(_current_state);
        _current_state->set_active(false);
    }
    _current_state = find_state(next);
    if(_current_state != nullptr) {
        _current_state->set_context(_context);
        _current_state->set_active(true);
        callBeginState(_current_state);
    }
}