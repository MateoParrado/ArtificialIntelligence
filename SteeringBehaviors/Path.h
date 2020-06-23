#pragma once
#include "Vector.h"
#include "SDL.h"

//linked list node
struct Node
{
	Vector pos;
	Node* next;

	Node() :next(nullptr) {}
};

//structure to hold data for paths thatentities can follow
struct Path
{
public:
	bool isLoop;

	//first and last elements of the path, could be the same
	Node* first, * last;

	Path(bool isLoop = true) :isLoop(isLoop), first(nullptr), last(nullptr) {}

	//add a new node to the end of the list
	void addNode(Vector pos)
	{
		Node* temp = new Node();
		temp->pos = pos;

		if (!first)
		{
			first = temp;
			last = temp;
			return;
		}

		last->next = temp;
		last = temp;

		if (isLoop)
		{
			last->next = first;
		}
	}

	void draw(SDL_Renderer* r);

	~Path()
	{
		Node* curr = first;

		do {
			Node* temp = curr->next;
			delete curr;
			curr = temp;
		} while (curr != last);
	}
};