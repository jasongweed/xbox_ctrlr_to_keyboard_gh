#include <Windows.h>
#include <iostream>
#include <xinput.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "XInput.lib")

using namespace std;

//declarations

void manage_xbox_inputs_and_send_keys(bool _go_fast_bool);
bool detect_reverse();
bool detect_neutral();
void send_input_to_accelerate(INPUT i);
void stop_input_to_accelerate(INPUT input_key);
void get_xbox_input(); //updates global var belowi

//global var for controller state
XINPUT_STATE ctr_state;

void manage_xbox_inputs_and_send_keys(bool _cycling_fast_bool) {

	get_xbox_input(); //note this sets ctr_state_dword, which is a global XINPUT_STATE

	bool send_accel_input_bool = true;

	//if detect cycling input to accelerate
	if (_cycling_fast_bool) {
		//if cycling but reverse trigger also pressed, then release accel pedal
		if (detect_reverse()) {
			send_accel_input_bool = false; 
			cout << "reverse detected" << endl;
		}
		//if cycling but the neutral button/trigger also pressed, then release accel pedal
		else if (detect_neutral()) {
			send_accel_input_bool = false;
			cout << "neutral detected" << endl;
		}

		INPUT input_key= { 0 };
		//if no neutral or reverse detected, send input to accelerate to game
		if (send_accel_input_bool) {
			send_input_to_accelerate(input_key);
			cout << "acceleration unimpeded" << endl;
		}
		//otherwise release pedal in the game
		else { 
			stop_input_to_accelerate(input_key);
		}
	}
}

void get_xbox_input() {
 //here; copy code from below and return dword

	DWORD dwResult;    
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&ctr_state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &ctr_state);
		if (dwResult == ERROR_SUCCESS) {
			// Controller is connected
			cout << "Xbox Controller Detected " << endl;
			return;
		}
	}
	//if no controller connected, return 0 cast as DWORD
	return;
}

bool detect_reverse() {
	BYTE lt = ctr_state.Gamepad.bLeftTrigger;
	if(lt > 50) { //range of BYTE is 0-255
		return true;
		cout << "detected reverse" << endl;
	}
	else { return false; }
}

bool detect_neutral() {
	BYTE lt = ctr_state.Gamepad.bRightTrigger;
	if(lt > 50) { //range of BYTE is 0-255
		return true;
		cout << "detected neutral" << endl;
	}
	else { return false; }
}

void send_input_to_accelerate(INPUT _input_key) {
	_input_key.type = INPUT_KEYBOARD;
	_input_key.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	_input_key.ki.wVk = VkKeyScan('9');
	SendInput(1, &_input_key, sizeof(_input_key));
}

void stop_input_to_accelerate(INPUT _input_key) {
	_input_key.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &_input_key, sizeof(_input_key));
}



int main() {	
	std::cout << "Hello friends!";
	while (true) {
		Sleep(100);
		manage_xbox_inputs_and_send_keys(true);
	}
return 0;
}


/*
void retest_working_sendinput() {

	bool hold_down = false;
	INPUT input_key = { 0 };
	while (true) {
		Sleep(500);
		if (GetAsyncKeyState(VK_NUMPAD3)) { ///
			hold_down = true;
			input_key.type = INPUT_KEYBOARD;
			input_key.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
			input_key.ki.wVk = VkKeyScan('9');
		}
		if (GetAsyncKeyState(VK_NUMPAD4)) { ///
			hold_down = false;
			input_key.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &input_key, sizeof(input_key));
			cout << "detect press" << endl;
		}
		if (hold_down == true) {
			SendInput(1, &input_key, sizeof(input_key));
		}
	}
}
	

	while (true) {
		Sleep(1000);
		DWORD dwResult;    
		for (DWORD i=0; i< XUSER_MAX_COUNT; i++ )
		{
			XINPUT_STATE state;
			ZeroMemory( &state, sizeof(XINPUT_STATE) );

			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState( i, &state );

			if( dwResult == ERROR_SUCCESS )
			{
				// Controller is connected
				cout << "connected" << endl;
				cout << "Buttons: " << state.Gamepad.wButtons << endl;
				cout << "R trigger: ";
				cout << (char) state.Gamepad.bRightTrigger << endl;


			}
			else
			{
				// Controller is not connected
			//	cout << "not connected" << endl;
			}

			

		}
	}
*/

/*

		if (GetAsyncKeyState(VK_NUMPAD0)) { //Exit
			return 0;
		}
		if (GetAsyncKeyState(VK_NUMPAD1)) { //Mouseposition
			POINT p;
			GetCursorPos(&p);
			cout << "x-position: " << p.x << " | y.position: " << p.y << endl;
			Sleep(1000);
		}

		if (GetAsyncKeyState(VK_NUMPAD2)) { ///
			INPUT input = { 0 };
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &input, sizeof(input));
			ZeroMemory(&input, sizeof(input));
			Sleep(500);
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &input, sizeof(input));
		}
		
*/
