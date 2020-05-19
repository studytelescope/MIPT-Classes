#include "matrix.h"

matrix::matrix(int rows, int columns) :
		rows_number(rows),
		columns_number(columns)
	{
		container = new float[rows_number * columns_number];
	}

matrix::~matrix()
{
	free(container);
}

void matrix::init_matrix()
{
	srand(time(NULL));
	for (uint32_t i = 0; i < rows_number * columns_number; ++i)
		container[i] = rand() * 1.0;
}

float* matrix::operator[](int row)
{
	return &container[columns_number * row];
}

float const * matrix::operator[](int row) const
{
	return &container[columns_number * row];
}

void check_correctness(const matrix &m1, const matrix &m2, matrix &res)
{
	if(m1.columns_number != m2.rows_number || m1.rows_number != m2.columns_number)
		exit(INCORRECT_INPUT_DATA);

	if(res.rows_number != m1.rows_number ||res.columns_number != m2.columns_number)
		exit(INCORRECT_INPUT_DATA);
}

void stupid_multiplication(const matrix &m1, const matrix &m2, matrix &res)
{
	check_correctness(m1, m2, res);
	cout << "stupid multiplication" << endl;

	auto start  = chrono::system_clock::now();	

	for (uint32_t i = 0; i < res.rows_number; ++i)
	{
		for (uint32_t k = 0; k < res.columns_number; ++k)
		{
			res[i][k] = 0;
			for (uint32_t n = 0; n < m1.columns_number; ++n)
				res[i][k] += m1[i][n] * m2[n][k];
		}
	}

	auto finish = chrono::system_clock::now();			
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);		
	cout << "simple method: " << result.count() << "ms\n";
}

void unusial_multiplication(const matrix &m1, const matrix &m2, matrix &res)
{
	check_correctness(m1, m2, res);
	cout << "multiplication by blocks" << endl;

	auto start  = chrono::system_clock::now();	

	for (uint32_t i = 0; i < res.rows_number; ++i)
	{
		for (uint32_t n = 0; n < res.columns_number; ++n)
			res[i][n] = 0;
		for (uint32_t k = 0; k < m2.rows_number; ++k)
		{
			for (uint32_t n = 0; n < res.columns_number; ++n)
				res[i][n] += m1[i][n] * m2[k][n];
		}
	}

	auto finish = chrono::system_clock::now();			
	auto result = chrono::duration_cast<chrono::milliseconds>(finish - start);		
	cout << "method from wiki: " << result.count() << "ms\n";
}
