#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICPRIMITIVE_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICPRIMITIVE_HPP


// qt
#include <QGraphicsItem>
#include <QPen>


namespace pseorend::graphic_primitives
{
	// this class represents the base wrapper for all primitives
	class GraphicPrimitive: public QObject, public QGraphicsItem
	{
		Q_OBJECT

	public: // creation and destruction of objects
		explicit GraphicPrimitive(QObject* parent = nullptr);

	public: // interaction with the text
		auto text() const -> QString const&
		{ return m_text; }

		void setText(QString const& text)
		{ m_text = text; }

		void clearText()
		{ m_text.clear(); }

	public: // interaction with the drawing set
		auto pen() const -> QPen const&
		{ return m_pen; }

		auto brush() const -> QBrush const&
		{ return m_brush; }

		void setPen(QPen const& pen)
		{ m_pen = pen; }

		void setBrush(QBrush const& brush)
		{ m_brush = brush; }

	protected: // display the text when hover (hover mode)
		void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

	private: // members
		QString m_text;

		QPen m_pen;
		QBrush m_brush;
	};
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_GRAPHICPRIMITIVE_HPP
