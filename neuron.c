#include	"neuron.h"


#define HIGHEST (0.05)
#define LOWEST (-0.05)
double random_double(double highest,double lowest)
{
	return ((double)rand()*(highest-lowest))/(double)RAND_MAX+lowest;
}

void print_neuron(neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf)
{
	for (int i=0;i<network_conf.number_line_network;i++)
		{
			for(int j=0;j<network_conf.number_column_network;j++)
				{
					for(int k=0;k<file_conf.number_column_double_file;k++)
						printf("|%f|", neural_network[i][j].vector[k]);
					printf("\t");
				}
			printf("\n");
	}
}

void init_neural_network(neuron ** neural_network,neuralNetwork network_conf,fileConf  file_conf)
{
	for (int i=0;i<network_conf.number_line_network;i++)
		{
			for(int j=0;j<network_conf.number_column_network;j++)
				{
					for(int k=0;k<file_conf.number_column_double_file;k++)
						neural_network[i][j].vector[k]	=	file_conf.vector[k]+random_double(HIGHEST,LOWEST);
				}
	}
}

