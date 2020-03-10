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
        blacklist_key(state, alt_down.code);
        
        const struct input_event *mapped_key = 0;
        
        
        if (equal(&state->input, &h_down)) {
            mapped_key = &arrow_left_down;
        } else if (equal(&state->input, &h_up)) {
            mapped_key = &arrow_left_up;
        } else if (equal(&state->input, &h_repeat)) {
            mapped_key = &arrow_left_repeat;
        } else if (equal(&state->input, &j_down)) {
            mapped_key = &arrow_down_down;
        } else if (equal(&state->input, &j_up)) {
            mapped_key = &arrow_down_up;
        } else if (equal(&state->input, &j_repeat)) {
            mapped_key = &arrow_down_repeat;
        } else if (equal(&state->input, &k_down)) {
            mapped_key = &arrow_up_down;
        } else if (equal(&state->input, &k_up)) {
            mapped_key = &arrow_up_up;
        } else if (equal(&state->input, &k_repeat)) {
            mapped_key = &arrow_up_repeat;
        } else if (equal(&state->input, &l_down)) {
            mapped_key = &arrow_right_down;
        } else if (equal(&state->input, &l_repeat)) {
            mapped_key = &arrow_right_repeat;
        } else if (equal(&state->input, &l_up)) {
            mapped_key = &arrow_right_up;
        }
    
        if (equal(&state->input, &wheel_up)) {
            write_event(&alt_up);
            return 1;
        }
        
        if (mapped_key) {
            write_event(mapped_key);
            return 1;
        }
        
        write_event(&alt_down);
        write_event(&syn);
        usleep(20000);
    } else if (equal(&state->input, &alt_down)) {
        state->alt_is_down = 1;
        return 1;
    }
    
    
    return 0;
}
