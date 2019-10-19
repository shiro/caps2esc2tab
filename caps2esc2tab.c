#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>
#include <linux/input.h>

// clang-format off
const struct input_event
        esc_up = {.type = EV_KEY, .code = KEY_ESC, .value = 0},
        ctrl_up = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 0},
        alt_up = {.type = EV_KEY, .code = KEY_LEFTALT, .value = 0},
        shift_up = {.type = EV_KEY, .code = KEY_LEFTSHIFT, .value = 0},
        meta_up = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 0},

        capslock_up = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 0},
        esc_down = {.type = EV_KEY, .code = KEY_ESC, .value = 1},
        ctrl_down = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 1},
        alt_down = {.type = EV_KEY, .code = KEY_LEFTALT, .value = 1},
        shift_down = {.type = EV_KEY, .code = KEY_LEFTSHIFT, .value = 1},
        meta_down = {.type = EV_KEY, .code = KEY_LEFTMETA, .value = 1},
        capslock_down = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 1},
        esc_repeat = {.type = EV_KEY, .code = KEY_ESC, .value = 2},
        ctrl_repeat = {.type = EV_KEY, .code = KEY_LEFTCTRL, .value = 2},
        capslock_repeat = {.type = EV_KEY, .code = KEY_CAPSLOCK, .value = 2},

        tab_up = {.type = EV_KEY, .code = KEY_TAB, .value = 0},
        tab_down = {.type = EV_KEY, .code = KEY_TAB, .value = 1},
        tab_repeat = {.type = EV_KEY, .code = KEY_TAB, .value = 2},


        syn = {.type = EV_SYN, .code = SYN_REPORT, .value = 0};
// clang-format on


int alt_is_down = 0;
int shift_is_down = 0;
int ctrl_is_down = 0;
int meta_is_down = 0;

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

int is_modifier_down(){
    return alt_is_down || ctrl_is_down || shift_is_down || meta_is_down;
}

int main(void) {
    int capslock_is_down = 0, esc_give_up = 0;
    int tab_is_down = 0, tab_give_up = 0;


    struct input_event input;


    setbuf(stdin, NULL), setbuf(stdout, NULL);


    while (read_event(&input)) {
        if (input.type == EV_MSC && input.code == MSC_SCAN)
            continue;

        if (input.type != EV_KEY) {
            write_event(&input);
            continue;
        }

        if (equal(&input, &alt_down)) {
            alt_is_down = 1;
        } else if (equal(&input, &alt_up)) {
            alt_is_down = 0;
        }
//        if (equal(&input, &shift_down)) {
//            shift_is_down = 1;
//        } else if (equal(&input, &shift_up)) {
//            shift_is_down = 0;
//        }
//        if (equal(&input, &meta_down)) {
//            meta_is_down = 1;
//        } else if (equal(&input, &meta_up)) {
//            meta_is_down = 0;
//        }
//        if (equal(&input, &ctrl_down)) {
//            ctrl_is_down = 1;
//        } else if (equal(&input, &ctrl_up)) {
//            ctrl_is_down = 0;
//        }


        if (tab_is_down) {
            // repeat tab ignore
            if (equal(&input, &tab_down) ||
                equal(&input, &tab_repeat))
                continue;

            // handle tab up
            if (equal(&input, &tab_up)) {
                tab_is_down = 0;
                if (tab_give_up) {
                    tab_give_up = 0;
                    write_event(&alt_up);
                    write_event(&shift_up);
                    write_event(&meta_up);
                    continue;
                } write_event(&tab_down);
                write_event(&syn);
                usleep(20000);
                write_event(&tab_up);

                continue;
            }

            // handle tab + [key]
            if (input.value) {
                tab_give_up = 1;
                write_event(&alt_down);
                write_event(&shift_down);
                write_event(&meta_down);
                write_event(&syn);
                usleep(20000);
            }
        } else if (equal(&input, &tab_down) && !is_modifier_down()) {
            tab_is_down = 1;
            continue;
        }


        if (capslock_is_down) {
            if (equal(&input, &capslock_down) ||
                equal(&input, &capslock_repeat))
                continue;

            if (equal(&input, &capslock_up)) {
                capslock_is_down = 0;
                if (esc_give_up) {
                    esc_give_up = 0;
                    write_event(&ctrl_up);
                    continue;
                }
                write_event(&esc_down);
                write_event(&syn);
                usleep(20000);
                write_event(&esc_up);
                continue;
            }

            if (input.value) {
                esc_give_up = 1;
                write_event(&ctrl_down);
                write_event(&syn);
                usleep(20000);
            }
        } else if (equal(&input, &capslock_down) && !is_modifier_down()) {
            capslock_is_down = 1;
            continue;
        } else if (equal(&input, &capslock_down)){
            // handle modifier + caps_lock down
            continue;
        }else if (equal(&input, &capslock_up)){
            // handle modifier + caps_lock up
            write_event(&esc_down);
            write_event(&syn);
            usleep(20000);
            write_event(&esc_up);
            continue;
        }

        if (input.code == KEY_ESC)
            input.code = KEY_CAPSLOCK;

        write_event(&input);
    }
}
