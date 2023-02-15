

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include "structs.h"
using namespace std;

PriorityQueue::PriorityQueue(){
    //DEFINE FIRST NODE IN QUEUE
    head=NULL;
};
void PriorityQueue::enque(Node* newnode){
    Node* start=head;
    //IF QUEUE IS EMPTY,ADD NEWNODE IN HEAD
    if(head==NULL){
        head=newnode;
        return;
    }
    //IF VAL OF NEWNODE IS SMALLER THAN HEAD,CHANGE HEAD NODE WITH NEWNODE
    if (head->token.val > newnode->token.val)
    {
        newnode->next = head;
        head = newnode;
    }
    //FIND POSITION FOR NEWNODE,AND CHANGE CURRENT NODE WITH NEWNODE
    else{
        while (start->next != NULL &&start->next->token.val <= newnode->token.val)
        {
            start = start->next;
        }
        newnode->next = start->next;
        start->next = newnode;
    }
};


Node* PriorityQueue::dequeue(){
    //IF QUEUE IS EMPTY RETURN NULL
    if(head==NULL){ 
        return NULL;
    }
    //ELSE MAKE HEAD MOVE ITS NEXT NODE ,AND RETURN PREVIOUS  HEAD
    else{
        Node* temp = head;
        head = head->next;
        return temp;
    }
    
};

Tree::Tree(){
    //DEFINE FIRST ELEMENT
    root=NULL;
    
};
Tree::~Tree(){
    //IF QUEUE IS NOT EMPTY DELETE ALL
    if(root != NULL)
        deleteTree(root);
    root=NULL;
};

void Tree::deleteTree(Node* node){
    //DELETE NODE WİTH POSTORDER WAY UNTIL NODE IS NULL
    if(node!=NULL){
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    return;
};
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    //MERGE TEMP1 AND TEMP2 IN TEMP NODE
    Node* temp=new Node();
    temp->token.val = temp1->token.val+temp2->token.val;
    temp->token.symbol = temp1->token.symbol+temp2->token.symbol;
    return temp;
    
};
void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 
    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;
    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};