#pragma once
#include <vector>
class Mesh
{
public:
	Mesh();
	~Mesh();
private:
	unsigned int vbo_;
	unsigned int vao_;
};
