#include "appstate.h"

int tab_mod(struct appstate *state) {
    if (state->tab_is_down) {
        // repeat tab ignore
        if (equal(&state->input, &tab_down) ||
            equal(&state->input, &tab_repeat))
            return 1;
        
        // handle tab up
        if (equal(&state->input, &tab_up)) {
            state->tab_is_down = 0;
            if (blacklist_contains_key(state, tab_down.code)) {
                unblacklist_key(state, tab_down.code);
                write_event(&alt_up);
                write_event(&shift_up);
                write_event(&meta_up);
                return 1;
            }
            write_event(&tab_down);
            write_event(&syn);
            usleep(20000);
            write_event(&tab_up);
            
            return 1;
        }
        
        // handle tab + [key]
        if (state->input.value) {
            blacklist_key(state, tab_down.code);
            write_event(&alt_down);
            write_event(&shift_down);
            write_event(&meta_down);
            write_event(&syn);
            usleep(20000);
        }
    } else if (equal(&state->input, &tab_down) && !is_modifier_down(state)) {
        state->tab_is_down = 1;
        return 1;
    }
    
    return 0;
}
