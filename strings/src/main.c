/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.

*/

#include <stdio.h>

#include "../include/dyn_strings.h"

int main()
{
	String * str = string_new();
	printf( "String: %s, len: %d\n", string_get( str ), string_len( str ) );
	string_add( str, "lol" );
	printf( "String: %s, len: %d\n", string_get( str ), str->size );
	string_sub_beg( str, 0 );
	printf( "String: %s, len: %d\n", string_get( str ), string_len( str ) );
	string_sub_end( str, 3 );
	printf( "String: %s, len: %d\n", string_get( str ), string_len( str ) );
	string_sub_beg( str, 1 );
	printf( "String: %s, len: %d\n", string_get( str ), string_len( str ) );
	string_sub_end( str, 1 );
	printf( "String: %s, len: %d\n", string_get( str ), string_len( str ) );
	return 0;
}