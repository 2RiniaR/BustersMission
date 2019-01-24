#pragma once

//----------------------------------------------------------
// KEY_INFO ƒNƒ‰ƒX
//----------------------------------------------------------
class KEY_INFO {

private:
	int Key[256];
	int JoypadAmount;

public:
	int Ax;
	int Ay;
	int UpdateKey();
	int GetJoypadAmount() { return JoypadAmount; }
	int GetKeyStatus(int KeyCode) { return Key[KeyCode]; };

};
