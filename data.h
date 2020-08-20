#ifndef DATA_H
#define DATA_H

#include 	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>
#include 	<math.h>


typedef struct data
{
	double * vector;
	char * name;
	double norm;
}data;
typedef	struct fileConf
{
	int number_line_file;
	int number_column_double_file;
	double * vector;// average vector of the database vectors
}fileConf;

int count_number_column_file(FILE * file);
int count_number_line_file(FILE * file);
//void init_data_value(data * data_value,int number_column_double_file);
//void init_data_array(data * array_data,int number_column_double_file,int number_line_file);
double calcul_norm (double * vector,int number_column_double_file);
void vector_normalisation(data * data_value,int number_column_double_file);
void print_data (data * data_value, int number_column_double_file);
void shuffle_array(int * data_array_index,int number_line_file);
void parser (data * array_data,fileConf * file_conf);
#endif