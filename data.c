#include "data.h"


int count_number_line_file(FILE * file)
{
	size_t line_buf_size = 0;
	char *	file_line;
	int nbr_line_file =	0;

	while(getline(&file_line, &line_buf_size, file)	!=	-1)
		nbr_line_file ++;
	free(file_line);
  	file_line = NULL;
	return nbr_line_file;
}

int count_number_column_file(FILE * file)
{
	size_t line_buf_size = 0;
	char *	file_line;
	char * token ;
	int nbr_column_file =	0;
	if(getline(&file_line, &line_buf_size, file)	!=	-1)
	{
		token = strtok(file_line,",");
		while(token != NULL)
		{
			nbr_column_file ++;
			token	=	strtok(NULL,",");
		}
	}
	free(file_line);
	free(token);
	return nbr_column_file;
}
void print_data (data * data_value, int number_column_double_file)
{
	for (int i = 0;i<number_column_double_file;i++)
		printf("%lf\t",data_value->vector[i]);
	printf("%lf\t",data_value->norm);
	printf("%s\n",data_value->name);
}

/*void init_data_value(data * data_value,int number_column_double_file)
{
	data_value->vector = malloc(number_column_double_file*sizeof(double));
	if(data_value->vector==NULL)
	{
		printf("erreur malloc2\n");
		exit(0);
	}
	data_value->name = malloc(30*sizeof(char));
	if(data_value->name==NULL)
	{
		printf("erreur malloc3\n");
		exit(0);
	}
	data_value->norm =0.0;
}
void init_data_array(data * array_data,int number_column_double_file,int number_line_file)
{
	array_data = malloc(number_line_file*sizeof(data));// allocate array of struct data with size of the number of lines
	if(array_data==NULL)
	{
		printf("erreur malloc1\n");
		exit(0);
	}
	for(int i =0;i<number_line_file;i++)
	{
		init_data_value(&array_data[i],number_column_double_file);// allocate data for each structure in the array_data
	}

}*/
void shuffle_array(int * data_array_index,int number_line_file)
{
	srand(time(NULL));// init rand to give a new number each time
	for(int i=(number_line_file-1);i>0;i--)
	{
		int j	=	rand()%(i);// rand() % (maxrange-minrange)+ minragnge;
		int  index_tmp;
		index_tmp=data_array_index[i];
		data_array_index[i]=data_array_index[j];
		data_array_index[j]=index_tmp;
	}

}

/** function to calculate norm of a vector of size (number_column_double_file) */
double calcul_norm (double * vector,int number_column_double_file)
{
	double norm = 0.0;
	for(int i =	0;i<number_column_double_file;i++)
		norm+= pow(vector[i],2.0);
	
	return sqrt(norm);
}

/*  x[i]/norm for every vector in the data array */
void vector_normalisation(data * data_value,int number_column_double_file)
{
	for(int i=0;i<number_column_double_file;i++)
		data_value->vector[i]=data_value->vector[i]/data_value->norm;
}
/*function to calculate the average vector of the Iris dataser 
void average_vector(data * array_data,fileConf * file_conf)
{
	for(int i=0;i<file_conf->number_column_double_file;i++)
	{
		for (int j = 0; j < file_conf->number_line_file; j++)
		{
			file_conf->vector[i]+=array_data[j].vector[i];
		}
		file_conf->vector[i]=file_conf->vector[i]/file_conf->number_line_file;
	}
}*/
void parser (data * array_data,fileConf * file_conf)
{
	/*****************************************/
	// DECLARATION in relation with the file structure
	/****************************************/
	FILE * file =	NULL;

	/*****************************************/
	// DECLARATION in relation with reading file
	/****************************************/
	size_t line_buf_size = 0;
	char *	file_line;//string that stocks the line i'm reading from the file
	char * token ;
	char * endPtr;
	int line_read_file =0; // represents the number of the file line i'm reading
	
	file =	fopen("iris.data","r");
	if(file == NULL)
	{
		printf("Erreur d'ouverture fichier iris.data/n");
		exit(0);
	}

	/**********************************************************************/
	/*  reading from the file line by line and then stock in array_data	  */
	/**********************************************************************/
	while(getline(&file_line, &line_buf_size, file)	!=	-1)
		{
			token	=	strtok(file_line,",");
			for(int i=0;i<file_conf->number_column_double_file;i++)
			{
				
				//printf("%lf\t",strtod(token,&endPtr));
				array_data[line_read_file].vector[i] = strtod(token,&endPtr);
				token	=	strtok(NULL,",");
			}
			token = strtok(token,"\n");
			//printf("%s\n",token);
			strcpy(array_data[line_read_file].name,token);
			array_data[line_read_file].norm = calcul_norm (array_data[line_read_file].vector,file_conf->number_column_double_file);
			vector_normalisation(&array_data[line_read_file],file_conf->number_column_double_file);
			/************calculating the average vector of the iris database ******/
			// in here adding the normalised vectors
			for(int i=0;i<file_conf->number_column_double_file;i++)
				file_conf->vector[i]+=array_data[line_read_file].vector[i];
			file_conf->norm+=array_data[line_read_file].norm;
			/**********************************************************************/
			line_read_file ++;// to know witch line i'm reading in file
		}
		/************calculating the average vector of the iris database ******/
		/************** in here spliting by  the number of vectors to get the average *********/
		for(int i=0;i<file_conf->number_column_double_file;i++)
			file_conf->vector[i]=file_conf->vector[i]/file_conf->number_line_file;
		file_conf->norm=file_conf->norm/file_conf->number_line_file;
  	file_line = NULL;
	fclose(file);
}