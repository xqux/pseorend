#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_MARKEDARROW_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_MARKEDARROW_HPP


// project's headers
#include "GraphicArrow.hpp"


namespace pseorend::graphic_primitives
{
	// this class marks the indentation for
	// the text and the head size of the arrow
	class MarkedArrow: public GraphicArrow
	{
		Q_OBJECT

	public: // creation and destruction of objects
		explicit MarkedArrow(QObject* parent = nullptr)
			: GraphicArrow(parent)
			, m_textIndent(), m_headSize() {}

	public: // manipulation of the text indent
		auto textIndent() const -> qreal
		{ return m_textIndent; }

		void setTextIndent(qreal indent)
		{ m_textIndent = indent; }

	public: // manipulation of the arrowhead
		auto headSize() const -> QSizeF const&
		{ return m_headSize; }

		void setHeadSize(QSizeF const& size)
		{ m_headSize = size; }

	private: // members
		qreal m_textIndent;
		QSizeF m_headSize;
	};
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_MARKEDARROW_HPP
