#ifndef DATA_H
#define DATA_H

#include 	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>


typedef struct data
{
	double * vector;
	char * name;
	double norm;
}data;
int count_number_column_file(FILE * file);
int count_number_line_file(FILE * file);
//void init_data_value(data * data_value,int number_column_double_file);
//void init_data_array(data * array_data,int number_column_double_file,int number_line_file);
void print_data (data * data_value, int number_column_double_file);
void shuffle_array(int * data_array_index,int number_line_file);
void parser (data * array_data);
#endif