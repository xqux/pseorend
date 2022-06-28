// related header
#include "syntactic-relations.hpp"

// project's headers
#include "drawing-visualization.inl"
#include "figure-making.hpp"
#include "text-facilities.inl"


// qt enums
using Qt::AlignmentFlag::AlignBottom;
using Qt::AlignmentFlag::AlignHCenter;
using Qt::AlignmentFlag::AlignLeft;
using Qt::AlignmentFlag::AlignRight;
using Qt::AlignmentFlag::AlignTop;
using Qt::AlignmentFlag::AlignVCenter;
using Qt::ArrowType::DownArrow;
using Qt::ArrowType::LeftArrow;
using Qt::ArrowType::NoArrow;
using Qt::ArrowType::RightArrow;
using Qt::ArrowType::UpArrow;
using Qt::ArrowType;
using Qt::TextFlag::TextSingleLine;

// syntactic arrows
using pseorend::graphic_primitives::relations::CornerArrow;
using pseorend::graphic_primitives::relations::SingleArrow;

// namespaces containing data specifically for this file
using namespace pseorend::graphic_primitives::drawing_visualization;
using namespace pseorend::graphic_primitives::figure_making;
using namespace pseorend::graphic_primitives::text_facilities;


// service functions
constexpr auto getDirection(QPointF const& start, QPointF const& end) -> ArrowType
{
	if (start.x() > end.x())
	{ return LeftArrow; }
	else if (start.x() < end.x())
	{ return RightArrow; }
	else if (start.y() > end.y())
	{ return UpArrow; }
	else if (start.y() < end.y())
	{ return DownArrow; }

	assert(false && "points can't be equal.");
}

// these functions compresses the code
template <typename T>
inline void drawArrow(T* obj, QPainter* painter)
{
	assert(obj != nullptr && painter != nullptr &&
	       "incorrectly passed values for drawing a primitive");

	// preparation
	painter->setPen(obj->pen());
	painter->setBrush(obj->brush());

	// drawing
	obj->drawLines(painter);
	obj->drawText(painter);
	obj->drawHead(painter);

	// visualization
	auto boundingRect = obj->boundingRect();
	highlightArea(painter, boundingRect);
}

template <typename T>
inline auto tryDrawText(T* obj, QPainter* painter,
                        QFontMetricsF const& metrics,
                        QRectF const& textBoundedRect,
                        QString const& text) -> bool
{
	assert(obj != nullptr && painter != nullptr &&
	       "incorrectly passed values for drawing a primitive");

	auto flags = static_cast<int>(TextSingleLine);

	// align text to bounding rectangle
	auto const& [start, finish] = obj->getTailPoints();
	auto direction = getDirection(start, finish);

	switch (direction)
	{
	case UpArrow:
		flags |= static_cast<int>(AlignHCenter | AlignBottom);
		break;

	case DownArrow:
		flags |= static_cast<int>(AlignHCenter | AlignTop);
		break;

	case LeftArrow:
		flags |= static_cast<int>(AlignVCenter | AlignRight);
		break;

	case RightArrow:
		flags |= static_cast<int>(AlignVCenter | AlignLeft);
		break;

	default:
		assert(false && "impossible branch of program execution.");
	}

	// check if the text is fit
	auto textRect = metrics.boundingRect(textBoundedRect, flags, text);

	if (!isFitTextSize(textBoundedRect.size(), textRect.size()))
	{ return false; }

	// drawing
	painter->eraseRect(textRect);
	painter->drawText(textRect, flags, text);

	// visualization
	highlightArea(painter, textBoundedRect);
	highlightArea(painter, textRect);

	return true;
}

template <typename T>
inline void drawHead(T* obj, QPainter* painter)
{
	assert(obj != nullptr && painter != nullptr &&
	       "incorrectly passed values for drawing a primitive");

	auto headRect = obj->headRect();

	// preparing a triangle head
	auto const& [start, finish] = obj->getHeadPoints();
	auto direction = getDirection(start, finish);
	auto head = makeTringlePattern(headRect, direction);

	// drawing
	painter->drawPath(head);

	// visualization
	highlightArea(painter, headRect);
}

