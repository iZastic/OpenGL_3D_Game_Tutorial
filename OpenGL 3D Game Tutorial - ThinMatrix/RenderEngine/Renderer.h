#ifndef RENDERER_H
#define RENDERER_H

#include "RawModel.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void Prepare();
	void Render(RawModel* model);
};

#endif // RENDERER_H