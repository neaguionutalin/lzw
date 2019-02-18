// #include "comp0019.h"
//
// void Encode(FILE* in_file, FILE* out_file) {
// 	char text[1000];
// 	int i=0;
// 	while(feof(in_file)){
// 		text[i++]=fgetc(in_file);
// 		fprintf("%c", text[i]);
// 	}
// 	text[i]='\0';
// 	fprintf(out_file, "%s", text);
// }


#include "comp0019.h"
#include <string.h>
#define MAXCHAR 1000

void Encode(FILE* in_file, FILE* out_file) {
	char str[MAXCHAR];

	while(fgets(str, MAXCHAR, in_file)!=NULL){
		printf("%s\n", str);
		fprintf(out_file, "%s", str);
	}
}
