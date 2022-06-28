#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICFIGURE_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICFIGURE_HPP


// project's headers
#include "GraphicPrimitive.hpp"


namespace pseorend::graphic_primitives
{
	// this class represents the base wrapper for all figure primitives
	class GraphicFigure: public GraphicPrimitive
	{
		Q_OBJECT

	public: // creation and destruction of objects
		explicit GraphicFigure(QObject* parent = nullptr)
			: GraphicPrimitive(parent)
			, m_figureRect() {}

		explicit GraphicFigure(QRectF const& figure, QObject* parent = nullptr)
			: GraphicPrimitive(parent)
			, m_figureRect(figure) {}

	public: // interaction with the rectangle of the figure
		auto figureRect() const -> QRectF const&
		{ return m_figureRect; }

		void setFigureRect(QRectF const& rect)
		{ m_figureRect = rect; }

	public:
		auto boundingRect() const -> QRectF override
		{ return figureRect(); }

	private: // members
		QRectF m_figureRect;
	};
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICFIGURE_HPP
