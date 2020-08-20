#ifndef NEURON_H
#define NEURON_H

#include 	<stdlib.h>
#include 	<float.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>
#include 	<math.h>
#include	"data.h"

typedef struct neuron
{
	double * vector;
	char * ticket;
	double activation;
}neuron;

typedef struct neuralNetwork
{
	int number_line_network;
	int number_column_network;
	double alpha; // coef d'apprentissage
	int r_voisinage;// not yet done
	int total_of_iteration;
}neuralNetwork;

typedef struct bestMatchUnit
{
	double activation;
	int bmu_line;
	int bmu_column;
	struct bestMatchUnit *next;
}bmu;

double random_double(double highest,double lowest);
void voisinage (data *array_data,int array_data_index, neuron ** neural_network,neuralNetwork network_conf,int * line_column_bmu,fileConf file_conf,int this_iteration,double alpha_t);
double euclidean_distance(double * vector_1, double * vector_2, int number_column_double_file);
void learning_machine(data * array_data,int *array_data_index,neuron ** neural_network,neuralNetwork  network_conf,fileConf file_conf,int this_iteration);
void print_neuron(neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf);
void init_neural_network(neuron ** neural_network,neuralNetwork network_conf,fileConf  file_conf);
void delete_bmu_chaine(bmu ** bmu_chaine);
int double_equal_double(double a, double b);
int * best_match_unit(data * array_data,neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf);
int * best_match_unit2(data * array_data,neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf);
void print_ticket_neuron(neuron ** neural_network,neuralNetwork network_conf);
void ticketing_neural_network(data * array_data,neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf);
/* best _match unit return the line and column of the winner neuron in a table of size 2*/
#endif