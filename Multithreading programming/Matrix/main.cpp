#include "matrix.h"

int main()
{
	matrix  first 		 (1024, 1024);
	matrix  second 		 (1024, 1024);
	matrix 	result_matrix(1024, 1024);

	first.init_matrix ();
	second.init_matrix();

	stupid_multiplication(first, second, result_matrix);
	unusial_multiplication(first, second, result_matrix);

	return 0;
}