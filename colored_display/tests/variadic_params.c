/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <stdio.h>

#include "../include/display.h"

int main()
{
	size_t max_st = ~0;
	uint64_t max_ui64 = -1;
	disp_test( "Variadic: %s, %c, %d, %f, %zu, %llu\n", "str", 'c', 10, 12.4, max_st, max_ui64 );
	return 0;
}