template <typename T>
inline auto textBoundedRect(T* obj) -> QRectF
{
	auto const& [start, finish] = obj->getTailPoints();
	auto direction = getDirection(start, finish);

	switch (direction)
	{
	case UpArrow:
		return QRectF(start.x() - obj->textBoundedLimit() * qreal(0.5),
		              finish.y() + obj->headSize().height() + obj->pen().width(),
		              obj->textBoundedLimit(),
		              start.y() - finish.y() - obj->textIndent() -
		                  obj->headSize().height() - obj->pen().width());

	case DownArrow:
		return QRectF(start.x() - obj->textBoundedLimit() * qreal(0.5),
		              start.y() + obj->textIndent(),
		              obj->textBoundedLimit(),
		              finish.y() - start.y() - obj->textIndent() -
		                  obj->headSize().height() - obj->pen().width());

	case LeftArrow:
		return QRectF(finish.x() + obj->headSize().width() + obj->pen().width(),
		              start.y() - obj->textBoundedLimit() * qreal(0.5),
		              start.x() - finish.x() - obj->textIndent() -
		                  obj->headSize().width() - obj->pen().width(),
		              obj->textBoundedLimit());

	case RightArrow:
		return QRectF(start.x() + obj->textIndent(),
		              start.y() - obj->textBoundedLimit() * qreal(0.5),
		              finish.x() - start.x() - obj->textIndent() -
		                  obj->headSize().width() - obj->pen().width(),
		              obj->textBoundedLimit());

	default:
		assert(false && "impossible branch of program execution.");
	}
}

template <typename T>
inline auto headRect(T* obj) -> QRectF
{
	auto const& [start, finish] = obj->getHeadPoints();
	auto direction = getDirection(start, finish);
	auto headSize = obj->headSize();

	switch (direction)
	{
	case UpArrow:
		return QRectF(finish.x() - headSize.width() * qreal(0.5),
		              finish.y(),
		              headSize.width(), headSize.height());

	case DownArrow:
		return QRectF(finish.x() - headSize.width() * qreal(0.5),
		              finish.y() - headSize.height(),
		              headSize.width(), headSize.height());

	case LeftArrow:
		return QRectF(finish.x(),
		              finish.y() - headSize.height() * qreal(0.5),
		              headSize.width(), headSize.height());

	case RightArrow:
		return QRectF(finish.x() - headSize.width(),
		              finish.y() - headSize.height() * qreal(0.5),
		              headSize.width(), headSize.height());

	default:
		assert(false && "impossible branch of program execution.");
	}
}


auto SingleArrow::textBoundedRect() const -> QRectF
{ return ::textBoundedRect(this); }

auto SingleArrow::isFitText(QFontMetrics const& metrics) const -> bool
{ return ::isFitText(text(), textBoundedRect(), metrics); }

auto SingleArrow::isFitTextRect(QFontMetrics const& metrics) const -> bool
{ return ::isFitTextRect(text(), defaultText(), textBoundedRect(), metrics); }

auto SingleArrow::headRect() const -> QRectF
{ return ::headRect(this); }

void SingleArrow::setLine(qreal len, ArrowType direction)
{
	switch (direction)
	{
	case UpArrow:
		m_lastPos = QPointF(m_firstPos.x(), m_firstPos.y() - len);
		break;

	case DownArrow:
		m_lastPos = QPointF(m_firstPos.x(), m_firstPos.y() + len);
		break;

	case LeftArrow:
		m_lastPos = QPointF(m_firstPos.x() - len, m_firstPos.y());
		break;

	case RightArrow:
		m_lastPos = QPointF(m_firstPos.x() + len, m_firstPos.y());
		break;

	default:
		assert(false && "direction isn't valid value.");
	}
}

void SingleArrow::paint(QPainter* painter, QStyleOptionGraphicsItem const*, QWidget*)
{ ::drawArrow(this, painter); }

void SingleArrow::drawLine(QPainter* painter)
{
	auto const& [start, finish] = getTailPoints();
	painter->drawLine(QLineF(start.x(), start.y(),
	                         finish.x(), finish.y()));
}

void SingleArrow::drawText(QPainter* painter)
{ ::drawText(this, painter, tryDrawText<SingleArrow>); }

void SingleArrow::drawHead(QPainter* painter)
{ ::drawHead(this, painter); }

