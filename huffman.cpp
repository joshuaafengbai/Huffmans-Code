#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>
#include <chrono>

using namespace std::chrono;


struct hufftreenode {
	char character;
	int frequency;
	hufftreenode* left;
	hufftreenode* right;
};

typedef hufftreenode* hufftreeptr;

//Nodeleft and NodeRight visit every leaf node in the hufftree and then records the path taken to get there
void NodeRight(std::string StringPath, hufftreeptr NodeCurrent, std::map<char, std::string>& hufftable);
void NodeLeft(std::string StringPath, hufftreeptr NodeCurrent, std::map<char, std::string>& hufftable);
//IdentifySmallest: Returns the smallest hufftree and removes it from Temporary Vector
hufftreeptr IdentifySmallest(std::vector<hufftreeptr>& TemporaryVector);

bool valid_hufftree(const hufftreeptr hufftree);
std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable);
std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree);

int main() {
  std::string message, encodedmessage, decodedmessage;
	hufftreeptr hufftree;
	std::map<char, int> freqtable;
	std::map<char, std::string> hufftable;

	message = "the quick brown fox jumped over the lazy dog aaaaaaaaaaaaaaaaa";
    std::cout << message << std::endl;

	// 1) encoding (compression)
	encodedmessage = huffencode(message, freqtable, hufftree, hufftable);

  if(valid_hufftree(hufftree))  {
		std::cout << "valid Huffman tree." << std::endl;
	}
	else {
		std::cout << "not valid Huffman tree." << std::endl;
	}

	std::cout << encodedmessage << std::endl;
	std::map<char, std::string> :: iterator it;
    for(it = hufftable.begin(); it != hufftable.end(); it++){
 		std::cout<<"(" <<it->first<<", "<<it->second<<")"<<std::endl;
    }

  decodedmessage = huffdecode(encodedmessage, hufftree);
  if(decodedmessage == message){
    std::cout << "decoding OK." << std::endl;
  }
  else {
    std::cout << "decoding not OK." << std::endl;
  }
  return 0;


std::string filename;
std::ifstream infile;
	    std::cout << "Please enter the name of the file to use for input" << std::endl;
	    std::cin >> filename;
	    std::cout << std::endl;

	    infile.open(filename.c_str());

	    if(!infile.is_open())
	    {
	           std::cout << "the file couldn't be opened" << std::endl;
	           exit(EXIT_FAILURE);
	    }

	    std::string c;

	    while(infile >> c)
	    {
	        message.append(c);
	    }

	    auto start1 = high_resolution_clock::now();//start stopwatch
	    encodedmessage = huffencode ( message , freqtable , hufftree , hufftable ) ;
	    auto stop1 = high_resolution_clock::now(); //stop stopwatch
	    // Get duration. Subtract the timepoints
	    auto duration1 = duration_cast<microseconds>(stop1 - start1);
	    std::cout << "Time taken to encode: " << duration1.count() << " mS" << std::endl;

	    auto start2 = high_resolution_clock::now();//start stopwatch
	    decodedmessage = huffdecode ( encodedmessage , hufftree ) ;
	    auto stop2 = high_resolution_clock::now(); //stop stopwatch
	    // Get duration. Subtract the timepoints
	    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
	    std::cout << "Time taken to decode: " << duration2.count() << " uS" << std::endl;

}

void NodeRight(std::string StringPath, hufftreeptr NodeCurrent, std::map<char, std::string>& hufftable){
  StringPath.push_back('1');
  //Check if this node is a leaf
  if((NodeCurrent->left == NULL) && (NodeCurrent->right == NULL)){
    hufftable[NodeCurrent->character] = StringPath;
  }
  else{
    if(NodeCurrent->left != NULL){
      NodeLeft(StringPath, NodeCurrent->left, hufftable);
    }
    if(NodeCurrent->right != NULL){
      NodeRight(StringPath, NodeCurrent->right, hufftable);
    }
  }
}

void NodeLeft(std::string StringPath, hufftreeptr NodeCurrent, std::map<char, std::string>& hufftable){
  StringPath.push_back('0');
  //Check if this node is a leaf
  if((NodeCurrent->left == NULL) && (NodeCurrent->right == NULL)){
    hufftable[NodeCurrent->character] = StringPath;
  }
  else{
    if(NodeCurrent->left != NULL){
      NodeLeft(StringPath, NodeCurrent->left, hufftable);
    }
    if(NodeCurrent->right != NULL){
      NodeRight(StringPath, NodeCurrent->right, hufftable);
    }
  }
}

