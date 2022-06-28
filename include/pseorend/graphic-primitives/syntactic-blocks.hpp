#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_SYNTACTIC_BLOCKS_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_SYNTACTIC_BLOCKS_HPP


// project's headers
#include "GraphicFigure.hpp"
#include "TextLimiter.hpp"


// these classes contain everything for
// drawing and rendering figures
namespace pseorend::graphic_primitives::blocks
{
	class Alg: public GraphicFigure, public TextLimiter
	{
		Q_OBJECT

	public: // creation and destruction of objects
		using GraphicFigure::GraphicFigure;

	public: // text limit rectangle
		auto textBoundedRect() const -> QRectF override
		{ return boundingRect(); }

	public: // checking text to display
		auto isFitText(QFontMetrics const& metrics) const -> bool override;
		auto isFitTextRect(QFontMetrics const& metrics) const -> bool override;

	public:
		void paint(QPainter* painter, QStyleOptionGraphicsItem const*,
		           QWidget* = nullptr) override;

		void drawFigure(QPainter* painter);
		void drawText(QPainter* painter);
	};

	class Process: public GraphicFigure, public TextLimiter
	{
		Q_OBJECT

	public: // creation and destruction of objects
		using GraphicFigure::GraphicFigure;

	public: // text limit rectangle
		auto textBoundedRect() const -> QRectF override
		{ return boundingRect(); }

	public: // checking text to display
		auto isFitText(QFontMetrics const& metrics) const -> bool override;
		auto isFitTextRect(QFontMetrics const& metrics) const -> bool override;

	public:
		void paint(QPainter* painter, QStyleOptionGraphicsItem const*,
		           QWidget* = nullptr) override;

		void drawFigure(QPainter* painter);
		void drawText(QPainter* painter);
	};

	class IO: public GraphicFigure, public TextLimiter
	{
		Q_OBJECT

	public: // creation and destruction of objects
		explicit IO(QObject* parent = nullptr)
			: GraphicFigure(parent)
			, m_slope() {}

		explicit IO(QRectF const& figure, qreal slope, QObject* parent = nullptr)
			: GraphicFigure(figure, parent)
			, m_slope(slope) {}

	public: // interaction with the slope of the parallelogram
		auto slope() const -> qreal
		{ return m_slope; }

		void setSlope(qreal slope)
		{ m_slope = slope; }

	public: // text limit rectangle
		auto textBoundedRect() const -> QRectF override
		{ return boundingRect(); }

	public: // checking text to display
		auto isFitText(QFontMetrics const& metrics) const -> bool override;
		auto isFitTextRect(QFontMetrics const& metrics) const -> bool override;

	public:
		void paint(QPainter* painter, QStyleOptionGraphicsItem const*,
		           QWidget* = nullptr) override;

		void drawFigure(QPainter* painter);
		void drawText(QPainter* painter);

	private: // members
		qreal m_slope;
	};

	class Decision: public GraphicFigure, public TextLimiter
	{
		Q_OBJECT

	public: // creation and destruction of objects
		using GraphicFigure::GraphicFigure;

	public: // text limit rectangle
		auto textBoundedRect() const -> QRectF override
		{ return boundingRect(); }

	public: // checking text to display
		auto isFitText(QFontMetrics const& metrics) const -> bool override;
		auto isFitTextRect(QFontMetrics const& metrics) const -> bool override;

	public:
		void paint(QPainter* painter, QStyleOptionGraphicsItem const*,
		           QWidget* = nullptr) override;

		void drawFigure(QPainter* painter);
		void drawText(QPainter* painter);
	};
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_SYNTACTIC_BLOCKS_HPP