auto SingleArrow::boundingRect() const -> QRectF
{
	auto const& [start, finish] = getTailPoints();
	auto direction = getDirection(start, finish);

	switch (direction)
	{
	case UpArrow:
		return QRectF(start.x() - textBoundedLimit() * qreal(0.5),
		              finish.y(),
		              textBoundedLimit(),
		              start.y() - finish.y());

	case DownArrow:
		return QRectF(start.x() - textBoundedLimit() * qreal(0.5),
		              start.y(),
		              textBoundedLimit(),
		              finish.y() - start.y());

	case LeftArrow:
		return QRectF(finish.x(),
		              start.y() - textBoundedLimit() * qreal(0.5),
		              start.x() - finish.x(),
		              textBoundedLimit());

	case RightArrow:
		return QRectF(start.x(),
		              start.y() - textBoundedLimit() * qreal(0.5),
		              finish.x() - start.x(),
		              textBoundedLimit());

	default:
		assert(false && "impossible branch of program execution.");
	}
}


auto CornerArrow::textBoundedRect() const -> QRectF
{ return ::textBoundedRect(this); }

auto CornerArrow::isFitText(QFontMetrics const& metrics) const -> bool
{ return ::isFitText(text(), textBoundedRect(), metrics); }

auto CornerArrow::isFitTextRect(QFontMetrics const& metrics) const -> bool
{ return ::isFitTextRect(text(), defaultText(), textBoundedRect(), metrics); }

auto CornerArrow::headRect() const -> QRectF
{ return ::headRect(this); }

void CornerArrow::setTextBoundedLimit(qreal lim)
{
	m_textBoundedLimit = lim;

	if (m_points.size() >= 2)
	{ reserveRect(textBoundedRect()); }
}

auto CornerArrow::getTailPoints() const -> PointPair
{
	auto size = m_points.size();
	assert(size >= 2 && "the arrow doesn't contain lines to determine the direction.");

	auto const& start = m_points[0];
	auto const& finish = m_points[1];

	return PointPair(start, finish);
}

auto CornerArrow::getHeadPoints() const -> PointPair
{
	auto size = m_points.size();
	assert(size >= 2 && "the arrow doesn't contain lines to determine the direction.");

	auto const& start = m_points[size - 2];
	auto const& finish = m_points[size - 1];

	return PointPair(start, finish);
}

void CornerArrow::setStartPos(QPointF const& pos)
{
	m_points.clear();
	m_points.append(pos);
}

void CornerArrow::addLine(qreal len, ArrowType direction)
{
	assert(!m_points.isEmpty() && "starting point not set.");

	// adding a line based on its direction
	auto last = m_points.last();
	auto point = QPointF();

	switch (direction)
	{
	case UpArrow:
		point = QPointF(last.x(), last.y() - len);
		reserveRect(QRectF(point, QSizeF(pen().width(), len)));
		break;

	case DownArrow:
		point = QPointF(last.x(), last.y() + len);
		reserveRect(QRectF(last, QSizeF(pen().width(), len)));
		break;

	case LeftArrow:
		point = QPointF(last.x() - len, last.y());
		reserveRect(QRectF(point, QSizeF(len, pen().width())));
		break;

	case RightArrow:
		point = QPointF(last.x() + len, last.y());
		reserveRect(QRectF(last, QSizeF(len, pen().width())));
		break;

	default:
		assert(false && "direction isn't valid value.");
	}

	m_points.append(point);

	// reserve tail line rectangle
	if (m_points.size() == 2)
	{ reserveRect(textBoundedRect()); }
}

void CornerArrow::paint(QPainter* painter, QStyleOptionGraphicsItem const*, QWidget*)
{ ::drawArrow(this, painter); }

void CornerArrow::drawLines(QPainter* painter)
{
	for (auto i = 1; i < m_points.size(); ++i)
	{
		auto const& start = m_points[i - 1];
		auto const& finish = m_points[i];

		painter->drawLine(QLineF(start.x(), start.y(),
		                         finish.x(), finish.y()));
	}
}

void CornerArrow::drawText(QPainter* painter)
{ ::drawText(this, painter, tryDrawText<CornerArrow>); }

void CornerArrow::drawHead(QPainter* painter)
{ ::drawHead(this, painter); }

void CornerArrow::reserveRect(QRectF const& rect)
{ m_boundedRect = m_boundedRect.united(rect); }
