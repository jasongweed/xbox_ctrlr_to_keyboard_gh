#include "ctrlr_to_keyboard_cpplib.h"
#include <stdio.h>
#include <Windows.h>


//global var for controller state
XINPUT_STATE ctr_state = { 0 };

int main() {

	while (true) {
		Sleep(500);
		manage_xbox_inputs_and_send_keys(ctr_state);
	}
	return 0;
}