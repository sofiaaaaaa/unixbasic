/*
* wizTit()
* define : make a document with user's input
*
* how to excute this function?
*  ./wizTit newFileName title1 title2 ..
*
* how to compile this?
*  gcc -o targetFunctionName thisFileNameWithExtension
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void writeBuf(int wfd, char *buf, size_t size);
int count(char *c, char x);

int main(int argc, char *argv[]){

	int wfd,n;
	char *buf;

	printf("argc = %d\n", argc);

	/*
	   file create
	   argv[1] : new file name
	   if the file exist an arror occurs.
        */

	wfd = open(argv[1], O_CREAT| O_WRONLY | O_EXCL, 0644);   
	if(wfd == -1){
		perror("Excl");
		exit(1);
	}
		
   
	//write file
	size_t size;
	for(n=2; n<argc; n++){
		size = strlen(argv[n]);
		int isize = (int)size;
	
		//add '##' to title parameter	
		buf = argv[n];

				
		printf("argv[%d] = %s |size= %d\n", n, buf ,isize);
	
		int c = count(buf,'-');
                printf("count == %d, %d \n", c, c>1 );

		if(c==0) writeBuf(wfd, "#", 1);
		else if(c>1) writeBuf(wfd, "  ###",5 );
		else writeBuf(wfd, " ##", 3);
		

		writeBuf(wfd, buf ,size);
		
		writeBuf(wfd, "\n\n", 2);
 
	}
	//close file	
	close(wfd);

	return 0;
}

void writeBuf(int wfd, char *buf, size_t size){
	if(write(wfd, buf ,size) != size ){
		 perror("Write");
		 exit(1);
	}
}

int count(char *c, char x){
	int i, count;
	for(i=0; i< sizeof(c); i++){
		if(c[i]==x)
			count++;
		else 
			continue;

	}
	
	return count;
}
