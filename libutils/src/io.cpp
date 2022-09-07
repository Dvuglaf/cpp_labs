#include <libutils/io.h>
#include<cerrno>	//errno
#include <cstdio>	//fgets, printf
#include <cstring>	//strchr
#include <cstdlib>	//strtol
#include <cctype>	//isspace

int utils::read_int(const char *prompt, int min, int max){
    while(true){
        printf("%s", prompt);
        char str[16];
        fgets(str, sizeof(str), stdin);
        if(strchr(str, '\n')==NULL){
            bool f=true;
            int c;
            while((c=fgetc(stdin))!='\n' && c!=EOF){
                if(!isspace(c)){
                    f=false;
                }
            }
            if(f==false){
                printf("The entered string is too large\n");
                continue;
            }
        }
        char *endptr=NULL;
        errno=0;
        long n=strtol(str, &endptr, 10);
        if(errno==ERANGE){
            printf("The entered number is too large\n");
            continue;
        }
        if(endptr==str){
            printf("The entered string is invalid\n");
            continue;
        }
        bool correct=true;
        for(char*p=endptr; *p!=0; ++p){
            if(!isspace(*p)){
                correct=false;
                break;
            }
        }
        if(correct==false){
            printf("The entered string contains invalid characters\n");
            continue;
        }
        if(n<min || n>max){
            printf("The entered number must be from %d to %d\n", min, max);
            continue;
        }
        return (int) n;
    }
}
double utils::read_double(const char* prompt, double min, double max, double eps) {
	while (true) {
		printf("%s", prompt);
		char str[16];
		fgets(str, sizeof(str), stdin);
		if (strchr(str, '\n') == NULL) {
			bool f = true;
			int c;
			while ((c = fgetc(stdin)) != '\n' && c != EOF) {
				if (!isspace(c)) {
					f = false;
				}
			}
			if (f == false) {
				printf("The entered string is too large\n");
				continue;
			}
		}
		char* endptr = NULL;
		errno = 0;
		double n = strtod(str, &endptr);
		if (errno == ERANGE) {
			printf("The entered number is too large\n");
			continue;
		}
		if (endptr == str) {
			printf("The entered string is invalid\n");
			continue;
		}
		bool correct = true;
		for (char* p = endptr; *p != 0; ++p) {
			if (!isspace(*p)) {
				correct = false;
				break;
			}
		}
		if (correct == false) {
			printf("The entered string contains invalid characters\n");
			continue;
		}
		if (min - n > eps || n - max > eps) {
			printf("The entered number must be from %lf to %lf\n", min, max);
			continue;
		}
		return n;
	}
}