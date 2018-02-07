#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

enum kv {KEY, VALUE};

const char *bookmark_filename = ".bookmark";
const int MAX_LINE = 4096;

char *concat(const char *s, const char *t){
	int ls = strlen(s), lt = strlen(t);
	char *res = (char*)malloc(sizeof(char)*(ls+lt+2));
	for(int i=0; i<ls; i++)res[i] = s[i]; res[ls] = '/';
	for(int i=0; i<lt; i++)res[ls+1+i] = t[i];
	res[ls+1+lt] = '\0';
	return res;
}

int main(int argc, char **argv)
{
	if(argc == 1){
		fprintf(stderr, "No argument, stop.\n");
		return -1;
	}

	struct passwd *pw = getpwuid(getuid());
	char *homedir = pw->pw_dir;
	char *bookmark_path = concat(homedir, bookmark_filename);
	FILE *bookmark_fp = fopen(bookmark_path, "r");
	free(bookmark_path);
	if(bookmark_fp == NULL){
		fprintf(stderr, "Error occured at fopen() with errno: %d\n", errno);
		return -1;
	}

	int len = strlen(argv[1]);
	char *s = argv[1];
	int found = 0;

	char *line = (char*)malloc(sizeof(char)*MAX_LINE);
	while(fgets(line, MAX_LINE, bookmark_fp) != NULL){
		int line_len = strlen(line);
		enum kv state = KEY;
		for(int i=0; i<line_len; i++){
			if(line[i] == '\t'){
				state = VALUE;
				if(i == len){
					found = 1;
					while(line[i] == '\t')i++;
					printf("%s", line+i);
					fclose(bookmark_fp);
					return 0;
				}
				else{
					break;
				}
			}
			if(i > len && state == KEY){break;}
			if(line[i] != s[i]){break;}
		}
	}
	if(!found) {fprintf(stderr, "Key not found.\n"); printf("%s", s); return 0;}

	return 0;
}
