#ifndef _VEXMATRIX_H_
#define _VEXMATRIX_H_

class VexMatrix {
public:
	VexMatrix(uint8_t numrows, uint8_t numcols, const uint8_t *rows, const uint8_t *cols);
	~VexMatrix();
	void begin();
	void update();
	uint8_t get(uint8_t idx);
private:
	uint8_t	m_num_rows;
	uint8_t m_num_cols;
	const uint8_t *m_rows;
	const uint8_t *m_cols;
	uint8_t m_val[5];
};

#endif // _VEXMATRIX_H_
