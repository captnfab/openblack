/*******************************************************************************
 * Copyright (c) 2018-2022 openblack developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/openblack/openblack
 *
 * openblack is licensed under the GNU General Public License version 3.
 ******************************************************************************/

#include "TextureViewer.h"

#include "Graphics/Texture2D.h"
#include "Gui/Gui.h"
#include "Locator.h"

using namespace openblack;
using namespace openblack::gui;

TextureViewer::TextureViewer()
    : DebugWindow("Texture Viewer", ImVec2(950.0f, 780.0f))
{
}

void TextureViewer::Draw(Game& game)
{
	float fontSize = ImGui::GetFontSize();
	auto const& textures = Locator::resources::ref().GetTextures();

	_filter.Draw();

	ImGui::BeginChild("textures", ImVec2(fontSize * 15.0f, 0));
	auto textureSize = ImGui::GetItemRectSize();
	ImGui::BeginChild("texturesSelect", ImVec2(textureSize.x - 5, textureSize.y - ImGui::GetTextLineHeight() - 5), true);
	uint32_t displayedTexture = 0;

	textures.Each([this, &displayedTexture](entt::id_type id, entt::resource_handle<const graphics::Texture2D> texture) {
		if (_filter.PassFilter(texture->GetName().c_str()))
		{
			displayedTexture++;

			if (ImGui::Selectable(texture->GetName().c_str(), id == _selectedTexture))
			{
				_selectedTexture = id;
			}
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("%s", texture->GetName().c_str());
			}
		}
	});
	ImGui::EndChild();
	ImGui::Text("%u textures", displayedTexture);
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("viewer", ImVec2(fontSize * -15.0f, 0));

	auto texture = textures.Handle(_selectedTexture);
	if (texture)
	{
		const auto format = texture->GetFormat();
		std::string formatStr = std::to_string(format);
		if (format == bgfx::TextureFormat::R8)
		{
			formatStr = "R8";
		}
		else if (format == bgfx::TextureFormat::RGB8)
		{
			formatStr = "RGB8";
		}
		ImGui::Text("width: %u, height: %u, format: %s", texture->GetWidth(), texture->GetHeight(), formatStr.c_str());
		ImGui::Image(texture->GetNativeHandle(), ImVec2(512, 512));
	}

	ImGui::EndChild();
}

void TextureViewer::Update(Game& game, const Renderer& renderer) {}

void TextureViewer::ProcessEventOpen([[maybe_unused]] const SDL_Event& event) {}

void TextureViewer::ProcessEventAlways([[maybe_unused]] const SDL_Event& event) {}