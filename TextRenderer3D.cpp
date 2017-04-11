#include "pch.h"
#include "TextRenderer3D.h"
#include "Common\DirectXHelper.h"


HolographicFaceTracker::TextRenderer3D::TextRenderer3D(std::shared_ptr<DX::DeviceResources> device_resources_in) : DX::Resource(device_resources_in) {
	create_sahders();

}


void HolographicFaceTracker::TextRenderer3D::draw_string_billboard(std::wstring const & string, Windows::Foundation::Numerics::float3 start_pos) {}

void HolographicFaceTracker::TextRenderer3D::create_sahders() {
	auto load_vs = DX::ReadDataAsync(L"ms-appx:///FontVertexShader.cso");

	auto create_vs = load_vs.then([this](auto& file_data) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateVertexShader(
				fileData.data(),
				fileData.size(),
				nullptr,
				&vertex_shader
			)
		);

		constexpr auto vertex_description = std::array<D3D11_INPUT_ELEMENT_DESC, 2>{ {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexPositionTex, pos), D3D11_INPUT_PER_VERTEX_DATA },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, offsetof(VertexPositionTex, tex), D3D11_INPUT_PER_VERTEX_DATA }
			} };

		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreateInputLayout(
				vertex_description.data(),
				vertex_description.size(),
				file_data.data(),
				file_data.size(),
				&input_layout
			)
		);
	});

	auto load_ps = DX::ReadDataAsync(L"ms-appx:///FontPixelShader.cso");

	auto create_ps = load_ps.then([this](auto& file_data) {
		DX::ThrowIfFailed(
			m_deviceResources->GetD3DDevice()->CreatePixelShader(
				file_data.data(),
				file_data.size(),
				nullptr,
				&pixel_shader
			)
		);
	});

	auto shader_task_group = create_vs && create_ps;
}