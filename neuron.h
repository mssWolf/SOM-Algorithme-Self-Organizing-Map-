#ifndef NEURON_H
#define NEURON_H

#include 	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include 	<time.h>
#include 	<math.h>
#include	"data.h"

typedef struct neuron
{
	double * vector;
	char * etiq;
	int activation;
}neuron;

typedef struct neuralNetwork
{
	int number_line_network;
	int number_column_network;
}neuralNetwork;

double random_double(double highest,double lowest);
void print_neuron(neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf);
void init_neural_network(neuron ** neural_network,neuralNetwork network_conf,fileConf  file_conf);
#endif