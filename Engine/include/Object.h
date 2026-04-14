#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <D3D11.h>

class Mesh;
class Shader;

class Object
{
public:
	Object(std::string name = "Object", Mesh* mesh = nullptr);
	virtual ~Object();

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* context);


	void SetName(const std::string name) { this->name = name; }
	const std::string& GetName() { return this->name; }

	bool IsActive() { return isActive; }
	void SetActive(bool bEnable) { this->isActive = bEnable; }

	bool IsVisiable() { return isVisiable; }
	void SetVisiable(bool bEnable) { this->isVisiable = bEnable; }
private:
	std::string name;

	bool isActive = true;
	bool isVisiable = true;

	Mesh* mesh;
	Shader* shader;
};

#endif // !_OBJECT_H_
