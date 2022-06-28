#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_FIGURE_MAKING_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_FIGURE_MAKING_HPP


// qt
#include <QPainterPath>


namespace pseorend::graphic_primitives::figure_making::details
{
	// qt enums
	using Qt::ArrowType;
}

// these functions build figures based on a given rectangle
namespace pseorend::graphic_primitives::figure_making::details
{
	auto makeEllipsePattern(QRectF const& rect) -> QPainterPath;
	auto makeRectanglePattern(QRectF const& rect) -> QPainterPath;
	auto makeParallelogramPattern(QRectF const& rect, qreal slope) -> QPainterPath;
	auto makeRhombusPattern(QRectF const& rect) -> QPainterPath;
	auto makeTringlePattern(QRectF const& rect, ArrowType direction) -> QPainterPath;
}

namespace pseorend::graphic_primitives::figure_making
{
	using details::makeEllipsePattern;
	using details::makeRectanglePattern;
	using details::makeParallelogramPattern;
	using details::makeRhombusPattern;
	using details::makeTringlePattern;
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_FIGURE_MAKING_HPP
