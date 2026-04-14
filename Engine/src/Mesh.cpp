#include "Mesh.h"

bool Mesh::Initialize(ID3D11Device* device)
{
    if (meshData.GetVetices().empty()) {
        return false;
    }

    vertexBuffer = std::make_unique<Buffer>(BufferType::Vertex);

    if (!vertexBuffer->Create(device, sizeof(DirectX::XMFLOAT3), 
        static_cast<UINT>(meshData.GetVertCount()), meshData.GetVetices().data())) {
        return false;
    }


    return true;
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    if (vertexBuffer) {
        vertexBuffer->Bind(context);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->Draw(static_cast<UINT>(vertexBuffer->GetCount()), 0);
    }
}
