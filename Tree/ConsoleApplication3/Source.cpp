#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue> 
#include<cstring>
using namespace std;
ofstream fout("output.txt");
ifstream fin("input.txt");
struct node{
	int value;
	struct node *left=NULL;
	struct node *right=NULL;
	struct node *parent=NULL;
}*head;
void init(int value){
	head = new node();
	head->value = value;
}
void insert(int value){
		node *current = head;
		while (1){
			if (current->value < value){ 
				if (current->right == NULL)
				{
					current->right = new node();
					current->right->value = value;
					current->right->parent = current;
					break;
				}
				else{ current = current->right; }
			}
			else if (current->value > value) {
				if (current->left == NULL)
				{
					current->left = new node();
					current->left->value = value;
					current->left->parent = current;
					break;
				}
				else{ current = current->left; }
			}
			else{break;}
		}
}
void print(node* n) {
	if (n != NULL){
		fout << n->value <<endl;
		print(n->left);
		print(n->right);
	}
}
void del(int value){
	node *current = head;
	while (1){
		if (current == NULL){
			return;
		}
		if (current->value < value){
			current = current->right; 
		}
		else if (current->value > value) {
			current = current->left; 
		}
		else{ break; }
	}
	if (current->left == NULL &&current->right == NULL &&current->parent==NULL){
		head = NULL;
	}
	else if (current->left == NULL &&current == head){
		head = current->right;
		current = NULL;
	}
	else if (current->right == NULL &&current == head){
		head = current->left;
		current = NULL;
	}
	else if (current->left == NULL &&current->right == NULL){
		if (current->parent->right == current) current->parent->right = NULL;
		else current->parent->left = NULL;
		current = NULL;
		delete current;
	}
	else if (current->left == NULL){
		if (current->parent->right == current) current->parent->right = current->right;
		else current->parent->left = current->right;
		current = NULL;
		delete current;

	}
	else if (current->right == NULL){
		if (current->parent->right == current) current->parent->right = current->left;
		else current->parent->left = current->left;
		current = NULL;
		delete current;
	}
	else{
		node* h = current;
		current = current->right;
		while (1){
			if (current->left == NULL)
				break;
			current = current->left;
		}
		h->value = current->value;
		if (current->right == NULL)
		{
			if (current->parent->right == current)current->parent->right = NULL;
			else current->parent->left = NULL;
		}
		else{
			if (current->parent->right == current) current->parent->right = current->right;
			else current->parent->left = current->right;
		}
	}
}
int main()
{
	string s;
	string d;
	getline(fin, d);
	getline(fin, s);
	if (getline(fin, s))
		init(atoi(s.c_str()));
	while (getline(fin, s)){
		insert(atoi(s.c_str()));
	}
	del(atoi(d.c_str()));
	print(head);
	fout.close();
	fin.close();
	return 0;
}