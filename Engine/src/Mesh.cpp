#include "Mesh.h"

bool Mesh::Initialize(ID3D11Device* device)
{
    if (meshData.GetVetices().empty() || meshData.GetIndices().empty()) {
        return false;
    }

    vertexBuffer = std::make_unique<Buffer>(BufferType::Vertex);

    if (!vertexBuffer->Create(device, sizeof(DirectX::XMFLOAT3), 
        static_cast<UINT>(meshData.GetVertCount()), meshData.GetVetices().data())) {
        return false;
    }

    indexBuffer = std::make_unique<Buffer>(BufferType::Index);

    if (!indexBuffer->Create(device, sizeof(uint32_t),
        static_cast<UINT>(meshData.GetIndexCount()), meshData.GetIndices().data())) {
        return false;
    }


    return true;
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    if (vertexBuffer && indexBuffer) {
        vertexBuffer->Bind(context);
        indexBuffer->Bind(context);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->DrawIndexed(static_cast<UINT>(indexBuffer->GetCount()),0, 0);
    }
}
