/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unicode/ustdio.h>

#include "../include/colors.h"

#include "../include/display.h"

bool is_color_enabled = true;

bool get_color_enabled()
{
	return is_color_enabled;
}

void set_color_enabled( bool is_enabled )
{
	is_color_enabled = is_enabled;
}

void disp_common( FILE * file, bool use_unicode, const char * fmt, ... )
{
	char * res_str = ( char * )malloc( sizeof( char ) * MAX_STR_SIZE );
	size_t res_ctr = 0;

	va_list args;
	va_start( args, fmt );

	while( * fmt != '\0' ) {
		if( * fmt == '{' && *( fmt + 1 ) != '\0' ) {
			++fmt;
			if( * fmt == '{' ) {
				res_str[ res_ctr++ ] = * fmt;
				++fmt;
				continue;
			}
			char tmp[ 10 ];
			uint8_t tmp_ctr = 0;
			while( * fmt != '\0' && * fmt != '}' ) {
				tmp[ tmp_ctr++ ] = * fmt++;
			}
			if( * fmt == '\0' ) continue;
			++fmt;
			if( !get_color_enabled() ) continue;
			if( tmp_ctr >= 10 ) tmp_ctr = 9;
			tmp[ tmp_ctr ] = '\0';
			const char * tmp_res = get_color( tmp );
			// invalid color
			if( strcmp( tmp_res, "0" ) == 0 ) continue;
			res_str[ res_ctr ] = '\0';
			strcat( res_str, tmp_res );
			// no + 1 because the return value is length and we use it as index so we need to - 1 it anyway
			res_ctr = strlen( res_str );
			continue;
		}

		res_str[ res_ctr++ ] = * fmt++;
	}
	if( res_str[ res_ctr ] != '\0' ) res_str[ res_ctr++ ] = '\0';

	if( use_unicode ) {
		UFILE * ufile = u_finit( file, NULL, NULL );
		u_vfprintf( ufile, res_str, args );
		u_fclose( ufile );
	}
	else {
		vfprintf( file, res_str, args );
	}

	va_end( args );
	free( res_str );
}
