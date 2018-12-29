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
} Vec;

Vec * vec_create( int data_size );
void vec_delete( Vec ** v );

void vec_add( Vec * v, const void * data );

void * vec_get_data( const Vec * v, int loc );
void * vec_get_data_copy( const Vec * v, int loc );

int vec_count( const Vec * v );

void vec_del_at( Vec * v, int loc );

void vec_clear( const Vec * v );

void vec_sort( Vec * v, int ( * sorter )( const void * a, const void * b ) );

#endif // VECTORS_H
