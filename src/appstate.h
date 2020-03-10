#pragma once

#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdlib.h>

#define IGNORE_LIST_SIZE 20

const struct input_event
        esc_up   = {.type = EV_KEY, .code = KEY_ESC, .value = 0},
        ctrl_up  = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 0},
        alt_up   = {.type = EV_KEY, .code = KEY_LEFTALT, .value = 0},
        shift_up = {.type = EV_KEY, .code = KEY_LEFTSHIFT, .value = 0},
        meta_up  = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 0},
        
        capslock_up     = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 0},
        esc_down        = {.type = EV_KEY, .code = KEY_ESC, .value = 1},
        ctrl_down       = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 1},
        alt_down        = {.type = EV_KEY, .code = KEY_LEFTALT, .value = 1},
        alt_repeat      = {.type = EV_KEY, .code = KEY_LEFTALT, .value = 2},
        shift_down      = {.type = EV_KEY, .code = KEY_LEFTSHIFT, .value = 1},
        meta_down       = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 1},
        capslock_down   = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 1},
        esc_repeat      = {.type = EV_KEY, .code = KEY_ESC, .value = 2},
        ctrl_repeat     = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 2},
        capslock_repeat = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 2},
        
        wheel_up       = {.type = EV_REL, .code = REL_WHEEL, .value = 1},
        wheel_down       = {.type = EV_REL, .code = REL_WHEEL, .value = -1},
        
        tab_up     = {.type = EV_KEY, .code = KEY_TAB, .value = 0},
        tab_down   = {.type = EV_KEY, .code = KEY_TAB, .value = 1},
        tab_repeat = {.type = EV_KEY, .code = KEY_TAB, .value = 2},
        
        F8_up   = {.type = EV_KEY, .code = KEY_F8, .value = 0},
        F8_down = {.type = EV_KEY, .code = KEY_F8, .value = 1},
        
        h_up   = {.type = EV_KEY, .code = KEY_H, .value = 0},
        h_down = {.type = EV_KEY, .code = KEY_H, .value = 1},
        h_repeat = {.type = EV_KEY, .code = KEY_H, .value = 2},
        j_up   = {.type = EV_KEY, .code = KEY_J, .value = 0},
        j_down = {.type = EV_KEY, .code = KEY_J, .value = 1},
        j_repeat = {.type = EV_KEY, .code = KEY_J, .value = 2},
        k_up   = {.type = EV_KEY, .code = KEY_K, .value = 0},
        k_down = {.type = EV_KEY, .code = KEY_K, .value = 1},
        k_repeat = {.type = EV_KEY, .code = KEY_K, .value = 2},
        l_up   = {.type = EV_KEY, .code = KEY_L, .value = 0},
        l_down = {.type = EV_KEY, .code = KEY_L, .value = 1},
        l_repeat = {.type = EV_KEY, .code = KEY_L, .value = 2},
        
        arrow_up_up = {.type = EV_KEY, .code = KEY_UP, .value = 0},
        arrow_up_down = {.type = EV_KEY, .code = KEY_UP, .value = 1},
        arrow_up_repeat = {.type = EV_KEY, .code = KEY_UP, .value = 2},
        arrow_down_up = {.type = EV_KEY, .code = KEY_DOWN, .value = 0},
        arrow_down_down = {.type = EV_KEY, .code = KEY_DOWN, .value = 1},
        arrow_down_repeat = {.type = EV_KEY, .code = KEY_DOWN, .value = 2},
        arrow_left_up = {.type = EV_KEY, .code = KEY_LEFT, .value = 0},
        arrow_left_down = {.type = EV_KEY, .code = KEY_LEFT, .value = 1},
        arrow_left_repeat = {.type = EV_KEY, .code = KEY_LEFT, .value = 2},
        arrow_right_up = {.type = EV_KEY, .code = KEY_RIGHT, .value = 0},
        arrow_right_repeat = {.type = EV_KEY, .code = KEY_RIGHT, .value = 2},
        arrow_right_down = {.type = EV_KEY, .code = KEY_RIGHT, .value = 1},
        
        right_alt_up     = {.type = EV_KEY, .code = KEY_RIGHTALT, .value = 0},
        right_alt_down   = {.type = EV_KEY, .code = KEY_RIGHTALT, .value = 1},
        right_alt_repeat = {.type = EV_KEY, .code = KEY_RIGHTALT, .value = 2},
        
        space_up     = {.type = EV_KEY, .code = KEY_SPACE, .value = 0},
        space_down   = {.type = EV_KEY, .code = KEY_SPACE, .value = 1},
        space_repeat = {.type = EV_KEY, .code = KEY_SPACE, .value = 2},
        
        syn = {.type = EV_SYN, .code = SYN_REPORT, .value = 0};


struct appstate {
    int                capslock_is_down;
    int                tab_is_down;
    int                control_is_down;
    int                shift_is_down;
    int                meta_is_down;
    int                alt_is_down;
    int                right_alt_is_down;
    
    int                script_is_paused;
    
    struct input_event input;
    
    int ignore_list[IGNORE_LIST_SIZE];
    int ignore_list_index;
};

int equal(const struct input_event *first, const struct input_event *second) {
    return first->type == second->type && first->code == second->code &&
           first->value == second->value;
}

int read_event(struct input_event *event) {
    return fread(event, sizeof(struct input_event), 1, stdin) == 1;
}

void write_event(const struct input_event *event) {
    if (fwrite(event, sizeof(struct input_event), 1, stdout) != 1)
        exit(EXIT_FAILURE);
}

int is_modifier_down(struct appstate *state) {
    return state->alt_is_down || state->control_is_down || state->shift_is_down || state->meta_is_down;
}

int unblacklist_key(struct appstate *state, int keycode) {
    int      key_pos = -1;
    for (int i       = 0; i <= state->ignore_list_index; i++)
        if (state->ignore_list[i] == keycode) {
            key_pos = i;
            break;
        }
    
    if (key_pos == -1) return 2;
    
    for (int i = key_pos; i < state->ignore_list_index; i++)
        state->ignore_list[i] = state->ignore_list[i + 1];
    
    --state->ignore_list_index;
    
    return 0;
}

int blacklist_contains_key(struct appstate *state, int keycode) {
    for (int i = 0; i <= state->ignore_list_index; i++)
        if (state->ignore_list[i] == keycode)
            return 1;
    
    return 0;
}

void blacklist_key(struct appstate *state, int keycode) {
    if(blacklist_contains_key(state, keycode)) return;
    
    state->ignore_list[++state->ignore_list_index] = keycode;
}



