/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"
#include "pqueue.h"

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
void encodeHelper(Node* encodeTree, Map<ext_char, string>& map, string route);
void codeWriterHelper(const string& line, obstream& file);
bool isLast(Node* curr);
Node* combineChildren(Node* zero, Node* one);
Node* makeLast(ext_char character, int weight);

// so basically here the code reads chars and then calculates their frequencies.
Map<ext_char, int> getFrequencyTable(istream& file) {
	// TODO: Implement this!
	Map<ext_char, int> tableOfCharfrequency;
	char ch;
	while (file.get(ch)) {
		tableOfCharfrequency[ch]++;
	}
	tableOfCharfrequency[PSEUDO_EOF] = 1;
	return tableOfCharfrequency;
	
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	// TODO: Implement this!

	PriorityQueue<Node*> priorQueueOfNode;
	// i created leaf nodes for every char.
	for (ext_char character : frequencies) {
		int currFreq = frequencies[character];
		priorQueueOfNode.enqueue(makeLast(character, currFreq), currFreq);
	}
	// with this while loop we will combine all of the nodes until one is left.
	while (true) {
		if (priorQueueOfNode.size() == 1)break;
		Node* rightNode = priorQueueOfNode.dequeue();
		Node* leftNode = priorQueueOfNode.dequeue();
		priorQueueOfNode.enqueue(combineChildren(leftNode, rightNode),
			leftNode->weight + rightNode->weight);

	}
	return priorQueueOfNode.dequeue();
}
// i created this method in order to create last node.
Node* makeLast(ext_char character, int weight) {
	Node* node = new Node;
	node->weight = weight;
	node->character = character;
	node->one = NULL;
	node->zero = NULL;
	return node;
}
// with this code i combine children to make a parent.
Node* combineChildren(Node* zero, Node* one) {
	Node* curr = new Node;
	curr->weight = zero->weight + one->weight;
	curr->character = NOT_A_CHAR;
	curr->one = one;
	curr->zero = zero;
	return curr;
}
/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
// i used recursion to deallocate memory.
void freeTree(Node* root) {
	// TODO: Implement this!
	if (!root) return;
	freeTree(root->one);
	freeTree(root->zero);
	delete root;
}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
// we encode every character to bits and then we write them down.
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	// TODO: Implement this!
	Map<ext_char, string> MapOfEncoding;
	string empty = "";
	// recursive method to create map.
	encodeHelper(encodingTree, MapOfEncoding, empty);

	char character;
	while (infile.get(character)) {
		ext_char extra = character;
		// we write bits with this method.
		codeWriterHelper(MapOfEncoding[character], outfile);
	}
	codeWriterHelper(MapOfEncoding[PSEUDO_EOF], outfile);
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
// i made a recursive method in order to make map form tree.
void encodeHelper(Node* encodeTree, Map<ext_char, string>& map, string route) {
	if (encodeTree == NULL)return;
	if (!encodeTree->one && !encodeTree->zero) {
		map[encodeTree->character] = route;
		return;

	}
	encodeHelper(encodeTree->one, map, route + "1");
	encodeHelper(encodeTree->zero, map, route + "0");


}
// with this method we write bits in string like 0 or 1.
void codeWriterHelper(const string& line, obstream& file) {
	
	for (char currBit : line) {
		file.writeBit(currBit == '1');
	}
}


// my main focus was to write characters to file so i used boolean method.
// if we get to the last node which means that its leaf then we reset for next char.
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	// TODO: Implement this!
	Node* currTree = encodingTree;
	int currbit;
	while ( (currbit = infile.readBit())!=-1) {
		if (currbit != 0) {
			currTree = currTree->one;
		}
		else {
			currTree = currTree->zero;
		}
		if (isLast(currTree)) {
			if (currTree->character == PSEUDO_EOF) {
				break;
			}
			char  decodeCh = static_cast<char>(currTree->character);
			file.put(decodeCh);
			currTree = encodingTree;
		}	
		

	}
}
// if its last node then it return true.
bool isLast(Node* curr) {
	return curr != NULL && curr->one == NULL && curr->zero == NULL ;

}


/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
// with this code we can compress a file.
void compress(ibstream& infile, obstream& outfile) {
	// TODO: Implement this!
	Map<ext_char, int> freqOfAll = getFrequencyTable(infile);
	
	writeFileHeader(outfile, freqOfAll);
	Node* constructedEncodedTree = buildEncodingTree(freqOfAll);
	// in order to read again our input we rewind stream.
	infile.rewind();

	encodeFile(infile, constructedEncodedTree, outfile);
	// cleans tree.
	freeTree(constructedEncodedTree);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
// with this code i decomppress a file.
void decompress(ibstream& infile, ostream& outfile) {
	// TODO: Implement this!

	Map<ext_char, int> freqOfAll = readFileHeader(infile);
	
	Node* constructedEncodedTree = buildEncodingTree(freqOfAll);

	decodeFile(infile, constructedEncodedTree, outfile);
	freeTree(constructedEncodedTree);
}

