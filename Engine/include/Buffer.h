#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <D3D11.h>
#include <wrl/client.h>

enum class BufferType {
	Vertex,
	Index,
	Constant,
	Unknown
};


class Buffer
{
public:
	Buffer(BufferType type) : type(type){}
	~Buffer() = default;

	bool Create(
		ID3D11Device* device,
		UINT elementSize,
		UINT elementCount,
		const void* initData = nullptr,
		bool dynamic = false,
		bool cpuAccess = false
	);

	void Bind(ID3D11DeviceContext* context, UINT slot = 0) const;
	void Update(ID3D11DeviceContext* context, const void* data
	,size_t size);

	UINT GetCount() const { return count; }
	ID3D11Buffer* Get() const { return buffer.Get(); }
	BufferType GetType() { return this->type; }
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

	BufferType type = BufferType::Unknown;

	UINT stride = 0;
	UINT count = 0;
	bool dynamic = 0;
};

#endif // !_BUFFER_H_
