#include "hotkey.h"

#include "city/constants.h"
#include "game/cheats.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/system.h"
#include "graphics/screenshot.h"
#include "graphics/video.h"
#include "window/popup_dialog.h"

#include <string.h>

static struct {
    hotkeys hotkey_state;
} data;

const hotkeys *hotkey_state(void)
{
    return &data.hotkey_state;
}

void hotkey_reset_state(void)
{
    memset(&data.hotkey_state, 0, sizeof(data.hotkey_state));
}

void hotkey_character(int c, int with_ctrl, int with_alt)
{
    if (with_ctrl) {
        switch (c) {
            case 'a':
                data.hotkey_state.toggle_editor_battle_info = 1;
                break;
            case 'o':
                data.hotkey_state.load_file = 1;
                break;
            case 's':
                data.hotkey_state.save_file = 1;
                break;
        }
        return;
    }
    if (with_alt) {
        switch (c) {
            case 'x':
                data.hotkey_state.escape_pressed = 1;
                break;
            case 'k':
                game_cheat_activate();
                break;
            case 'c':
                game_cheat_money();
                break;
            case 'v':
                game_cheat_victory();
                break;
        }
        return;
    }

    switch (c) {
        case '[':
            data.hotkey_state.decrease_game_speed = 1;
            break;
        case ']':
            data.hotkey_state.increase_game_speed = 1;
            break;
        case ' ':
            data.hotkey_state.toggle_overlay = 1;
            break;
        case 'p':
            data.hotkey_state.toggle_pause = 1;
            break;
        case 'f':
            data.hotkey_state.show_overlay = OVERLAY_FIRE;
            break;
        case 'd':
            data.hotkey_state.show_overlay = OVERLAY_DAMAGE;
            break;
        case 'c':
            data.hotkey_state.show_overlay = OVERLAY_CRIME;
            break;
        case 't':
            data.hotkey_state.show_overlay = OVERLAY_PROBLEMS;
            break;
        case 'w':
            data.hotkey_state.show_overlay = OVERLAY_WATER;
            break;
        case 'l':
            data.hotkey_state.cycle_legion = 1;
            break;
        case '1':
            data.hotkey_state.show_advisor = ADVISOR_LABOR;
            break;
        case '2':
            data.hotkey_state.show_advisor = ADVISOR_MILITARY;
            break;
        case '3':
            data.hotkey_state.show_advisor = ADVISOR_IMPERIAL;
            break;
        case '4':
            data.hotkey_state.show_advisor = ADVISOR_RATINGS;
            break;
        case '5':
            data.hotkey_state.show_advisor = ADVISOR_TRADE;
            break;
        case '6':
            data.hotkey_state.show_advisor = ADVISOR_POPULATION;
            break;
        case '7':
            data.hotkey_state.show_advisor = ADVISOR_HEALTH;
            break;
        case '8':
            data.hotkey_state.show_advisor = ADVISOR_EDUCATION;
            break;
        case '9':
            data.hotkey_state.show_advisor = ADVISOR_ENTERTAINMENT;
            break;
        case '0':
            data.hotkey_state.show_advisor = ADVISOR_RELIGION;
            break;
        case '-':
            data.hotkey_state.show_advisor = ADVISOR_FINANCIAL;
            break;
        case '=':
        case '+':
            data.hotkey_state.show_advisor = ADVISOR_CHIEF;
            break;
    }
}

void hotkey_home(void)
{
    data.hotkey_state.rotate_map_left = 1;
}

void hotkey_end(void)
{
    data.hotkey_state.rotate_map_right = 1;
}

void hotkey_esc(void)
{
    data.hotkey_state.escape_pressed = 1;
}

void hotkey_page_up(void)
{
    data.hotkey_state.increase_game_speed = 1;
}

void hotkey_page_down(void)
{
    data.hotkey_state.decrease_game_speed = 1;
}

void hotkey_enter(int with_alt)
{
    if (with_alt) {
        system_set_fullscreen(!setting_fullscreen());
    } else {
        data.hotkey_state.enter_pressed = 1;
    }
}

void hotkey_func(int f_number, int with_any_modifier, int with_ctrl)
{
    switch (f_number) {
        case 1:
        case 2:
        case 3:
        case 4:
            if (with_any_modifier) {
                data.hotkey_state.set_bookmark = f_number;
            } else {
                data.hotkey_state.go_to_bookmark = f_number;
            }
            break;
        case 5: system_center(); break;
        case 6: system_set_fullscreen(!setting_fullscreen()); break;
        case 7: system_resize(640, 480); break;
        case 8: system_resize(800, 600); break;
        case 9: system_resize(1024, 768); break;
        case 12: graphics_save_screenshot(with_ctrl); break;
    }
}

static void confirm_exit(int accepted)
{
    if (accepted) {
        system_exit();
    }
}

void hotkey_handle_escape(void)
{
    video_stop();
    window_popup_dialog_show(POPUP_DIALOG_QUIT, confirm_exit, 1);
}
