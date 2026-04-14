#include "Object.h"
#include "Mesh.h"
#include "Shader.h"

Object::Object(std::string name, Mesh* mesh) : 
name(name), mesh(mesh), shader(new Shader())
{

}
Object::~Object()
{
	delete shader;
	delete mesh;
}
bool Object::Initialize(ID3D11Device* device) {
	if (shader) {
		if (!shader->CreateVertexShader(device, L"../Engine/Shaders/BasicShader.hlsl ")) {
			return false;
		}
		if (!shader->CreatePixelShader(device, L"../Engine/Shaders/BasicShader.hlsl")) {
			return false;
		}

	}
	else
	{
		return false;
	}

	if (mesh) {
		return mesh->Initialize(device);
	}
	
	return false;
}
void Object::Render(ID3D11DeviceContext* context) {
	if (!isVisiable || !mesh || !shader) {
		return;
	}

	shader->Bind(context);
	mesh->Render(context);

}

