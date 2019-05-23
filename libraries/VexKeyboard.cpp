#include "VexKeyboard.h"

static const uint8_t VEKEYBOARD_REPORT_DESCR[] PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x07,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, VEXKEYBOARD_REPORT_ID,   //   REPORT_ID (VEXKEYBOARD_REPORT_ID)

#ifdef VEXKEYBOARD_NKRO
    // 8 bits report[0]
    0x05, 0x07,                    //    Usage Page (Key Codes)
    0x19, 0xe0,                    //    Usage Minimum (L-Shift)
    0x29, 0xe7,                    //    Usage Maximum (R-GUI)
    0x15, 0x00,                    //    Logical Minimum (0)
    0x25, 0x01,                    //    Logical Maximum (1)
    0x75, 0x01,                    //    Report Size (1)
    0x95, 0x08,                    //    Report Count (8)
    0x81, 0x02,                    //    Input (Data, Variable, Absolute)

    // 112 bits report[1..14]
    0x19, 0x04,                    //    Usage Minimum (A)
    0x29, 0x74,                    //    Usage Maximum (F24 + 1)
    0x15, 0x00,                    //    Logical Minimum (0)
    0x25, 0x01,                    //    Logical Maximum (1)
    0x75, 0x01,                    //    Report Size (1)
    0x95, 0x70,                    //    Report Count (112)
    0x81, 0x02,                    //    Input (Data, Variable, Absolute)

    // 8 bits report[15]
    0x19, 0x85,                    //    Usage Minimum (Pad Comma)
    0x29, 0x8C,                    //    Usage Maximum (Intl6)
    0x15, 0x00,                    //    Logical Minimum (0)
    0x25, 0x01,                    //    Logical Maximum (1)
    0x75, 0x01,                    //    Report Size (1)
    0x95, 0x08,                    //    Report Count (8)
    0x81, 0x02,                    //    Input (Data, Variable, Absolute)
#else
    // 8 bits report[0]
    0x05, 0x07,                    //    Usage Page (Key Codes)
    0x19, 0xe0,                    //    Usage Minimum (L-Shift)
    0x29, 0xe7,                    //    Usage Maximum (R-GUI)
    0x15, 0x00,                    //    Logical Minimum (0)
    0x25, 0x01,                    //    Logical Maximum (1)
    0x75, 0x01,                    //    Report Size (1)
    0x95, 0x08,                    //    Report Count (8)
    0x81, 0x02,                    //    Input (Data, Variable, Absolute)

    // 8 bits padding report[1]
    0x95, 0x01,                    //    Report Count (1)
    0x75, 0x08,                    //    Report Size (8)
    0x81, 0x01,                    //    Input (Constant) reserved byte(1)

    // 6 byte array report[2..7]
    0x95, 0x06,                    //    Report Count (6)
    0x75, 0x08,                    //    Report Size (8)
    0x15, 0x00,                    //    Logical Minimum (0)
    0x25, 0x74,                    //    Logical Maximum (F24 + 1)
    0x05, 0x07,                    //    Usage Page (Key codes)
    0x19, 0x00,                    //    Usage Minimum (0)
    0x29, 0x74,                    //    Usage Maximum (F24 + 1)
    0x81, 0x00,                    //    Input (Data, Array) Key array(6 bytes)
#endif

    0xc0                           // END_COLLECTION
};

VexKeyboard::VexKeyboard()
{
	static HIDSubDescriptor node(VEKEYBOARD_REPORT_DESCR, sizeof(VEKEYBOARD_REPORT_DESCR));
	HID().AppendDescriptor(&node);

	for (int i = 0; i < sizeof(m_keys)/sizeof(m_keys[0]); ++i)
		m_keys[i] = 0;
}
VexKeyboard::~VexKeyboard()
{}
void VexKeyboard::set(uint8_t key, bool on)
{
	uint8_t idx;
	uint8_t bit;
	if (key >= 0xE0 && key <= 0xE7) {
		idx = 0;
		bit = 1 << ((key - 0xE0) % 8);
	} else if (key >= 0x04 && key <= 0x73) {
		idx = 1 + ((key - 0x04) / 8);
		bit = 1 << ((key - 0x04) % 8);
	} else if (key >= 0x85 && key <= 0x8C) {
		idx = 15;
		bit = 1 << ((key - 0x85) % 8);
	} else {
		return;
	}

	if (on) {
		if (m_keys[idx] & bit)
			return;
		m_changed = true;
		m_keys[idx] |= bit;
	} else {
		if ((m_keys[idx] & bit) == 0)
			return;
		m_changed = true;
		m_keys[idx] &= ~bit;
	}
}
void VexJoystick::clear()
{
	for (int i = 0; i < sizeof(m_keys)/sizeof(m_keys[0]); ++i) {
		if (m_keys[i] != 0)
			m_changed = true;
		m_keys[i] = 0;
	}
}
void VexJoystick::send()
{
	if (!m_changed)
		return;
	m_changed = false;

#ifdef VEXKEYBOARD_NKRO
	HID().SendReport(VEXKEYBOARD_REPORT_ID, m_keys, sizeof(m_keys));
#else
	uint8_t report[8] = {
		m_keys[0],
		0, 0, 0, 0, 0, 0, 0
	};
	uint8_t idx = 2;
	for (uint8_t i = 1; i < 14; ++i) {
		for (uint8_t j = 0; j < 8; ++j) {
			if (m_keys[i] & (1<<j))
				report[idx++] = (i * 8) + j + 0x04;
			if (idx >= 7)
				goto done;
		}
	}
done:
	HID().SendReport(VEXKEYBOARD_REPORT_ID, report, sizeof(report));
#endif
}
