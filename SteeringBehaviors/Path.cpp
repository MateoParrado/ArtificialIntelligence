#include "Path.h"

void Path::draw(SDL_Renderer* r)
{
	if (!first || !first->next)
		return;

	Node* curr = first;

	while (curr != last)
	{
		SDL_RenderDrawLine(r, (int)curr->pos.getX(), (int)curr->pos.getY(),
						   (int)curr->next->pos.getX(), (int)curr->next->pos.getY());

		curr = curr->next;
	}

	if (isLoop)
	{
		SDL_RenderDrawLine(r, (int)first->pos.getX(), (int)first->pos.getY(),
						   (int)last->pos.getX(), (int)last->pos.getY());
	}
}
