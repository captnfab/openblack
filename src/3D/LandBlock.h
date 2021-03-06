/* OpenBlack - A reimplementation of Lionheads's Black & White engine
 *
 * OpenBlack is the legal property of its developers, whose names
 * can be found in the AUTHORS.md file distributed with this source
 * distribution.
 *
 * OpenBlack is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * OpenBlack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenBlack. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#ifndef OPENBLACK_LANDBLOCK_H
#define OPENBLACK_LANDBLOCK_H

#include <stdexcept>

#include <stdint.h>
#include <Graphics/OpenGL.h>
#include <glm/glm.hpp>

#include <Graphics/Mesh.h>
#include <Graphics/ShaderProgram.h>

#include "LandCell.h"

#define OPENBLACK_LANDISLAND_HEIGHT_UNIT 0.67f
#define OPENBLACK_LANDBLOCK_TOTAL_CELLS 289

namespace OpenBlack
{
	struct LandVertex
	{
		GLfloat position[3];
		GLfloat weight[3]; // interpolated
		GLubyte firstMaterialID[3];
		GLubyte secondMaterialID[3];
		GLubyte materialBlendCoefficient[3];
		GLubyte lightLevel;
		GLfloat waterAlpha;

		LandVertex(glm::vec3 _position, glm::vec3 _weight,
			GLubyte mat1, GLubyte mat2, GLubyte mat3,
			GLubyte mat4, GLubyte mat5, GLubyte mat6,
			GLubyte blend1, GLubyte blend2, GLubyte blend3,
			GLubyte _lightLevel, GLfloat _alpha)
		{
			position[0] = _position.x; position[1] = _position.y; position[2] = _position.z;
			weight[0] = _weight.x; weight[1] = _weight.y; weight[2] = _weight.z;
			firstMaterialID[0] = mat1; firstMaterialID[1] = mat2; firstMaterialID[2] = mat3;
			secondMaterialID[0] = mat4; secondMaterialID[1] = mat5; secondMaterialID[2] = mat6;
			materialBlendCoefficient[0] = blend1; materialBlendCoefficient[1] = blend2; materialBlendCoefficient[2] = blend3;
			lightLevel = _lightLevel; waterAlpha = _alpha;
		}
	};

	class LandIsland;

	class LandBlock
	{
	public:
		LandBlock();

		void LoadFromFile(void* block, size_t block_size);
		LandCell* GetCells() {
			return _cells;
		};
		glm::ivec2* GetBlockPosition() { return &_blockPosition; }
		glm::vec2* GetMapPosition() { return &_mapPosition; }

		void Draw(ShaderProgram* program);
		void BuildMesh(LandIsland* island);
	private:
		LandCell _cells[OPENBLACK_LANDBLOCK_TOTAL_CELLS];
		uint32_t _index;
		glm::ivec2 _blockPosition;
		glm::vec2 _mapPosition;

		std::vector<LandVertex> buildVertexList(LandIsland* island);
		std::unique_ptr<Mesh> _mesh;
	};
}

#endif
