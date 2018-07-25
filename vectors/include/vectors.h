/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef VECTORS_H
#define VECTORS_H

typedef struct
{
	int count;
	int size;
	int data_size;
	void ** data;
} Vector;

Vector * vec_create( int data_size );
void vec_delete( Vector ** v );

void vec_add( Vector * v, const void * data );

void * vec_get_data( Vector * v, int loc );
void * vec_get_data_copy( Vector * v, int loc );

void vec_del_at( Vector * v, int loc );

void vec_clear( Vector * v );

#endif // VECTORS_H
