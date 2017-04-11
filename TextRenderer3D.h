#pragma once

#include "Common\DeviceResources.h"
#include "Content\ShaderStructures.h"

namespace HolographicFaceTracker {
	/*!
	 * \brief Holds all the parameters needed to draw a single render_char on the screen
	 */
	struct char_drawing_params {
		Windows::Foundation::Numerics::float2 start_uv;
		Windows::Foundation::Numerics::float2 end_uv;
		int pixels_to_advance;
	};

	struct render_char {
		VertexPositionTex top_left;
		VertexPositionTex top_right;
		VertexPositionTex bottom_left;
		VertexPositionTex bottom_right;
	};

	/*! 
	 * \brief Renders text in a 3D space
	 *
	 * For simplicity's sake, this class ignores kerning
	 */
	class TextRenderer3D : public DX::Resource {
	public:
		TextRenderer3D(std::shared_ptr<DX::DeviceResources> device_resources_in);

		/*!
		 * \brief Renders the specified string at the provided position
		 *
		 * The string always faces towards the viewer
		 *
		 * Because it's simple, this method re-builds the vertex buffer each time it's called. This is gross but it'll work
		 * for now
		 *
		 * \param string The string to draw
		 * \param start_pos The position in 3D space of the lower-left cormer of the string
		 */
		void draw_string_billboard(std::wstring const& string, Windows::Foundation::Numerics::float3 start_pos);

	private:
		// Data for the current drawing session
		Windows::Foundation::Numerics::float3 cur_char_pos;

		std::vector<render_char> characters_in_string;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
		Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader;


		// Static data, pretty much. This member is initialized in the constructor
		std::unordered_map<char, char_drawing_params> character_locations;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> vertex_buffer_layout;

		void create_vertex_description();
	};
}

