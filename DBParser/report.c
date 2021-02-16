/*
 Program to implement a datebase searcher
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
int checkNameExists(FILE* file, char* name, char* ip)
{

// Read through the CSV data file, keep looking for the name.
// If found, store the IP address associated with the name
// to the variable ip and return success.
// Is bool a valid data type in C? How do you indicate true/false concept in C?
	const char s[2] = ",";
	char *token;
	int counter = 0;
	char line[100];
	char found_name[100];
	char found_ip[100];

	while (fgets(line, sizeof(line), file)) {
		counter = 0;
	   	/* get the first token */
		token = strtok(line, s);
		/* walk through other tokens */
		while(token != NULL) {
		    if (counter == 0) {
			    strcpy(found_name, token);
		    }
		    if (counter == 6) {
			    strcpy(found_ip, token);
		    }
		    counter++;
		  token = strtok(NULL, s);
		}
		if (strcmp(found_name, name) == 0) {
			strcpy(ip, found_ip);
			return 1;
		}
	}
	fclose(file);
	return 0;
}
int findCollaborators(char* sname, FILE* file)
{
// Go through the CSV data file
// look for collaborators of sname by looking for entries with the same ip as sip // if any collaborators are found, write it to the output report file.
        char str[100];
	char ip[50];
	char found_name[100];
	char found_ip[100];
        const char s[2] = ",";	
	FILE *report;
	char line[100];
	int counter = 0;
	char *token;
	int nameCounter = 0;

	if (!checkNameExists(file, sname, ip)) {
		fprintf(stderr, "Error, unable to locate %s\n", sname);
		return 1;
	}
        else if ((report = fopen("rpt.txt", "w")) == NULL) {
                fprintf(stderr, "Error, unable to open csv file rpt.txt\n");
                return 1;
        }	
	report = fopen("rpt.txt", "w");
	rewind(file);
	while (fgets(line, sizeof(line), file)) {
		counter = 0;
		/* get the first token */
		token = strtok(line, s);
		if (strcmp(token, found_name) == 0)
			continue;
		/* walk through other tokens */
		while(token != NULL) {
		    if (counter == 0) {
			    strcpy(found_name, token);
		    }
		    if (counter == 6) {
			    strcpy(found_ip, token);
		    }
		    counter++;
		  token = strtok(NULL, s);
		}
		if (strcmp(found_ip, ip) == 0 & strcmp(found_name, sname) != 0) {
			fprintf(report, "%s\n", found_name);
			nameCounter++;
		}
        }
	if (nameCounter ==0) {
		fprintf(report, "No collaborators found for %s\n", sname);
	}
        fclose(file);
	fclose(report);
	
}
int main(int argc, char *argv[]) {

	FILE *file;
	char str[100];
	if (argc != 4)
	{
		fprintf(stderr, "Error: invalid number of arguments!\n");
		printf("Usage: ./report <csvfile> \"%s\" <reportfile>\n",  "<student name>");
		return 1;
	}
	else if ((file = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Error, unable to open csv file %s \n", argv[1]);
		return 1;
	}

	if (findCollaborators(argv[2],file) ==1) {
		return 1;
	}
	
	return 0;

}

