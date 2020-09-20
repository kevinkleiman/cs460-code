#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void create_thumbnail(char * img[], int img_count) {
	// Generate 25% version of photo with execvp and convert
	// Display the thumbnail with execvp and display
	char * thumbnail_buffer[50];
	sprintf(thumbnail_buffer, "thumbnail%d.jpg", img_count); 
	char * conversion_params[] = {
		"convert",
		"-resize",
		"25%",
		img,
		thumbnail_buffer,
		NULL
	};
	execvp("convert", conversion_params);
	//execvp("display", params);
}

void convert_image(char * params[], int rot) {
	// If rot = -1 do not rotate else use execvp to convert the image
	// Ask user for caption
	execvp("convert", params);
}

int main(int argc, char * argv[]) {
	char * image_path;
	if (argc > 2) {
		image_path = argv[1];
	} else {
		printf("Invalid number of arguments, requires at least 1\n");
		exit(1);
	}
	char * params[] = {
		"test",
		argv[4],
	};
	create_thumbnail(argv[4], 1);	
}

	


