// related header
#include "syntactic-blocks.hpp"

// project's headers
#include "drawing-visualization.inl"
#include "figure-making.hpp"
#include "text-facilities.inl"


// qt enums
using Qt::AlignmentFlag::AlignCenter;
using Qt::TextFlag::TextWordWrap;

// syntactic figures
using pseorend::graphic_primitives::blocks::Alg;
using pseorend::graphic_primitives::blocks::Process;
using pseorend::graphic_primitives::blocks::IO;
using pseorend::graphic_primitives::blocks::Decision;

// namespaces containing data specifically for this file
using namespace pseorend::graphic_primitives::drawing_visualization;
using namespace pseorend::graphic_primitives::figure_making;
using namespace pseorend::graphic_primitives::text_facilities;


// these functions compresses the code
template <typename T>
inline void drawFigure(T* obj, QPainter* painter)
{
	assert(obj != nullptr && painter != nullptr &&
	       "incorrectly passed values for drawing a primitive");

	// preparation
	painter->setPen(obj->pen());
	painter->setBrush(obj->brush());

	// drawing
	obj->drawFigure(painter);
	obj->drawText(painter);

	// visualization
	highlightArea(painter, obj->figureRect());
}

template <typename T>
inline auto tryDrawText(T* obj, QPainter* painter,
                        QFontMetricsF const& metrics,
                        QRectF const& textBoundedRect,
                        QString const& text) -> bool
{
	assert(obj != nullptr && painter != nullptr &&
	       "incorrectly passed values for drawing a primitive");

	auto flags = static_cast<int>(AlignCenter) |
	             static_cast<int>(TextWordWrap);

	// check if the text is fit
	auto textRect = metrics.boundingRect(textBoundedRect, flags, text);

	if (!isFitTextSize(textBoundedRect.size(), textRect.size()))
	{ return false; }

	// drawing
	painter->drawText(textRect, flags, text);

	// visualization
	highlightArea(painter, textBoundedRect);
	highlightArea(painter, textRect);

	return true;
}


auto Alg::isFitText(QFontMetrics const& metrics) const -> bool
{ return ::isFitText(text(), textBoundedRect(), metrics); }

auto Alg::isFitTextRect(QFontMetrics const& metrics) const -> bool
{ return ::isFitTextRect(text(), defaultText(), textBoundedRect(), metrics); }

void Alg::paint(QPainter* painter, QStyleOptionGraphicsItem const*, QWidget*)
{ ::drawFigure(this, painter); }

void Alg::drawFigure(QPainter *painter)
{
	auto figure = makeEllipsePattern(figureRect());
	painter->drawPath(figure);
}

void Alg::drawText(QPainter *painter)
{ ::drawText(this, painter, tryDrawText<Alg>); }


auto Process::isFitText(QFontMetrics const& metrics) const -> bool
{ return ::isFitText(text(), textBoundedRect(), metrics); }

auto Process::isFitTextRect(QFontMetrics const& metrics) const -> bool
{ return ::isFitTextRect(text(), defaultText(), textBoundedRect(), metrics); }

void Process::paint(QPainter* painter, QStyleOptionGraphicsItem const*, QWidget*)
{ ::drawFigure(this, painter); }

void Process::drawFigure(QPainter *painter)
{
	auto figure = makeRectanglePattern(figureRect());
	painter->drawPath(figure);
}

void Process::drawText(QPainter *painter)
{ ::drawText(this, painter, tryDrawText<Process>); }


auto IO::isFitText(QFontMetrics const& metrics) const -> bool
{ return ::isFitText(text(), textBoundedRect(), metrics); }

auto IO::isFitTextRect(QFontMetrics const& metrics) const -> bool
{ return ::isFitTextRect(text(), defaultText(), textBoundedRect(), metrics); }

void IO::paint(QPainter* painter, QStyleOptionGraphicsItem const*, QWidget*)
{ ::drawFigure(this, painter); }

void IO::drawFigure(QPainter *painter)
{
	auto figure = makeParallelogramPattern(figureRect(), slope());
	painter->drawPath(figure);
}

void IO::drawText(QPainter *painter)
{ ::drawText(this, painter, tryDrawText<IO>); }


auto Decision::isFitText(QFontMetrics const& metrics) const -> bool
{ return ::isFitText(text(), textBoundedRect(), metrics); }

auto Decision::isFitTextRect(QFontMetrics const& metrics) const -> bool
{ return ::isFitTextRect(text(), defaultText(), textBoundedRect(), metrics); }

void Decision::paint(QPainter* painter, QStyleOptionGraphicsItem const*, QWidget*)
{ ::drawFigure(this, painter); }

void Decision::drawFigure(QPainter *painter)
{
	auto figure = makeRhombusPattern(figureRect());
	painter->drawPath(figure);
}

void Decision::drawText(QPainter *painter)
{ ::drawText(this, painter, tryDrawText<Decision>); }
