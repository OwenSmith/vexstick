#ifndef _VEXDELTA_H_
#define _VEXDELTA_H_

class VexDelta {
public:
	VexDelta();
	~VexDelta();
	void update(uint16_t a1, uint16_t a2, uint16_t a3);
	uint16_t get(uint8_t idx);
private:
	uint16_t m_val[3];
}

#endif // _VEXDELTA_H_