hufftreeptr IdentifySmallest(std::vector<hufftreeptr>& TemporaryVector){
  //Set the smallest frequency to the first vector node
  hufftreeptr SmallestNode = TemporaryVector[0];
  //Tracks the positon of the smallest frequency
  int Position = 0;
  for(int j=1; j<TemporaryVector.size(); j++){
    if(TemporaryVector[j]->frequency < SmallestNode->frequency){
      //Change Smallest node is a smaller node has been found
      SmallestNode = TemporaryVector[j];
      Position = j;
    }
  }
  TemporaryVector.erase(TemporaryVector.begin() + Position);   //remove the smallest node from the vector
  return SmallestNode; //return the address of the smallest node
}

bool valid_hufftree(const hufftreeptr hufftree){
  //All terminal nodes should have characters
  if((hufftree->left == NULL) && (hufftree->right == NULL)){
    if(hufftree->character == '\b'){
      return false;
    }
  }
  else{
    //Frequency of non leaf node equals sum of frequencies of two sub trees
    if((hufftree->left != NULL)&&(hufftree->right != NULL)){
      if(hufftree->frequency != (hufftree->left)->frequency + (hufftree->right)->frequency){
        return false;
      }
    }
    //Non leaf nodes should have two subtrees each
    else{
      return false;
    }
  }
  //We do this for every subsequent node
  if(hufftree->left != NULL){
    valid_hufftree(hufftree->left);
  }
  if(hufftree->right != NULL){
    valid_hufftree(hufftree->right);
  }
  return true;
}

std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable){
  //Code to build frequency table by going through message and recording frequency of each character
  for(int i=0; i<message.length(); i++){
    freqtable[message[i]] += 1;
  }
  //We create a tree for each character
  std::vector<hufftreeptr> TempVector;
  //We use this iterator to go through each vector
  std::map<char, int>:: iterator FrequencyTableCopy;
  std::string StringNew;
  for(FrequencyTableCopy = freqtable.begin(); FrequencyTableCopy != freqtable.end(); FrequencyTableCopy++){
    hufftreeptr  charTree = new hufftreenode();
    charTree->character = FrequencyTableCopy->first;
    charTree->frequency = FrequencyTableCopy->second;
    //We add all the characters to a temporary vector so we don't lose them
    TempVector.push_back(charTree);
  }
  //Unique case: if message is only 1 character type
  if(TempVector.size() == 1){
    hufftree = TempVector[0];
    //This shows that the only charcter is at the root node
    hufftable[hufftree->character] = "!";
    //So we skip if the if-statement executes
    goto skip;
  }

  //We find the two smallest nodes and connect them together until there arer no longer unconnected nodes
  while(TempVector.size() > 1){
    hufftreeptr smallest = IdentifySmallest(TempVector);
    hufftreeptr secondSmallest = IdentifySmallest(TempVector);
    //Create new node to join the two nodes above
    hufftreeptr ResultingNode = new hufftreenode();
    ResultingNode->frequency = smallest->frequency + secondSmallest->frequency;
    ResultingNode->left = smallest;
    ResultingNode->right = secondSmallest;
    TempVector.push_back(ResultingNode);

    //Then Assign tree
    hufftree = ResultingNode;
  }

  //Code build encoding table
  NodeLeft(StringNew, hufftree->left, hufftable);
  NodeRight(StringNew, hufftree->right, hufftable);

  skip:   //Skip to this point if only 1 character is in the message

  //Code to encode message
  for(int i=0; i<message.length(); i++){
    std::string StringPath = hufftable[message[i]];
    for(int j=0; j<StringPath.length(); j++){
      StringNew.push_back(StringPath[j]);
    }
  }

  return StringNew;
}

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree){
  std::string decodedmessage = "";
  hufftreeptr NodeCurrent = hufftree;
  for (int j=0; j<encodedmessage.size(); j++){
    //Checking if code is 0 or 1 in order to move left or right in hufftree
    if(encodedmessage[j]=='0'){
      NodeCurrent = NodeCurrent->left;
    }
    else{
      NodeCurrent = NodeCurrent->right;
    }
    //When current node is at leaf node we add character to a string
    if(NodeCurrent->character != '\0'){
      decodedmessage += NodeCurrent->character;
      NodeCurrent = hufftree;
    }
  }
  return decodedmessage;
}
