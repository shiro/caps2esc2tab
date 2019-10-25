#include "appstate.h"

int capslock_mod(struct appstate *state) {
    if (state->capslock_is_down) {
        if (equal(&state->input, &capslock_down) ||
            equal(&state->input, &capslock_repeat))
            return 1;
        
        if (equal(&state->input, &capslock_up)) {
            state->capslock_is_down = 0;
            
            if (blacklist_contains_key(state, capslock_down.code)) {
                unblacklist_key(state, capslock_down.code);
                write_event(&ctrl_up);
                return 1;
            }
            write_event(&esc_down);
            write_event(&syn);
            usleep(20000);
            write_event(&esc_up);
            return 1;
        }
        
        if (state->input.value) {
            blacklist_key(state, capslock_down.code);
            
            // navigation keys (h, j, k, l)
            // only bind to capslock + directional keys, no modifiers
            if (!state->tab_is_down &&
                !is_modifier_down(state) && (
                        equal(&state->input, &h_down) ||
                        equal(&state->input, &j_down) ||
                        equal(&state->input, &k_down) ||
                        equal(&state->input, &l_down))) {
                
                write_event(&meta_down);
                write_event(&alt_down);
                write_event(&ctrl_down);
                write_event(&shift_down);
                write_event(&state->input);
                
                write_event(&syn);
                usleep(20000);
    
                write_event(&meta_up);
                write_event(&alt_up);
                write_event(&ctrl_up);
                write_event(&shift_up);
                
                return 1;
            }
            
            write_event(&ctrl_down);
            write_event(&syn);
            usleep(20000);
        }
    } else if (equal(&state->input, &capslock_down) && !is_modifier_down(state)) {
        state->capslock_is_down = 1;
        return 1;
    } else if (equal(&state->input, &capslock_down)) {
        // handle modifier + caps_lock down
        return 1;
    } else if (equal(&state->input, &capslock_up)) {
        // handle modifier + caps_lock up
        write_event(&esc_down);
        write_event(&syn);
        usleep(20000);
        write_event(&esc_up);
        return 1;
    }
    
    return 0;
}
