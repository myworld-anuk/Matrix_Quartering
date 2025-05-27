#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "Matrix.h"
#include <cassert>

int main()
{
    Matrix m11(3,4,0);
	m11.set(0,0,1);
	m11.set(0,1,2);
	m11.set(0,2,3);
	m11.set(0,3,4);

	m11.set(1,0,5);
	m11.set(1,1,6);
	m11.set(1,2,7);
	m11.set(1,3,8);

	m11.set(2,0,9);
	m11.set(2,1,10);
	m11.set(2,2,11);
	m11.set(2,3,12);

	std::cout << "M11 to be quartered: " << std::endl;
	std::cout << m11 << std::endl;

	Matrix* ma1 = NULL;
	ma1 = m11.quarter();
	assert(ma1 != NULL);

	std::cout << "UL: " << std::endl << ma1[0] << std::endl;
	std::cout << "UR: " << std::endl << ma1[1] << std::endl;
	std::cout << "LL: " << std::endl << ma1[2] << std::endl;
	std::cout << "LR: " << std::endl << ma1[3] << std::endl;

	for(unsigned int i=0; i<4; i++)
	{
		assert((ma1[i].num_rows() == 2) && (ma1[i].num_cols() == 2));
	}

    // int* p = new int[2];
    // p[0] = 1;
    // p[1] = 2;

    // //fscanf(stdin, "c");

    // std::string command = "leaks " + std::to_string(getpid());
    // system(command.c_str());

    // return 0;
}