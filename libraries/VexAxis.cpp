#include "VexAxis.h"

VexAxis::VexAxis()
{
	m_cal[0] = m_cal[1] = m_cal[2] = m_cal[3] = 16384;
	m_val = 2048;
}
VexAxis::~VexAxis()
{}
void VexAxis::calibrate(uint16_t val)
{
	if (val < m_cal[1])
		m_cal[1] = val;
	if (val > m_cal[2])
		m_cal[2] = val;
}
void VexAxis::begin()
{
	m_cal[0] = m_cal[1] - 4;
	m_cal[3] = m_cal[2] + 4;
}
void VexAxis::update(uint16_t val)
{
	if (val < m_cal[0])
		m_cal[0] = val;
	if (val > m_cal[3])
		m_cal[3] = val;

	if (val < m_cal[1])
		m_val = map(val, m_cal[0], m_cal[1], 0, 2048);
	else if (val > m_cal[2])
		m_val = map(val, m_cal[2], m_cal[3], 2048, 4095);
	else
		m_val = 2048;
}
uint16_t VexAxis::get()
{
	return m_val;
}
