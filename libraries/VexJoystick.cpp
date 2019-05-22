#include "VexJoystick.h"

static const uint8_t POV_BITS2VAL[16] PROGMEM = {
	0, 1, 3, 2, // 0b----, 0b---N, 0b--E-, 0b--EN
	5, 0, 4, 0, // 0b-S--, 0b-S-N, 0b-SE-, 0b-SEN,
	7, 8, 0, 0, // 0bW---, 0bW--N, 0bW-E-, 0bW-EN,
	6, 0, 0, 0  // 0bWS--, 0bWS-N, 0bWSE-, 0bWSEN
};
static const uint8_t VEXJOYSTICK_REPORT_DESCR[] PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,                    // USAGE (Joystick)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, VEXJOYSTICK_REPORT_ID,   //   REPORT_ID (VEXJOYSTICK_REPORT_ID)

    0x09, 0x30,                    //   USAGE (X)
    0x09, 0x31,                    //   USAGE (Y)
    0x09, 0x32,                    //   USAGE (Z)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x0f,              //   LOGICAL_MAXIMUM (4095)
    0x75, 0x0c,                    //   REPORT_SIZE (12)
    0x95, 0x03,                    //   REPORT_COUNT (3)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)

    0x09, 0x39,                    //   USAGE (POV)
    0x15, 0x01,                    //   LOGICAL_MINIMUM (1)
    0x25, 0x08,                    //   LOGICAL_MAXIMUM (8)
    0x75, 0x04,                    //   REPORT_SIZE (4)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)

    0x05, 0x09,                    //   USAGE_PAGE (Button)
    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
    0x29, 0x10,                    //   USAGE_MAXIMUM (Button 16)
    0x95, 0x02,                    //   REPORT_COUNT (16)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x81, 0x02,                    //   Input (Data, Variable, Absolute)

    0xc0                           // END_COLLECTION
};

VexJoystick::VexJoystick()
{
	static HIDSubDescriptor node(VEXJOYSTICK_REPORT_DESCR, sizeof(VEXJOYSTICK_REPORT_DESCR));
	HID().AppendDescriptor(&node);

	m_axis[0] = m_axis[1] = m_axis[2] = 2048;
	m_btns[0] = m_btns[1] = m_btns[2] = m_btns[3] = 0;
	m_pov = 0;
}
VexJoystick::~VexJoystick()
{}
void VexJoystick::axis(uint8_t idx, uint16_t val)
{
	if (idx > 2)
		return;
	if (val = m_axis[idx])
		return;
	m_axis[idx] = val;
	m_changed = true;
}
void VexJoystick::btns(uint8_t idx, uint8_t val)
{
	if (idx > 3)
		return;
	if (val == m_btns[idx])
		return;
	m_btns[idx] = val;
	m_changed = true;
}
void VexJoystick::pov(uint8_t val)
{
	if (val > sizeof(POV_BITS2VAL)/sizeof(POV_BITS2VAL[0]))
		return;
	val = POV_BITS2VAL[val];
	if (val == m_pov)
		return;
	m_pov = val;
	m_chnaged = true;
}
void VexJoystick::send()
{
	if (!m_changed)
		return;
	m_changed = false;

	uint8_t report[] = {
		  m_axis[0] & 0x0FF,
		((m_axis[0] & 0xF00) >> 8) | ((m_axis[1] & 0x00F) << 4),
		((m_axis[1] & 0xFF0) >> 4),
		  m_axis[2] & 0x0FF,
		((m_axis[2] & 0xF00) >> 8) | (m_pov << 4),
		  m_btns[0],
		  m_btns[1]
	};
	HID().SendReport(VEXJOYSTICK_REPORT_ID, report, sizeof(report));
}
