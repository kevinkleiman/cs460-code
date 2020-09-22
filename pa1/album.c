#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

// A function for easily converting images
void convert_image(char * img[], char * out_img[], int rot, int resize) {
	char * resize_buffer[50];
	char * rotate_buffer[50];
	
	// Use -1 as a selector
	if (rot > -1 ) {
		// Get conversion params from user and image
		sprintf(rotate_buffer, "%d", rot);
		char *conversion_params[] = {
			"convert",
			img,
			"-rotate",
			rotate_buffer,
			out_img,
			NULL	
		};
		// Fork a process to handle conversion
		pid_t pid = fork();
		if (pid == 0) {
			execvp("convert", conversion_params);
		}
	}
	if (resize > -1) {
		// Same as rotate just resizing
		sprintf(resize_buffer, "%d%%", resize);
		char * conversion_params[] = {
			"convert",
			"-resize",
			resize_buffer,
			img,
			out_img,
			NULL
		};
		pid_t pid = fork();
		if (pid == 0) {
			execvp("convert", conversion_params);
		}
	}
}

// Creates thumbnails
void create_thumbnail(char * img_arr[], int img_count) {
	char * thumbnail_buffer[50];
	// Forks process to generate 25% version of photo
	pid_t pid = fork();
	if (pid == 0) {
		for (int i = 1; i < img_count; i++) {
			sprintf(thumbnail_buffer, "thumbnail%d.jpg", i);
			convert_image(img_arr[i], thumbnail_buffer, -1, 25);
		}
	} else {
		// Calls init to get user input while this is going on
		init(img_arr, img_count);
	}	
}

// Based heavily on given example code from Github
void write_html(char * captions[], int img_count) {
    char * outfilename = "index.html";
	char * thumbnail_buffer[50];
	char * medium_buffer[50];

    FILE* fp = NULL;
    if ((fp = fopen(outfilename, "w")) == NULL) {
        fprintf(stderr, "Cannot Open Output File\n", outfilename);
        exit(1);
    }
    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "<title>Kev's Digital Photo Album</title>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");

    fprintf(fp, "<h1>Kev's Digital Photo Album</h1>\n");
    fprintf(fp, "<ul>\n");
	// Dynamically write caption and photo display
    for(int i = 1; i < img_count; i++) {
		printf("Caption: %s\n", captions[i]);
		sprintf(thumbnail_buffer, "thumbnail%d.jpg", i);
		sprintf(medium_buffer, "medium_photo%d.jpg", i);
        fprintf(fp, "\t<li>\n\t\t<h3>%s</h3>\n\t\t<a href=\"%s\"><img src=\"%s\"></a>\n\t</li>\n", "caption holder", medium_buffer, thumbnail_buffer);
    }
    fprintf(fp, "</ul>\n");

    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

	fclose(fp);
    fprintf(stdout, "\nindex.html Created\n", outfilename);
}

// Init function to get user input and handle display of thumbnails
void init(char * img_arr[], int img_count) {
	int rot;
	int child_status;
	char * medium_buffer[50];
	char * thumbnail_buffer[50];
	char * captions[100][100];
	pid_t pid = fork();
	// Forks process to create 75% photos while getting user input
	if (pid == 0) {
		for (int i = 1; i < img_count; i++) {
			sprintf(medium_buffer, "medium_photo%d.jpg", i);
			convert_image(img_arr[i], medium_buffer, -1, 75);
		}
	} else {
		char * caption[50];
		waitpid(pid, &child_status, 0);
		for (int i = 1; i < img_count; i++) {
			// Creates medium and thumbnail names
			sprintf(medium_buffer, "medium_photo%d.jpg", i);
			sprintf(thumbnail_buffer, "thumbnail%d.jpg", i);
			// Forkes process to display
			pid_t pid_1 = fork();
			if (pid_1 == 0) {
				char * display_params[] = {"display", img_arr[i], NULL};
				execvp("display", display_params);
			}
			printf("\nEnter rotation (degrees): ");
			scanf("%d", &rot);
			printf("\nEnter a caption: ");
			scanf("%s", &caption);
			// Kills display process
			kill(pid_1, SIGTERM);
			// Copies into array for captions
			strcpy(captions[i - 1], caption);
			printf("%s", captions[i]);
			convert_image(medium_buffer, medium_buffer, rot, -1);
		}
		// Writes index.html
		write_html(captions, img_count);
	}
}

// Main function
int main(int argc, char * argv[]) {
	// Checks for photos in argv
	if (argc < 2) {
		printf("Invalid number of arguments, requires at least 1\n");
		exit(1);
	}
	create_thumbnail(argv, argc);	
	return 0;
}

	


