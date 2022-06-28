#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_SYNTACTIC_RELATIONS_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_SYNTACTIC_RELATIONS_HPP


// project's headers
#include "MarkedArrow.hpp"
#include "TextLimiter.hpp"


namespace pseorend::graphic_primitives::relations::details
{
	// qt enums
	using Qt::ArrowType;

	// a pair of points denoting a directed line segment
	using PointPair = QPair<QPointF const&, QPointF const&>;
}

// these classes contain everything for
// drawing and rendering arrows
namespace pseorend::graphic_primitives::relations::details
{
	class SingleArrow: public MarkedArrow, public TextLimiter
	{
		Q_OBJECT

	public: // creation and destruction of objects
		explicit SingleArrow(QObject* parent = nullptr)
			: MarkedArrow(parent), TextLimiter()
			, m_textBoundedLimit(), m_firstPos(), m_lastPos() {}

		explicit SingleArrow(QPointF const& startPos, QObject* parent = nullptr)
			: MarkedArrow(parent), TextLimiter()
			, m_textBoundedLimit(), m_firstPos(startPos), m_lastPos() {}

	public: // text limit rectangle
		auto textBoundedRect() const -> QRectF override;

	public: // checking text to display
		auto isFitText(QFontMetrics const& metrics) const -> bool override;
		auto isFitTextRect(QFontMetrics const& metrics) const -> bool override;

	public: // manipulation of the arrowhead
		auto headRect() const -> QRectF override;

	public: // the area (width or height), the text rectangle constraint
		auto textBoundedLimit() const -> qreal
		{ return m_textBoundedLimit; }

		void setTextBoundedLimit(qreal lim)
		{ m_textBoundedLimit = lim; }

	public: // area markup
		auto startPos() const -> QPointF const&
		{ return m_firstPos; }

		auto getLine() const -> QLineF
		{
			return QLineF(m_firstPos.x(), m_firstPos.y(),
			              m_lastPos.x(), m_lastPos.y());
		}

		auto getTailPoints() const -> PointPair
		{ return PointPair(m_firstPos, m_lastPos); }

		auto getHeadPoints() const -> PointPair
		{ return getTailPoints(); }

		void setStartPos(QPointF const& pos)
		{ m_firstPos = pos; }

		void setLine(qreal len, ArrowType direction);

	public: // drawing
		void paint(QPainter* painter, QStyleOptionGraphicsItem const*,
		           QWidget* = nullptr) override;

		void drawLine(QPainter* painter);
		void drawText(QPainter* painter);
		void drawHead(QPainter* painter);

		void drawLines(QPainter* painter)
		{ drawLine(painter); }

	public:
		auto boundingRect() const -> QRectF override;

	private: // members
		qreal m_textBoundedLimit;
		QPointF m_firstPos, m_lastPos;
	};

	class CornerArrow: public MarkedArrow, public TextLimiter
	{
		Q_OBJECT

	public: // creation and destruction of objects
		explicit CornerArrow(QObject* parent = nullptr)
			: MarkedArrow(parent), TextLimiter()
			, m_textBoundedLimit(), m_points(), m_boundedRect() {}

		explicit CornerArrow(QPointF const& startPos, QObject* parent = nullptr)
			: MarkedArrow(parent), TextLimiter()
			, m_textBoundedLimit(), m_points({startPos}), m_boundedRect() {}

	public: // text limit rectangle
		auto textBoundedRect() const -> QRectF override;

	public: // checking text to display
		auto isFitText(QFontMetrics const& metrics) const -> bool override;
		auto isFitTextRect(QFontMetrics const& metrics) const -> bool override;

	public: // manipulation of the arrowheads
		auto headRect() const -> QRectF override;

	public: // the area (width or height), the text rectangle constraint
		auto textBoundedLimit() const -> qreal
		{ return m_textBoundedLimit; }

		void setTextBoundedLimit(qreal lim);

	public: // area markup
		auto startPos() const -> QPointF const&
		{ return m_points.first(); }

		auto points() const -> QVector<QPointF> const&
		{ return m_points; }

		auto getTailPoints() const -> PointPair;
		auto getHeadPoints() const -> PointPair;

		void setStartPos(QPointF const& pos);
		void addLine(qreal len, ArrowType direction);

	public: // drawing
		void paint(QPainter* painter, QStyleOptionGraphicsItem const*,
		           QWidget* = nullptr) override;

		void drawLines(QPainter* painter);
		void drawText(QPainter* painter);
		void drawHead(QPainter* painter);

	public: // reserve bounded rectangle
		void reserveRect(QRectF const& rect);

	public:
		auto boundingRect() const -> QRectF override
		{ return m_boundedRect; }

	private: // members
		qreal m_textBoundedLimit;
		QVector<QPointF> m_points;
		QRectF m_boundedRect;
	};
}

namespace pseorend::graphic_primitives::relations
{
	using details::SingleArrow;
	using details::CornerArrow;
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_SYNTACTIC_RELATIONS_HPP
