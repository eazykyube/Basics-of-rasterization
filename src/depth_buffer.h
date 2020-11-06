#pragma once


#include "triangle_rasterization.h"

using namespace linalg::ostream_overloads;

namespace cg
{

	class ZCulling : public TriangleRasterization
	{
	public:
		ZCulling(unsigned short width, unsigned short height, std::string objFile);
		virtual ~ZCulling();

		void Clear();

	protected:
		void DrawTriangle(cg::face face);
		void SetPixel(unsigned short x, unsigned short y, color color, float z);
		std::vector<float> depthBuffer;

	};

}
