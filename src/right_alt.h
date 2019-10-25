#include "appstate.h"

int right_alt_mod(struct appstate *state) {
    if (state->right_alt_is_down) {
        if (equal(&state->input, &right_alt_down) ||
            equal(&state->input, &right_alt_repeat))
            return 1;

        if (equal(&state->input, &right_alt_up)) {
            state->right_alt_is_down = 0;
            if (blacklist_contains_key(state, right_alt_down.code)) {
                unblacklist_key(state,right_alt_down.code);
                write_event(&alt_up);
                write_event(&meta_up);
                return 1;
            }
            write_event(&right_alt_down);
            write_event(&syn);
            usleep(20000);
            write_event(&right_alt_up);
            return 1;
        }

        // pressed right_alt + [KEY]
        if (state->input.value) {
            blacklist_key(state, right_alt_down.code);
            write_event(&alt_down);
            write_event(&meta_down);
            write_event(&syn);
            usleep(20000);
        }
    } else if (equal(&state->input, &right_alt_down)) {
        state->right_alt_is_down = 1;
        return 1;
    }
    
    
    return 0;
}
