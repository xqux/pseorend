#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICARROW_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICARROW_HPP


// project's headers
#include "GraphicPrimitive.hpp"


namespace pseorend::graphic_primitives
{
	// this class represents the base wrapper for all figure primitives
	class GraphicArrow: public GraphicPrimitive
	{
		Q_OBJECT

	public: // creation and destruction of objects
		using GraphicPrimitive::GraphicPrimitive;

	public: // manipulation of the arrowhead
		virtual auto headRect() const -> QRectF = 0;
	};
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICARROW_HPP
