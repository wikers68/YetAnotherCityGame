#pragma once

/*
*	Class with common data either for static and dynamic object
*/

class C3DObject
{
public:
	C3DObject();
	~C3DObject();

	/*
	*	To initialize the object, we use a void* type for data.
	*	We that, we can pass any data format for static object, dynamic, sprite...
	*/
	virtual void Initialize(void *data) = 0;
	virtual void Draw(float delta_t = 0.0f) = 0;
};

