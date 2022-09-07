/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef DYN_STRINGS_H
#define DYN_STRINGS_H

// Count DOES include the null terminator

typedef struct
{
	int count;
	int size;
	char * data;
} String;

String * string_new();
String * string_create_from( const char * from );

void string_del( String ** s );

const char * string_get( String * s );
void string_add( String * s, const char * from );
void string_set( String * s, const char * from );

void string_sub_beg( String * s, const int to );
void string_sub_end( String * s, const int from );

int string_len( String * s );

void string_clr( String * s );

#endif // DYN_STRINGS_H