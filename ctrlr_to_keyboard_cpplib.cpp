#include <Windows.h>
#include <iostream>
#include <xinput.h>
#include <stdio.h>
#include <stdlib.h>
#include "ctrlr_to_keyboard_cpplib.h"
#pragma comment(lib, "XInput.lib")
#pragma once

void manage_xbox_inputs_and_send_keys(XINPUT_STATE _ctr_state) {

	get_xbox_input(&_ctr_state); //note this sets ctr_state
	bool lt_pressed = false;

	//detect left trigger pressed
	if (detect_LT(&_ctr_state)) {
		std::cout << "Left trigger detected " << std::endl;
		lt_pressed = true;
	}
	//detect if right trigger pressed
	if (detect_RT(&_ctr_state)) {
		std::cout << "Right trigger detected" << std::endl;
	}

	INPUT input_key= { 0 };
	//if left trigger pressed, simulate pressing '2' on the keyboard
	if (lt_pressed) {
		send_input_to_press_keyboard_num2(input_key);
		std::cout << "Pressed 2" << std::endl;
	}
	//otherwise release the 2 button
	else { 
		stop_input_to_press_keybard_num2(input_key);
	}
}

void get_xbox_input(XINPUT_STATE * _ctr_state) {

	DWORD dwResult;    
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(_ctr_state, sizeof(XINPUT_STATE));

		// get the state of the controller from XInput.
		dwResult = XInputGetState(i, _ctr_state);
		if (dwResult == ERROR_SUCCESS) {
			// Controller is connected
			std::cout << "Xbox controller detected " << std::endl;
			return;
		}
		else {
			std::cout << "No Xbox controller detected..." << std::endl;
		}
	}
	return;
}

bool detect_LT(XINPUT_STATE * _ctr_state) {
	BYTE lt = _ctr_state->Gamepad.bLeftTrigger;
	if(lt > 50) { //range of BYTE is 0-255
		return true;
		std::cout << "detected reverse" << std::endl;
	}
	else { return false; }
}

bool detect_RT(XINPUT_STATE * _ctr_state) {
	BYTE lt = _ctr_state->Gamepad.bRightTrigger;
	if(lt > 50) { //range of BYTE is 0-255
		return true;
		std::cout << "detected neutral" << std::endl;
	}
	else { return false; }
}

void send_input_to_press_keyboard_num2(INPUT _input_key) {
	_input_key.type = INPUT_KEYBOARD;
	_input_key.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	_input_key.ki.wVk = VkKeyScan('2');
	SendInput(1, &_input_key, sizeof(_input_key));
}

void stop_input_to_press_keybard_num2(INPUT _input_key) {
	_input_key.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &_input_key, sizeof(_input_key));
}

