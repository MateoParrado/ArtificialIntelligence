#include "Entity.h"
#include <iostream>

using namespace std;

int Entity::nextId = 0;

void Entity::display(string s)
{
	cout << name << ": " << s << endl;
}