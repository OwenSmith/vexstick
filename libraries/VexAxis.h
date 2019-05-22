#ifndef _VEXAXIS_H_
#define _VEXAXIS_H_

class VexAxis {
public:
	VexAxis();
	~VexAxis();
	void calibrate(uint16_t val);
	void begin();
	void update(uint16_t val);
	uint16_t get();
private:
	uint16_t m_val;
	uint16_t m_cal[4];
}

#endif // _VEXAXIS_H_
