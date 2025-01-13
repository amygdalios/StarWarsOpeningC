#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define FRAME_COUNT 10
#define FRAME_DELAY 100000

// Display a single frame
void displayFrame(const char *filename){
    FILE *file = fopen(filename, "r");
    if(!file){
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)){
        printf("%s", line);
    }   
}

void playScene() {
    char filename[64];
    for(int i=0;i<FRAME_COUNT;i++){
        snprintf(filename, sizeof(filename), "frames/frame_%03d.txt", i); // Frame file name changes from frame_000.txt till the end of frame count
        system("clear"); // Clear terminal window
        displayFrame(filename);
        usleep(FRAME_DELAY); // Add delay between frames
    }
}

int main(void){
    playScene();
    return 0;
}