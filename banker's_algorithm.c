#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	
int main()
{	
	int m, n ;   // resources and processes, respectively.
	int i=0, j=0, k=0, total=0;
	char line[256][256];
	char fname[50];
	
	printf(" Banker's Algorithm - Safety Algorithm"
	       " \n Programmed by: John Cedric R. Warain");
	      
	printf("\n\n Input the filename to be opened: ");
	scanf("%s", fname);
	
	printf("\n Reading data file...done...\n ");
	printf("\n The data file is interpreted below: ");
	
    FILE *data = NULL; 
    data = fopen(fname, "r");
    
    //store the lines from the text file into an array
    while(fgets(line[i], 256, data)) 
	{
        line[i][strlen(line[i]) + 1] = '\0';
        i++;
    }
    total = i;
    
	//get values for resources and processes
	sscanf(line[0], "%d %d", &m, &n);
	
	
	//get values for instances for each resource type	
	char *token;
	token = strtok(line[1]," ");
	
	int instances[m];
	i = 0;
	while(token != NULL)
	{
        instances[i] = atoi(token);
        token = strtok(NULL," ");
        i++;
    }
    
    
    //get values for the allocation and max matrix
    int alloc[n][m];
    int max[n][m];
   
    k = 2;
    for(i=0; i < n; i++)
    {
    	token = strtok(line[k]," ");
		token = strtok(NULL," ");
		
			for(j=0; j < m; j++)
			{
				alloc[i][j] = atoi(token);
		        token = strtok(NULL," ");   	
			}
	    
		    for(j=0; j < m; j++)
			{
		        max[i][j] = atoi(token);
		        token = strtok(NULL," ");
		    }
				    
		k++;
	}
	
	
	printf("\n");
	for(i=0; i < m; i++)
		printf("\n Resource %d(R%d) = %d instances", i + 1, i + 1, instances[i] );
	
	//Allocated Resources for the processes	
	printf("\n\n Allocated Resources for the %d processes: ", n);
	
	printf("\n\n Process");
	
	for(i=0; i < m; i++)
		printf("\t R%d", i + 1);
		
	for(i=0; i < n; i++)
	{
		printf("\n P%d\t", i);
			for(j=0; j < m; j++)
			{
				printf("\t %d", alloc[i][j]);   	
			}
	}
	
	//Maximum Resources for the processes
	printf("\n\n Maximum Resources for the %d processes: ", n);
	
	printf("\n\n Process");
	
	for(i=0; i < m; i++)
		printf("\t R%d", i + 1);
		
	for(i=0; i < n; i++)
	{
		printf("\n P%d\t", i);
			for(j=0; j < m; j++)
			{
				printf("\t %d", max[i][j]);   	
			}
	}
	
	//"Need" Resources for the processes
	int need[n][m];
	
	for(i=0; i < n; i++)
	{
		for(j=0; j < m; j++)
		{
			need[i][j] = max[i][j] - alloc[i][j];   	
		}
	}
	
	printf("\n\n Need matrix for the %d processes: ", n);
	
	printf("\n\n Process");
	
	for(i=0; i < m; i++)
		printf("\t R%d", i + 1);
		
	for(i=0; i < n; i++)
	{
		printf("\n P%d\t", i);
			for(j=0; j < m; j++)
			{
				printf("\t %d", need[i][j]);   	
			}
	}
	
	//input for the available instances for each resource type
	int avail[m];
		
	int total_alloc[m];
	for(i = 0; i < m; i++)
		total_alloc[i] = 0;
	
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			total_alloc[i] += alloc[j][i];
		}
	}
	
	for(i=0; i < m; i++)
	{
		avail[i] = instances[i] - total_alloc[i];
	}
	
	printf("\n\n Available instances for each resource type:");
	
	for(i=0; i < m; i++)
		printf("\t R%d = %d", i + 1, avail[i]);
	
	
	
	//Safety Algorithm
	int remain[m];	
	int process[n], seq[n], index = 0;
	
	for (k = 0; k < n; k++) 
	{
        process[k] = 0;
    }
    
    for (k = 0; k < n; k++) 
	{
        seq[k] = -1;
    }
    
    int y = 0;
    
    for (k = 0; k < n; k++)
    {
    	for (i = 0; i < n; i++)
    	{
    		if (process[i] == 0)
    		{
				int flag = 0;
    			for(j = 0; j < m; j++)
    			{
    				if(need[i][j] > avail[j])
    				{
    					flag = 1;
    					break;
					}
				}
			
				if(flag == 0)
				{
					seq[index] = i;
					index++;
					printf("\n\n P%d is given the resources...", i);
					printf("\n Available is");
					
					for (y = 0; y < m; y++)
					{
						printf(" %d", avail[y]);	
					}
					printf(" -");
					
					for (y = 0; y < m; y++)
					{
						printf(" %d", need[i][y]);		
					}
					printf(" =");
					
					for(y = 0; y < m; y++)
					{
						remain[y] = avail[y] - need[i][y];
						printf(" %d", remain[y]);		
					}
					
					printf("\n P%d is done with the resources...", i);
					printf("\n Available is");
					
					for (y = 0; y < m; y++)
					{
						printf(" %d", remain[y]);	
					}
					printf(" +");
					
					for (y = 0; y < m; y++)
					{
						printf(" %d", max[i][y]);		
					}
					printf(" =");
					
					for(y = 0; y < m; y++)
					{
						avail[y] = remain[y] + max[i][y];
						printf(" %d", avail[y]);
					}
					
					process[i] = 1;
			
					printf("\n\n Current Sequence = ");
					for(y = 0; y < n; y++)
					{
						if(seq[y] > -1)
							printf(" P%d ", seq[y]);
					}		
				}
			}
		}
	}
	
	//print out safe or unsafe sequence
	for(i = 0; i < n; i++)
	{
		if(process[i] == 0)
		{
			printf("\n\n Warning- processes are in a deadlocked state.");
			printf("\n\n Unsafe Sequence = ");
			for(y = 0; y < n; y++)
			{
				if(seq[y] > -1)
					printf(" P%d ", seq[y]);
			}
			printf("\n\n");
			return 0;	
		}	
	}
	
	printf("\n\n Processes are not in a deadlocked state.");		
	printf("\n\n Safe Sequence = ");
	for(y = 0; y < n; y++)
	{
		if(seq[y] > -1)
			printf(" P%d ", seq[y]);
	}
	printf("\n\n");
	return 0;
	
}
    
    




