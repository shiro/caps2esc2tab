#include "appstate.h"

int alt_mod(struct appstate *state) {
    if (state->alt_is_down) {
        if (equal(&state->input, &alt_down) ||
            equal(&state->input, &alt_repeat))
            return 1;
        
        if (equal(&state->input, &alt_up)) {
            state->alt_is_down = 0;
            if (blacklist_contains_key(state, alt_down.code)) {
                unblacklist_key(state, alt_down.code);
                write_event(&alt_up);
                return 1;
            }
            write_event(&alt_down);
            write_event(&syn);
            usleep(20000);
            write_event(&alt_up);
            return 1;
        }
        
        // pressed alt + [KEY]
        if (state->input.value) {
            blacklist_key(state, alt_down.code);
            
            const struct input_event *mapped_down_key = 0;
            const struct input_event *mapped_up_key   = 0;
            
            if (equal(&state->input, &h_down)) {
                mapped_down_key = &arrow_left_down;
                mapped_up_key   = &arrow_left_up;
            } else if (equal(&state->input, &j_down)) {
                mapped_down_key = &arrow_down_down;
                mapped_up_key   = &arrow_down_up;
            } else if (equal(&state->input, &k_down)) {
                mapped_down_key = &arrow_up_down;
                mapped_up_key   = &arrow_up_up;
            } else if (equal(&state->input, &l_down)) {
                mapped_down_key = &arrow_right_down;
                mapped_up_key   = &arrow_right_up;
            }else if (equal(&state->input, &l_up)) {
                //mapped_down_key = &arrow_right_up;
                //mapped_up_key   = &arrow_right_up;
            }
            
            if (mapped_down_key) {
                write_event(mapped_down_key);
                write_event(&syn);
                usleep(20000);
                write_event(mapped_up_key);
                
                return 1;
            }
            
            write_event(&alt_down);
            write_event(&syn);
            usleep(20000);
        }
    } else if (equal(&state->input, &alt_down)) {
        state->alt_is_down = 1;
        return 1;
    }
    
    
    return 0;
}
