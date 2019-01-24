#include "DxLib.h"
#include "key.h"
#include "sceneMGR.h"

int KEY_INFO::UpdateKey() {

	char tmpKey[256];
	int PadInput;

	JoypadAmount = GetJoypadNum();

	if (JoypadAmount == 0) {

		GetHitKeyStateAll(tmpKey);

		for (int i = 0; i < 256; i++) {

			if (tmpKey[i] != 0) {
				Key[i]++;
			}

			else {
				Key[i] = 0;
			}

		}
	}
	else {


		PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		if ((PadInput & PAD_INPUT_1) != 0) {

			Key[KEY_INPUT_Z]++;

		}
		else {

			Key[KEY_INPUT_Z] = 0;

		}

		if ((PadInput & PAD_INPUT_7) != 0) {

			Key[KEY_INPUT_M]++;

		}
		else {

			Key[KEY_INPUT_M] = 0;

		}

		GetJoypadAnalogInput(&Ax, &Ay, DX_INPUT_PAD1);

		if (Ax > 400) {

			Key[KEY_INPUT_RIGHT]++;

		}
		else {

			Key[KEY_INPUT_RIGHT] = 0;

		}

		if (Ax < -400) {

			Key[KEY_INPUT_LEFT]++;

		}
		else {

			Key[KEY_INPUT_LEFT] = 0;

		}

		if (Ay > 400) {

			Key[KEY_INPUT_DOWN]++;

		}
		else {

			Key[KEY_INPUT_DOWN] = 0;

		}

		if (Ay < -400) {

			Key[KEY_INPUT_UP]++;

		}
		else {

			Key[KEY_INPUT_UP] = 0;

		}

	}
	
	return 0;

}
