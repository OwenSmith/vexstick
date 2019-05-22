#include "VexMatrix.h"

VexMatrix::VexMatrix(uint8_t numrows, uint8_t numcols, const uint8_t *rows, const uint8_t *cols)
{
	m_num_rows = numrows;
	m_num_cols = numcols;
	m_rows = rows;
	m_cols = cols;
}
VexMatrix::~VexMatrix()
{}
void VexMatrix::begin()
{
	for (uint8_t i = 0; i < sizeof(m_val)/sizeof(m_val[0]); ++i)
		m_val[i] = 0;
	for (uint8_t i = 0; i < m_num_rows; ++i)
		pinMode(m_rows[i], INPUT);
	for (uint8_t i = 0; i < m_num_cols; ++i)
		pinMode(m_cols[i], INPUT);
}
void VexMatrix::update()
{
	for (uint8_t c = 0; c < m_num_cols; ++c) {
		pinMode(m_cols[c], OUTPUT);
		digitalWrite(m_cols[c], LOW);

		m_val[c] = 0;
		for (uint8_t r = 0; r < m_num_rows; ++r) {
			pinMode(m_rows[r], INPUT_PULLUP);
			if (digitalRead(m_rows[r]) == LOW)
				m_val[c] |= (1 << r);
			pinMode(m_rows[r], INPUT);
		}

		pinMode(m_cols[c], INPUT);
	}
}
uint8_t VexMatrix::get(uint8_t idx)
{
	if (idx >= m_num_cols)
		return 0;
	return m_val[idx];
}
