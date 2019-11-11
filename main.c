#include 	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>
#include 	"data.h"


int main (int argc, char * argv[])
{
	data * array_data=NULL;
	FILE * file;
	fileConf file_conf;
	int *array_data_index;
	
	/***********************************************/
	//allocate memory for array data and it's index
	/**********************************************/
	file = fopen ("iris.data","r");
	file_conf.number_line_file =	count_number_line_file(file);
	fseek(file,0, SEEK_SET);
	file_conf.number_column_double_file = count_number_column_file(file)-1;
	//printf("line :%d\t column : %d ",number_line_file,number_column_double_file);
	fclose(file);
	array_data = malloc(file_conf.number_line_file*sizeof(data));
	array_data_index	=	malloc(file_conf.number_line_file*sizeof(int));
	file_conf.vector	=	malloc(file_conf.number_column_double_file*sizeof(double));

	for(int i =0 ;i<file_conf.number_column_double_file;i++)
		file_conf.vector[i]=0.0;

	for(int i =0;i<file_conf.number_line_file;i++)
	{
		array_data_index[i]=i;
		array_data[i].vector = malloc(file_conf.number_column_double_file*sizeof(double));
		array_data[i].name =	malloc(50*sizeof(char));
		array_data[i].norm = 0.0;
	}

	/******************** Parsing ***********************/
	parser(array_data,&file_conf);

	/******************* printing stuf ******************/
	for(int i=0;i<150;i++)
	{
		print_data (&array_data[i], file_conf.number_column_double_file);
	}
	printf("\n\nShuffled : \n\n");

	shuffle_array(array_data_index,file_conf.number_line_file);
	for(int i=0;i<file_conf.number_line_file;i++)
	{
		print_data (&array_data[array_data_index[i]], file_conf.number_column_double_file);
	}

	for(int i=0;i<file_conf.number_column_double_file;i++)
		printf("%lf\t",file_conf.vector[i]);
	printf("%lf\t Iris-average\n",file_conf.norm);


	/************fre the data i've being allocating**************/
	for(int i=0;i<file_conf.number_line_file;i++)
	{
		free(array_data[i].vector);
		free(array_data[i].name);
	}

	free(array_data);
	free(file_conf.vector);
	return 0;
}