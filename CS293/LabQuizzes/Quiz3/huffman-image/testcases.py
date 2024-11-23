import sys
import os
from PIL import Image
import numpy as np

def images_to_text(folder_path, output_folder):
    """Convert images in a folder to grayscale matrices and save them as text files."""
    # Ensure the output folder exists
    os.makedirs(output_folder, exist_ok=True)

    # Loop through all files in the folder
    for filename in os.listdir(folder_path):
        if filename.endswith(".jpg"):  # Add more extensions if needed
            # Full file path
            image_path = os.path.join(folder_path, filename)

            # Load the image
            image = Image.open(image_path)

            # Convert the image to grayscale
            gray_image = image.convert('L')

            # Convert the grayscale image to a NumPy array (matrix)
            gray_matrix = np.array(gray_image)

            # Generate output file path
            base_filename = os.path.splitext(filename)[0]  # Strip file extension
            output_file_path = os.path.join(output_folder, f"testcase_{base_filename}.txt")

            # Convert matrix to hexadecimal format
            hex_matrix = [[hex(pixel)[2:].zfill(2) for pixel in row] for row in gray_matrix]  # Strip '0x' and ensure 2 digits

            # Save the hex matrix to a text file
            with open(output_file_path, 'w') as f:
                for row in hex_matrix:
                    f.write(" ".join(row) + "\n")

            #print(f"Hexadecimal grayscale matrix for {filename} saved to {output_file_path}")


def text_to_images(input_folder, output_folder):
    """Read matrices from text files and create images from them."""
    # Ensure the output folder exists
    os.makedirs(output_folder, exist_ok=True)

    # Loop through all files in the input folder
    for filename in os.listdir(input_folder):
        if filename.endswith(".txt"):  # Process only .txt files
            # Full file path
            file_path = os.path.join(input_folder, filename)

            # Load the hex matrix from the text file
            with open(file_path, 'r') as f:
                hex_matrix = [line.strip().split() for line in f]

            # Convert hex matrix back to a decimal NumPy array
            gray_matrix = np.array([[int(pixel, 16) for pixel in row] for row in hex_matrix], dtype=np.uint8)

            # Print the matrix for debugging
            # print(f"Loaded matrix from {file_path}:")
            # print(len(gray_matrix))
            # print("\n")
            if len(gray_matrix[0]) == 0 :
                return

            # Convert the NumPy array (matrix) to an image
            image = Image.fromarray(gray_matrix)

            # Generate output file path
            base_filename = os.path.splitext(filename)[0]  # Strip file extension
            output_image_path = os.path.join(output_folder, f"{base_filename}.png")  # Save as PNG

            # Save the image
            image.save(output_image_path)

            #print(f"Image created from {filename} saved to {output_image_path}")


# Example usage
if __name__ == "__main__":

    if len(sys.argv) != 2:
        print("Usage: python script.py <1 or 2>")
        sys.exit(1)

    # Predefined folder paths
    input_images_folder = './testcases/input_img'
    output_text_folder = './testcases/input'
    input_text_folder = './testcases/output'
    output_images_folder = './testcases/output_img'

    choice = sys.argv[1]

    # Execute based on user input
    if choice == '1':
        # Convert images to text files
        images_to_text(input_images_folder, output_text_folder)
    elif choice == '2':
        # Convert text files back to images
        text_to_images(input_text_folder, output_images_folder)
    else:
        print("Invalid input! Please enter 1 or 2.")
