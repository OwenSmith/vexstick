#ifndef _VEXJOYSTICK_H_
#define _VEXJOYSTICK_H_

#ifndef VEXJOYSTICK_REPORT_ID
#define VEXJOYSTICK_REPORT_ID	0x01
#endif // VEXJOYSTICK_REPORT_ID

#define VEXJOYSTICK_NUM_AXES	3
#define VEXJOYSTICK_NUM_BTNS	16

class VexJoystick {
public:
	VexJoystick();
	~VexJoystick();
	void axis(uint8_t idx, uint16_t val);
	void btns(uint8_t idx, uint8_t val);
	void pov(uint8_t val);
	void send();
private:
	bool m_change;
	uint16_t m_axis[VEXJOYSTICK_NUM_AXES];
	uint8_t m_btns[(VEXJOYSTICK_NUM_BTNS + 7) / 8];
	uint8_t m_pov;
};

#endif // _VEXJOYSTICK_H_
