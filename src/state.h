#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

namespace godot {
    class State: public Node {
        GDCLASS(State, Node);
    
    protected:
        static void _bind_methods();
    
    private:
        Dictionary _context;
        bool _active;

    public:
        State();
        void set_context(const Dictionary &context);
        Dictionary get_context() const;
        void set_active(const bool active);
        bool get_active() const;
        State* get_parent_state();

        GDVIRTUAL0(_begin_state);
        GDVIRTUAL0(_end_state);
        GDVIRTUAL0R(String, _goto_state);
    };

    class StateMachine: public Node {
        GDCLASS(StateMachine, Node);

    protected:
        static void _bind_methods();

    private:
        String _default;
        Dictionary _context;
        State *_current_state;
    
    public:
        StateMachine();
        void set_context(const Dictionary &context);
        Dictionary get_context() const;
        void set_default(const String &name);
        String get_default() const;

    protected:
        void _notification(int p_what);
        State* find_state(const String &name);
        void change_state();
    };
}

#endif