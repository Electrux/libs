/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_STR_SIZE 2048

extern bool is_color_enabled;

bool get_color_enabled();
void set_color_enabled( bool is_enabled );

void disp_common( FILE * file, bool use_unicode, const char * fmt, ... );

// if we use fmt parameter explicitly here, it will cause error if there is no
// variable argument to be used ( unless we opt for the gcc extension: ##__VA_ARGS__ )
// so, instead, we just let it use fmt as a variadic argument as well
#define disp( ... ) disp_common( stdout, false, __VA_ARGS__ )
#define udisp( ... ) disp_common( stdout, true, __VA_ARGS__ )

#define disp_test( ... ) disp_common( stderr, false, __VA_ARGS__ )
#define udisp_test( ... ) disp_common( stderr, true, __VA_ARGS__ )

#endif // DISPLAY_H
