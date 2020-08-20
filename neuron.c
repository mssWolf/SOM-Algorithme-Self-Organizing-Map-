#include	"neuron.h"


#define HIGHEST (0.05)
#define LOWEST (-0.05)

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BLUE "\x1b[34m"
#define WHITE "\x1b[37m"

double random_double(double highest,double lowest)
{
	return ((double)rand()*(highest-lowest))/(double)RAND_MAX+lowest;
}
double euclidean_distance(double * vector_1, double * vector_2, int number_column_double_file)
{
	double tmp=0.0;
	for(int i =0; i<number_column_double_file;i++)
		{
			tmp += pow((vector_1[i]-vector_2[i]),2);
		}
	return sqrt(tmp);
}
void print_neuron(neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf)
{
	for (int i=0;i<network_conf.number_line_network;i++)
		{
			for(int j=0;j<network_conf.number_column_network;j++)
				{
					for(int k=0;k<file_conf.number_column_double_file;k++)
						printf("|%f|", neural_network[i][j].vector[k]);
					printf("\n");
				}
			printf("------------------------------------------------------\n");
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
int double_equal_double(double a, double b)
{
    return fabs(a - b) < (DBL_MIN);
}
void delete_bmu_chaine(bmu ** bmu_chaine)
{
	if(*bmu_chaine!=NULL)
	{
		bmu * head = *bmu_chaine;
		bmu * next = head->next;
		while(head!= NULL)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}
	*bmu_chaine = NULL;
}
int * best_match_unit(data * array_data,neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf)
{
	srand(time(NULL));
	/** declaration and initialising bmu */
	bmu * bmu_chaine;
	bmu *bmu_tmp;
	/* allocating memory for the bmu*/
	bmu_chaine = malloc(sizeof(bmu));
	bmu_chaine->activation=100;
	bmu_chaine->bmu_line =0;
	bmu_chaine->bmu_column=0;
	bmu_chaine->next=NULL;
	// to compare it with every neuron in the neuarl network 
	for(int j=0;j<network_conf.number_line_network;j++)
	{//printf("\n-----------j =%d\n", j);
		for(int k=0;k<network_conf.number_column_network;k++)
		{
			neural_network[j][k].activation = euclidean_distance(neural_network[j][k].vector,array_data->vector,file_conf.number_column_double_file);
			//printf("each k= %d distance =%lf\t",k,neural_network[j][k].activation);
			if(bmu_chaine->activation > neural_network[j][k].activation)
			{

				delete_bmu_chaine(&bmu_chaine);
				bmu_chaine = malloc(sizeof(bmu));
				bmu_chaine->activation = neural_network[j][k].activation;
				bmu_chaine->bmu_line =j;
				bmu_chaine->bmu_column=k;
				bmu_chaine->next=NULL;
				//printf("update k= %d distance =%lf (l=%d,k=%d) \n",k,neural_network[j][k].activation,bmu_chaine->bmu_line,bmu_chaine->bmu_column);
			}
			else if(double_equal_double(bmu_chaine->activation,neural_network[j][k].activation))
			{
				bmu_tmp = bmu_chaine;
				while(bmu_tmp->next != NULL)
					bmu_tmp = bmu_tmp->next;
				bmu_tmp->next = malloc(sizeof(bmu));
				bmu_tmp=bmu_tmp->next;
				bmu_tmp->activation = neural_network[j][k].activation;
				bmu_tmp->bmu_line =j;
				bmu_tmp->bmu_column=k;
				bmu_tmp->next=NULL;
				bmu_tmp=NULL;
			}
		}
	}
	/*********chose the winner from the best match unit*********/
	// not yet done 
		bmu_tmp = bmu_chaine;
		//printf("bbbbbb l=%d,c=%d\n",bmu_chaine->bmu_line,bmu_chaine->bmu_column);
	int bmu_choice=0;
	int * line_column_bmu ;
	line_column_bmu	=	malloc(2*sizeof(int));
	// getiing the number of bmu in the chained list
	while(bmu_tmp != NULL)
		{
			//printf("%lf",bmu_tmp->activation);
			bmu_tmp=bmu_tmp->next;

			bmu_choice++;
		}
		//choosing the winer bmu from the bmu chained list
	//printf("size = %d\t",bmu_choice);
	bmu_choice=rand() % bmu_choice;
	//printf("choice = %d\n",bmu_choice);
	bmu_tmp = bmu_chaine;
	//printf("aaaaa l=%d,c=%d\n",bmu_tmp->bmu_line,bmu_tmp->bmu_column);
	int i=0;
	while(i<(bmu_choice))
	{
		bmu_tmp = bmu_tmp->next;
		//printf("while i=%d l=%d,c=%d\n",i,bmu_tmp->bmu_line,bmu_tmp->bmu_column);
		i++;
	}
	//printf("avant int : l=%d,c=%d\n",bmu_tmp->bmu_line,bmu_tmp->bmu_column);
	line_column_bmu[0]=bmu_tmp->bmu_line;
	line_column_bmu[1]=bmu_tmp->bmu_column;
	//printf("apres int : l=%d,c=%d\n",line_column_bmu[0],line_column_bmu[1]);
	delete_bmu_chaine(&bmu_chaine);
	return line_column_bmu;
}
int * best_match_unit2(data * array_data,neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf)
{
	int * line_column_bmu ;
	line_column_bmu	=	malloc(2*sizeof(int));
	double activation=10000.00;
	for(int j=0;j<network_conf.number_line_network;j++)
	{//printf("\n-----------j =%d\n", j);
		for(int k=0;k<network_conf.number_column_network;k++)
		{
			neural_network[j][k].activation = euclidean_distance(neural_network[j][k].vector,array_data->vector,file_conf.number_column_double_file);
		//	printf("each k= %d distance =%lf\t",k,neural_network[j][k].activation);
			if(activation > neural_network[j][k].activation)
			{
				activation=neural_network[j][k].activation;
				line_column_bmu[0]=j;
				line_column_bmu[1]=k;
		//		printf("update k= %d distance =%lf (l=%d,k=%d) \n",k,neural_network[j][k].activation,line_column_bmu[0],line_column_bmu[1]);
			}	
		}
	}
	return line_column_bmu;
}
double alpha_in_time(double alpha_init,int total_of_iteration,int this_iteration)
{
	return alpha_init * (1-(this_iteration/total_of_iteration));
}

void voisinage (data *array_data,int array_data_index, neuron ** neural_network,neuralNetwork network_conf,int * line_column_bmu,fileConf file_conf,int this_iteration,double alpha_t)
{
	for (int i=(line_column_bmu[0]-network_conf.r_voisinage);i<=(line_column_bmu[0]+network_conf.r_voisinage)&& i<network_conf.number_line_network ;i++)
	{
		if(i>=0 )
		{
			for(int j=(line_column_bmu[1]-network_conf.r_voisinage);j<=(line_column_bmu[1]+network_conf.r_voisinage) && j<network_conf.number_column_network;j++)
				{
					if(j>=0)
					{
						for(int k=0;k<file_conf.number_column_double_file;k++)
							neural_network[i][j].vector[k]=neural_network[i][j].vector[k]+alpha_t*(array_data[array_data_index].vector[k]-neural_network[i][j].vector[k]);
						
					}
				}
		}
	}
}
void ticketing_neural_network(data * array_data,neuron ** neural_network,neuralNetwork network_conf,fileConf file_conf)
{
	for(int i=0;i<network_conf.number_line_network;i++)
	{
		for (int j = 0; j < network_conf.number_column_network; j++)
		{
			neural_network[i][j].activation = 1000.0;
			neural_network[i][j].ticket = strdup(array_data[0].name);
		//	printf("--------------begin :%s\n",	neural_network[i][j].ticket );
			for(int k=0;k<file_conf.number_line_file;k++)
			{
			//	printf("--- %lf\n",euclidean_distance(neural_network[i][j].vector,array_data[k].vector, file_conf.number_column_double_file));
				if(neural_network[i][j].activation>euclidean_distance(neural_network[i][j].vector,array_data[k].vector, file_conf.number_column_double_file))
				{
					neural_network[i][j].activation = euclidean_distance(neural_network[i][j].vector,array_data[k].vector, file_conf.number_column_double_file);
					neural_network[i][j].ticket = strdup(array_data[k].name);
			
				}
			}
		}			
	}
}
void print_ticket_neuron(neuron ** neural_network,neuralNetwork network_conf)
{
	printf(WHITE"\n\nIris-setosa :");
	printf(RED "A\n");
	printf(WHITE"Iris-versicolor :");
	printf(GREEN "B\n");
	printf(WHITE"Iris-virginica :");
	printf(WHITE "C\n\n\n");
	for(int i=0;i<network_conf.number_line_network;i++)
	{
		for (int j = 0; j < network_conf.number_column_network; j++)
		{
			if(!strcmp(neural_network[i][j].ticket,"Iris-setosa"))
			{
					printf(RED "A\t");
			}else{
				if(!strcmp(neural_network[i][j].ticket,"Iris-versicolor"))
				{
					printf(GREEN "B\t");
				}else{
						if(!strcmp(neural_network[i][j].ticket,"Iris-virginica"))
						{
							printf(WHITE "C\t");
						}
					}
				}
		}
		printf("\n");			
	}
}
void print_ticket_neuron2(neuron ** neural_network,neuralNetwork network_conf)
{
	printf(WHITE"\n\nCLASS1 :");
	printf(RED "A\n");
	printf(WHITE"CLASS2 :");
	printf(GREEN "B\n");
	printf(WHITE"CLASS3 :");
	printf(BLUE "C\n\n\n");
	for(int i=0;i<network_conf.number_line_network;i++)
	{
		for (int j = 0; j < network_conf.number_column_network; j++)
		{
			if(!strcmp(neural_network[i][j].ticket,"CLASS1"))
			{
					printf(RED "A\t");
			}else{
				if(!strcmp(neural_network[i][j].ticket,"CLASS2"))
				{
					printf(GREEN "B\t");
				}else{
						if(!strcmp(neural_network[i][j].ticket,"CLASS3"))
						{
							printf(BLUE "C\t");
						}
					}
				}
		}
		printf("\n");			
	}
}
void learning_machine(data * array_data,int *array_data_index,neuron ** neural_network,neuralNetwork  network_conf,fileConf file_conf,int this_iteration)
{
	int * line_column_bmu;
	double alpha_t = alpha_in_time(network_conf.alpha,network_conf.total_of_iteration,this_iteration);
	//one iteration of learning
	shuffle_array(array_data_index,file_conf.number_line_file);
	for(int i=0;i<file_conf.number_line_file;i++)
	{
		line_column_bmu = best_match_unit2(&array_data[array_data_index[i]],neural_network,network_conf,file_conf);
		//printf("---------------l=%d c=%d\n",line_column_bmu[0],line_column_bmu[1]);
		voisinage (array_data,array_data_index[i], neural_network,network_conf,line_column_bmu,file_conf,this_iteration,alpha_t);
	}
}
