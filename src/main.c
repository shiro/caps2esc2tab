#include <stdio.h>

#include <unistd.h>
#include <linux/input.h>

#include "appstate.h"
#include "capslock.h"
#include "tab.h"
#include "alt.h"
#include "right_alt.h"


int main(void) {
    struct appstate state;
    state.ignore_list_index = -1;
    state.disable_alt_mod   = 0;
    
    setbuf(stdin, NULL), setbuf(stdout, NULL);
    
    
    while (read_event(&state.input)) {
        if (state.input.type == EV_MSC && state.input.code == MSC_SCAN)
            continue;
    
        if (equal(&state.input, &F8_down)) {
            state.disable_alt_mod = !state.disable_alt_mod;
        }
    
        // key not handled by the script
        if ( state.input.type != EV_KEY && state.input.type != EV_REL) {
            write_event(&state.input);
            continue;
        }
        
        if (equal(&state.input, &ctrl_down)) state.control_is_down = 1;
        else if (equal(&state.input, &ctrl_up)) state.control_is_down = 0;
    
        if (equal(&state.input, &shift_down)) state.shift_is_down = 1;
        else if (equal(&state.input, &shift_up)) state.shift_is_down = 0;
        
        if (equal(&state.input, &wheel_up)) {
            continue;
        }
        
        if (tab_mod(&state)) continue;
        
        if (capslock_mod(&state)) continue;

        if (!state.disable_alt_mod)
            if (alt_mod(&state)) continue;
    
        if (!state.disable_alt_mod)
            if (right_alt_mod(&state)) continue;
        
        // esc is caps lock
        if (state.input.code == KEY_ESC)
            state.input.code = KEY_CAPSLOCK;
        
        
        write_event(&state.input);
    }
}
