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
		printf("%lf",data_value->vector[i]);
	printf("%lf",data_value->norm);
	printf("%s\n",data_value->name);
}

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
				array_data[line_read_file].vector[i] = strtod(token,&endPtr); // get the double in the string token
				token	=	strtok(NULL,",");
			}
			token = strtok(token,"\n");
			//printf("%s\n",token);
			strcpy(array_data[line_read_file].name,token);// to get the name of the vector
			// calculat the norm of the vector in the data
			array_data[line_read_file].norm = calcul_norm (array_data[line_read_file].vector,file_conf->number_column_double_file);
			//normalising vector of the data
			vector_normalisation(&array_data[line_read_file],file_conf->number_column_double_file);
			/************calculating the average vector of the iris database ******/
			// in here adding the normalised vectors
			for(int i=0;i<file_conf->number_column_double_file;i++)
				file_conf->vector[i]+=array_data[line_read_file].vector[i];
			/**********************************************************************/
			line_read_file ++;// to know witch line i'm reading in file
		}
		/************calculating the average vector of the iris database ******/
		/************** in here spliting by  the number of vectors to get the average *********/
		for(int i=0;i<file_conf->number_column_double_file;i++)
			file_conf->vector[i]=file_conf->vector[i]/file_conf->number_line_file;

  	file_line = NULL;
	fclose(file);
}