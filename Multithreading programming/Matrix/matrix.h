#include <cstdint>
#include <ctime>
#include <iostream>
#include <chrono>

using namespace std;

const int INCORRECT_INPUT_DATA = -1;

class matrix
{
public:
	const int rows_number;
	const int columns_number;
	float *container;

	matrix(int, int);
	~matrix();

	float       *operator[](int);
	float const *operator[](int) const;
	void 		init_matrix();
};

void unusial_multiplication(const matrix &, const matrix &, matrix &);
void stupid_multiplication(const matrix &, const matrix &, matrix &);
void check_correctness(const matrix &, const matrix &, matrix &);
