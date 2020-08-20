#include 	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>
#include 	"data.h"
#include	"neuron.h"

#define FLAG_TEST_DATA_ARRAY 0
#define FLAG_TEST_DATA_ARRAY_SHUFFLED 0
#define FLAG_TEST_AVERAGE_VECTOR 0
#define FLAG_RANDOM 0
#define	FLAG_TEST_INIT_NEURAL_NETWORK 0
#define FLAG_BEST_MATCH_UNIT 0
#define FLAG_LEARNING_NEURAL_NETWORK 0
#define FLAG_TEST_training_NEURAL_NETWORK 0
#define FLAG_EUCLI_DIST 0
#define flag 0


int main (int argc, char * argv[])
{
	/*data declaration*/
	data * array_data=NULL;
	FILE * file;
	fileConf file_conf;
	int *array_data_index;
	
	/*neural network declaratoin*/
	neuron ** neural_network;
	neuralNetwork network_conf;

	/***********************************************/
	//allocate memory for array data and it's index
	/**********************************************/
	file = fopen ("iris.data","r");
	file_conf.number_line_file=	count_number_line_file(file);
	fseek(file,0, SEEK_SET);
	file_conf.number_column_double_file = count_number_column_file(file)-1;
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

	/***********************************************/
	//allocate memory for the neural network and initialising the conf struct
	/**********************************************/
	network_conf.number_line_network=6;
	network_conf.number_column_network=10;
	network_conf.alpha=0.9;
	neural_network	=	(neuron**)malloc(network_conf.number_line_network*sizeof(neuron *));
	for(int i=0;i<network_conf.number_line_network;i++)
		{
			neural_network[i]	=	(neuron*)malloc(network_conf.number_column_network*sizeof(neuron));
			for(int j =0;j<network_conf.number_column_network;j++)
			{
				neural_network[i][j].vector	=	malloc(file_conf.number_column_double_file*sizeof(double));
			}
		}


	/******************** Parsing ***********************/
	parser(array_data,&file_conf);


	/******************* testing random value for the neural network **********/
	init_neural_network(neural_network,network_conf,file_conf);


	/******************* printing stuff of data ******************/
	if(FLAG_TEST_DATA_ARRAY)
	{
		printf("Data array\n");
		for(int i=0;i<file_conf.number_line_file;i++)
		{
			print_data (&array_data[i], file_conf.number_column_double_file);
		}
	}
	if(FLAG_TEST_DATA_ARRAY_SHUFFLED)
	{
		printf("\n\nShuffled Data array: \n\n");

		shuffle_array(array_data_index,file_conf.number_line_file);
		for(int i=0;i<file_conf.number_line_file;i++)
		{
			print_data (&array_data[array_data_index[i]], file_conf.number_column_double_file);
		}
	}
	if(FLAG_TEST_AVERAGE_VECTOR)
	{	
		printf("The average vector\n");
		for(int i=0;i<file_conf.number_column_double_file;i++)
			printf("%lf\t",file_conf.vector[i]);
		printf("\n");
	}
	if(FLAG_RANDOM)
	{
		for(int i =0;i<150;i++)
		printf("%lf\n",random_double(0.05,-0.05));
	}
	/******************* printing stuff of neural network ******************/
	if(FLAG_TEST_INIT_NEURAL_NETWORK)
	{
		printf ("Initialisation of the neural network :\n");
		print_neuron(neural_network,network_conf,file_conf);
	}

	/*********** printing best match unit **************************/
	if(FLAG_BEST_MATCH_UNIT)
	{
		int * line_column_bmu;
		shuffle_array(array_data_index,file_conf.number_line_file);
		printf("Choosing the winner bmu :\n");
		for(int i=0;i<file_conf.number_line_file;i++)
		{
			line_column_bmu = best_match_unit2(&array_data[array_data_index[i]],neural_network,network_conf,file_conf);
			printf("l=%d|c=%d\n",line_column_bmu[0],line_column_bmu[1]);
		}
	}

	if(FLAG_EUCLI_DIST)
	{
		int * line_column_bmu;
		for(int i=0;i<10;i++)
		{printf("-----------------------------i=%d\n\n\n",i);
			line_column_bmu = best_match_unit(&array_data[i],neural_network,network_conf,file_conf);
			printf("l=%d|c=%d\n",line_column_bmu[0],line_column_bmu[1]);
		}
	}
	/************ printinf the neural network after the learning phase before neighberhood ********/
		network_conf.total_of_iteration = 500 * file_conf.number_column_double_file;
		//network_conf.r_voisinage =3;
		//learning_machine(array_data,array_data_index,neural_network,network_conf,file_conf,0);
		/*********************** first phase of the learning curve ******************************/
	network_conf.r_voisinage =3;
		for(int i=0;i<network_conf.total_of_iteration/12;i++)
			learning_machine(array_data,array_data_index,neural_network,network_conf,file_conf,i);
		network_conf.r_voisinage =2;
		for(int i=network_conf.total_of_iteration/12;i<network_conf.total_of_iteration/8;i++)
			learning_machine(array_data,array_data_index,neural_network,network_conf,file_conf,i);
		network_conf.r_voisinage =1;
		for(int i=network_conf.total_of_iteration/8;i<network_conf.total_of_iteration/4;i++)
			learning_machine(array_data,array_data_index,neural_network,network_conf,file_conf,i);

		/****************** second phase of the learning curve *****************/
		network_conf.alpha=network_conf.alpha/10;
		for(int i=network_conf.total_of_iteration/4;i<network_conf.total_of_iteration;i++)
			learning_machine(array_data,array_data_index,neural_network,network_conf,file_conf,i);		
	
	/***************** ticketing `************************/
		ticketing_neural_network(array_data,neural_network,network_conf,file_conf);
		


	/************* print the ticket of all te neuron's in the neural network*********************/
		print_ticket_neuron(neural_network,network_conf);
	if(FLAG_TEST_INIT_NEURAL_NETWORK)
	{
		printf ("Initialisation of the neural network :\n");
		print_neuron(neural_network,network_conf,file_conf);
	}
		
	if(FLAG_LEARNING_NEURAL_NETWORK)
	{	
		printf("The neural network learning neighberhood :\n");	
		print_neuron(neural_network,network_conf,file_conf);
	}




	
	/************fre the data i've been allocating for array_data and it index**************/
	for(int i=0;i<file_conf.number_line_file;i++)
	{
		free(array_data[i].vector);
		free(array_data[i].name);
	}

	free(array_data);
	free(file_conf.vector);

	/************ free the data i've been allocating for the neural network ***************/

	for(int i=0;i<network_conf.number_line_network;i++)
	{
		for(int j=0;j<network_conf.number_column_network;j++)
			free(neural_network[i][j].vector);
		free(neural_network[i]);
	}
	free(neural_network);

	return 0;
}