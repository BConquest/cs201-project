#include <stdio.h>  
#include <unistd.h>  

int main(int argc, char *argv[])  
{ 
	int opt; 

	while((opt = getopt(argc, argv, ":if:lrx")) != -1)  
	{  
		switch(opt)  
		{ 
			case 'l':
				printf("whatever");
				break;
			case 'f':  
				printf("filename: %s\n", optarg);  
				break;  
			case ':':  
			       printf("option needs a value\n");  
			       break;  
			case '?':  
			       printf("unknown option: %c\n", optopt); 
			       break;  
		}  
	}  

	for(; optind < argc; optind++){      
		printf("extra arguments: %s\n", argv[optind]);  
	} 

	return 0; 
} 
