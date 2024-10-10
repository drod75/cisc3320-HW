#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(){

	// flags set
	int flags = O_CREAT | O_WRONLY;
	
	// file created and id returned
	int fd = open("newfile.txt", flags,0644);

	// close file
	close(fd);
	
	// end program
	return 0;
}