Huffman Encoding -

You are given a grayscale image where each pixel is represented by an 8-bit value (0-255). Implement an image compression technique using Huffman Encoding where you treat each pixel intensity as a character and build a Huffman Tree based on the frequency of these pixel values.

1. Given the pixel values of the image and calculate the frequency of each intensity level (0-255).
2. Compress the image by encoding the pixel values using Huffman codes.
3. Output the compressed data and a mapping of pixel values to their Huffman codes.
4. Implement a decompression function to verify that the image can be reconstructed from the compressed data.

Input:

    A grayscale image with pixel values ranging from 0-255.

Output:

    Compressed binary data for the image.
    A file containing the Huffman codes for each pixel intensity.
    The reconstructed image after decompression.

Example:

    For a 28x28 grayscale image:

        [ff, .... , d1]
        [0,   .... , ff]
        [0,   .... , d0]
             .......
        [d0,  .... , ff]


    The program should output the compressed binary data and a mapping of intensity levels to Huffman codes.

    Output format -
    	Compressed binary data: 100110101...
    	Huffman codes:
    	   0 -> 1
    	   1 -> 01010
    	     .......
    	   ff -> 01011
    	Reconstructed Image:
    	   ff  ... d1
    	   0   ... ff
           0   ... d0
             .......
    	   d0  ... ff

Explanation:

    1. Input: A 2D grayscale image of size 28x28 is provided with each pixel value ranging from 0 to 255.
    2. Huffman Tree: The frequency of each pixel intensity (0, 128, 255 etc) is calculated to build the Huffman Tree.
    3. Compressed Data: The pixel values are then encoded using the generated Huffman codes.
    4. Huffman Codes: The mapping of pixel values to their corresponding Huffman codes is displayed.
    5. Decompression: The compressed data is decoded, and the original image is reconstructed to verify correctness.

Your Task:

Complete the 3 given functions in "huffman.cpp".

1. "buildHuffmanTree(const unordered_map<string, int>& freq, unordered_map<string, string>& huffmanCodes)"

Arguments: - freq: Map storing the frequencies of each possible pixel value in the image - huffmanCodes: Map storing the binary huffman code of each possible pixel value in the image

Return: - minHeap[0]: Pointer to node containing the final huffman tree formed

Note - The "printCodes" function already generates the "huffmanCodes" in the given file. You don't need to edit those lines.

2. "compressImage(const vector<vector<string>>& image, unordered_map<string, string>& huffmanCodes)"

Arguments: - image: 2D array of hexadecimal values representing the image to be compressed - huffmanCodes: Map storing the binary huffman code of each possible pixel value in the image

Return: - compressedData: string containing the compressed data

Note - In the compressedData first go by row by and then by column

3. "decompressImage(const string& compressedData, Node* root, int rows, int cols, unordered_map<string, string> huffmanCodes)"

Arguments: - compressedData: string containing the compressed data - root: Pointer to root of huffman tree - rows: Number of rows in image - cols: Number of columns in image - huffmanCodes: Map storing the binary huffman code of each possible pixel value in the image

Return: - reconstructedImage: 2D array of hexadecimal values

Scoring:
Use `make runtests` to test your compressed code implementation on the provided testcases.
Only the length of compressed data is being checked for now, but complete correctness of code will be checked during final grading.

Notes:
Please look at huffman.h for the AVAILABLE interface to heap.
