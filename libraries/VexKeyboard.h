#ifndef _VEXKEYBOARD_H_
#define _VEXKEYBOARD_H_

#ifndef VEXKEYBOARD_REPORT_ID
#define VEXKEYBOARD_REPORT_ID	0x01
#endif // VEXKEYBOARD_REPORT_ID

#define VEXKEYBOARD_NKRO

class VexKeyboard {
public:
	VexKeyboard();
	~VexKeyboard();
	void set(uint8_t key, bool on);
	void clear();
	void send();
private:
	bool m_change;
	uint8_t m_keys[1+14+1]; // 0xE0-0xE7, 0x04-0x73, 0x85-0x8C
};

#endif // _VEXKEYBOARD_H_
