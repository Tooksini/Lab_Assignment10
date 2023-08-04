#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
typedef struct TrieNode{
    int count;
    struct TrieNode *children[26];

} TrieNode;
typedef struct Trie {
    struct TrieNode* root;
}Trie;

TrieNode* createNode();
Trie* createTrie();

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){
    if (pTrie == NULL || word == NULL){
        return;
    }
        
    TrieNode* curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL){
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word){

   if (pTrie == NULL || word == NULL || strlen(word) == 0) {
        return 0;
    }

    struct TrieNode* curr = pTrie->root;
    for (int i = 0; word[i] != '\0'; ++i) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return 0; //
        }
        curr = curr->children[index];
    }
    return curr->count;
}
// deallocate the trie node
void deallocateTrieNode(TrieNode *node) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        deallocateTrieNode(node->children[i]);
    }
    free(node);
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie){
     if (pTrie == NULL) {
        return NULL;
    }
    deallocateTrieNode(pTrie->root);
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
TrieNode *createNode(){
    TrieNode *newNode = (TrieNode *)malloc(sizeof(TrieNode));
    newNode->count = 0;
    for (int i = 0; i < 26; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}
// Initializes a trie structure
Trie* createTrie(){
    struct Trie* newTrie = (struct Trie*)malloc(sizeof(struct Trie));
    newTrie->root = createNode();
    return newTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int numWords = 0;
    char word[256];

    while (fscanf(file, "%s", word) != EOF && numWords < 256) {
        pInWords[numWords] = (char *)malloc((strlen(word) + 1) * sizeof(char));
        strcpy(pInWords[numWords], word);
        numWords++;
    }

    fclose(file);
    return numWords;
}


int main(void){
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");


	return 0;
}