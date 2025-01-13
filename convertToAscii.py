import subprocess
import os


# I used this python script to automate converting all of the frames I generated from the video file to ascii art using jp2a.

# Define input and output directories
input_dir = "frames"
output_dir = "ascii_frames"

# Ensure the output directory exists
os.makedirs(output_dir, exist_ok=True)

# Get a sorted list of all frame files in the input directory
frame_files = sorted([f for f in os.listdir(input_dir) if f.endswith(".png")])

# Track skipped frames for debugging
skipped_frames = []

# Loop through all frames and convert each to ASCII
for frame in frame_files:
    input_path = os.path.join(input_dir, frame)
    output_path = os.path.join(output_dir, os.path.splitext(frame)[0] + ".txt")

    try:
        # Use jp2a to convert the PNG frame to ASCII art and save to output file
        subprocess.run(
            ["jp2a", "--width=80", input_path, "--output=" + output_path],
            check=True
        )
        print(f"Converted {frame} to ASCII art.")
    except subprocess.CalledProcessError as e:
        print(f"Error converting {frame}: {e}")
        skipped_frames.append(frame)
    except Exception as e:
        print(f"Unexpected error with {frame}: {e}")
        skipped_frames.append(frame)

# Report skipped frames
if skipped_frames:
    print("\nThe following frames were skipped due to errors:")
    for skipped in skipped_frames:
        print(skipped)
else:
    print("\nAll frames were successfully processed!")
