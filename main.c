#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define FRAME_COUNT 2040
#define FRAME_DELAY 66666 // Lowered frame delay to match audio (Delay for 15fps)

pid_t audio_pid; // Store the audio process PID for cleanup

// Function to handle SIGINT
void handle_sigint(int sig) {
    if (audio_pid > 0) {
        kill(audio_pid, SIGTERM); // Terminate the audio process
    }
    printf("\nPlayback interrupted.\n");
    exit(0);
}

// Display a single frame
void displayFrame(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Play audio in a separate process
void playAudio(const char *audioFile) {
    audio_pid = fork();
    if (audio_pid == 0) {
        // Child process plays audio
        execlp("ffplay", "ffplay", "-nodisp", "-autoexit", audioFile, NULL);
        perror("Failed to play audio");
        exit(1);
    }
    if (audio_pid < 0) {
        perror("Failed to fork audio process");
        exit(1);
    }
}

// Play the frames and audio
void playScene() {
    char filename[64];

    for (int i = 0; i < FRAME_COUNT; i++) {
        snprintf(filename, sizeof(filename), "frames/frame_%03d.txt", i + 1); // Construct frame filename
        system("clear"); // Clear the terminal window
        displayFrame(filename); // Display the frame
        usleep(FRAME_DELAY); // Delay to match FPS
    }
}

int main(void) {
    // Handle SIGINT to cleanly terminate playback
    signal(SIGINT, handle_sigint);

    // Play the audio
    playAudio("audio.mp3");

    // Play the frames
    playScene();

    // Wait for the audio process to finish
    if (audio_pid > 0) {
        waitpid(audio_pid, NULL, 0);
    }

    printf("Playback finished!\n");
    return 0;
}
