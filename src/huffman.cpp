
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
#include "huffman.h"
#include "structs.h"

using namespace std;
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};

void Huffman::sortKey ()
{
  sortedKey = key;
  sort (sortedKey.begin (), sortedKey.end ());
  
};

void Huffman::findFrequency ()
{
//sort key    
  sortKey ();
  //count same symbol in sortedkey
  for (auto i = sortedKey.begin (); i != sortedKey.end (); i++)
  {
      //counter
      int value = 0;
      for (auto j = sortedKey.begin (); j != sortedKey.end (); j++)
	    {
	  //if symbols are same, increase counter
        if (*i == *j)
        {
            value++;
        }
	    }
      //define new node with its val=counter,its symbol=current char in loop
      Node *y = new Node ();
      y->token.val = value;
      y->token.symbol = *i;
      //if current char is not same with previous char in loop, add node in queue
      if (*i != *(i - 1)){
	        queue.enque (y);
	    }
      //else delete node
      else{
	        delete y;
	    }
  }
};

void Huffman::createHuffmanTree ()
{
  //create queue
  findFrequency ();
  //take first two of queue,
  Node *a = queue.dequeue ();
  Node *b = queue.dequeue ();
  //until queue is empty
  while (b != NULL)
    {
        //merge two nodes and put in root
      huffmanTree.root = huffmanTree.mergeNodes (a, b);
      //enqueue root in queue
      queue.enque (huffmanTree.root);
      //create left and right subtree
      huffmanTree.root->left = a;
      huffmanTree.root->right = b;
    //take first two of queue again
      a = queue.dequeue ();
      b = queue.dequeue ();
    }
};

void Huffman::printHuffmanTree ()
{
  huffmanTree.printTree (huffmanTree.root, 0);
};

string Huffman::getTokenBinary (char tokenChar, Node * traverse,string tokenBinary)
{
//change desired char to string
  string data = "";
  data += tokenChar;
  // s is symbol of current node
  string s = traverse->token.symbol;
  //if desired char is equal to symbol of current node, return current tokenBinary
  if (data == s)
  {
      return tokenBinary;
  }
    //str1 is symbol of root of left subtree
  string str1 = traverse->left->token.symbol;
  //str2 is symbol of root of right subtree
  string str2 = traverse->right->token.symbol;
    // unsize int found1 and found2 hold whether desired char is in left or rigt subtree or not
  size_t found1 = str1.find (data);
  size_t found2 = str2.find (data);
  //if desired char is present in symbol of left subtree, return current left tree with adding 0 to tokenBinary
  if (found1 != string::npos)
  {
      return getTokenBinary (tokenChar, traverse->left, tokenBinary + "0");
  }
//else if desired char is present in symbol of right subtree, return current right tree with adding 0 to tokenBinary
  else if (found2 != string::npos)
  {
      return getTokenBinary (tokenChar, traverse->right, tokenBinary + "1");

  }
    //else char isnt in tree
  else
  {
      return "";
  }
};

int Huffman::findDepth (Node * r, char x)
{
    //convert char to string
  string str;
  str += x;
  // if tree is empty
  if (r == NULL)
    return -1;

  // define distance is -1
  int d = -1;

  // Check if desired char is symbol current node or check if it is present in the left or right subtree
  if ((r->token.symbol == str)|| (d = findDepth (r->left, x)) >= 0 || (d = findDepth (r->right, x)) >= 0)

    // increase depth and Return depth of the node
    return d + 1;

  return d;
};

void Huffman::encodePassword (string password)
{
  Node *r = huffmanTree.root;
//chars in given password
  for (auto i = password.begin (); i != password.end (); i++)
    {
        //find depth of current char,convert int to string
      string str = to_string (findDepth (r, *i));
      //add it to encodedValPassword
      encodedValPassword += str;
      Node *p = huffmanTree.root;
      string x = "";
      //find binary of current char , add it to encodedBinaryPassword
      encodedBinaryPassword += getTokenBinary (*i, p, x);
    }

};


void Huffman::printEncodedPassword ()
{
  cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
  cout << "Encoded Password Value: " << encodedValPassword << endl;
};

void Huffman::decodePassword (string encodedBinaryPassword, string encodedValPassword)
{
    //it keeps iterator to start binary of next char in encodedBinaryPassword
  int k = 0;
  int j = 0;
  //initilaze first char in string
  string h = "(";
  int s = encodedValPassword.size ();
  //for size of encodedValPassword
  for (int i = 0; i != s; i++)
    {
        //convert char to int
        int p = int (encodedValPassword[i]) - 48;
        //for depth of current char
        for (j = 0; j != p; j++)
    	{
    	    //add binary of current char
    	  h += encodedBinaryPassword[j + k];
    	}
    	//after binary, adding another string belongs to current char
        h += "(";
        h += encodedValPassword[i];
        h += ")";
        int a = encodedValPassword.size ();
        if (i < a - 1){
    	    h += ",";
        }
        //update k to start binary of next char in encodedBinaryPassword
        k += j;
    }
    //end of strings
    h += ")";
    //decode h
    decodeToken (h);
};


void Huffman::decodeToken (string encodedToken)
{
  Node *g = huffmanTree.root;

  int s = encodedToken.size ();
  //for size of encodedToken 
  for (int i = 1; i != s; i++)
    {
        //current char of string
      char c = encodedToken[i];
      if ((int (c) - 48) == 0)
	    {
	      //if c=0, go left
	      g = g->left;
	    }
	  //else if c=1, go right
      else if ((int (c) - 48) == 1)
	    {
	      g = g->right;
	    }
	  //else if c = '(' move until c = ')'
      else if (c == '(')
      {
        decodedPassword += g->token.symbol;
        while (c != ')')
        {
          i++;
          c = encodedToken[i];
        }
      }
	  //else if c = ',' it means it is in begining of next char,refresh g
      else if (c == ',')
	    {
	      g = huffmanTree.root;
	    }
	  //else it means end of string,quit function
      else
	    {
	      return;
	    }   
    }
};

void Huffman::printDecodedPassword ()
{
  cout << "Decoded Password: " << decodedPassword << endl;
};
