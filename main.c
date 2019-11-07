#include 	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>
#include 	"data.h"


int main (int argc, char * argv[])
{
	data * array_data=NULL;
	FILE * file;
	int number_column_double_file ;
	int number_line_file;
	int *array_data_index;
	
	/***********************************************/
	//allocate memory for array data and it's index
	/**********************************************/
	file = fopen ("iris.data","r");
	number_line_file =	count_number_line_file(file);
	fseek(file,0, SEEK_SET);
	number_column_double_file = count_number_column_file(file)-1;
	//printf("line :%d\t column : %d ",number_line_file,number_column_double_file);
	fclose(file);
	array_data = malloc(number_line_file*sizeof(data));
	array_data_index	=	malloc(number_line_file*sizeof(int));

	for(int i =0;i<number_line_file;i++)
	{
		array_data_index[i]=i;
		array_data[i].vector = malloc(number_column_double_file*sizeof(double));
		array_data[i].name =	malloc(30*sizeof(char));
		array_data[i].norm = 0.0;
	}

	/******************** Parsing ***********************/
	parser(array_data);

	/******************* printing stuf ******************/
	for(int i=0;i<150;i++)
	{
		print_data (&array_data[i], number_column_double_file);
	}
	printf("\n\nShuffled : \n\n");

	shuffle_array(array_data_index,number_line_file);
	for(int i=0;i<number_line_file;i++)
	{
		print_data (&array_data[array_data_index[i]], number_column_double_file);

	}

	return 0;
}