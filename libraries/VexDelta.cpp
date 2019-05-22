#include "VexDelta.h"

VexDelta::VexDelta()
{
	m_val[0] = m_val[1] = m_val[2] = 2048;
}
VexDelta::~VexDelta()
{}
void VexDelta::update(uint16_t a1, uint16_t a2, uint16_t a3)
{
}
uint16_t VexDelta::get(uint8_t idx)
{
	if (idx > 2)
		return 2048;
	return m_val[idx];
}
