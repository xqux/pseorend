#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_DRAWING_VISUALIZATION_INL
#define   PSEOREND_GRAPHIC_PRIMITIVES_DRAWING_VISUALIZATION_INL


// qt
#include <QPainter>


namespace pseorend::graphic_primitives::drawing_visualization::details
{
	// qt enums
	using Qt::BrushStyle::BDiagPattern;
	using Qt::PenStyle::DashLine;

	// default drawing set
	inline auto const DEFAULT_PEN = QPen(
		QBrush(QColor(128, 128, 128)),
		qreal(1.0),
		DashLine
	);

	inline auto const DEFAULT_BRUSH = QBrush(
		QColor(128, 128, 128, 64),
		BDiagPattern
	);
}

// these debug functions are for rendering
// additional details when drawing figures
// they only make sense in the context of
// defined PSEOREND_DRAWING_VISUALIZATION_ENABLED as true
namespace pseorend::graphic_primitives::drawing_visualization::details
{
#if defined(PSEOREND_DRAWING_VISUALIZATION_ENABLED) && PSEOREND_DRAWING_VISUALIZATION_ENABLED

	inline void highlightArea(QPainter *painter, QRectF const& rect,
	                          QPen const& pen = DEFAULT_PEN,
	                          QBrush const& brush = DEFAULT_BRUSH)
	{
		painter->save();

		// this rectangle is displayed only during debugging (when set flag)
		painter->setPen(pen);
		painter->setBrush(brush);
		painter->drawRect(rect);

		painter->restore();
	}

#else  // PSEOREND_DRAWING_VISUALIZATION_ENABLED

	template <typename... Args>
	inline void highlightArea(Args&&...) {}

#endif // PSEOREND_DRAWING_VISUALIZATION_ENABLED
}

namespace pseorend::graphic_primitives::drawing_visualization
{
	using details::highlightArea;
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_DRAWING_VISUALIZATION_INL
