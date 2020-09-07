#pragma once
#include <Windows.h>
#include <iostream>
#include <xinput.h>
#include <stdio.h>
#include <stdlib.h>

void manage_xbox_inputs_and_send_keys(XINPUT_STATE ctr_state);
bool detect_LT(XINPUT_STATE * ctr_state);
bool detect_RT(XINPUT_STATE * ctr_state);
void send_input_to_press_keyboard_num2(INPUT i);
void stop_input_to_press_keybard_num2(INPUT input_key);
void get_xbox_input(XINPUT_STATE * ctr_state); //updates global var


