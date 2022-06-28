// related header
#include "figure-making.hpp"


// qt enums
using Qt::ArrowType::UpArrow;
using Qt::ArrowType::DownArrow;
using Qt::ArrowType::LeftArrow;
using Qt::ArrowType::RightArrow;


namespace pseorend::graphic_primitives::figure_making::details
{
	auto makeEllipsePattern(QRectF const& rect) -> QPainterPath
	{
		auto path = QPainterPath();
		path.addEllipse(rect);

		return path;
	}

	auto makeRectanglePattern(QRectF const& rect) -> QPainterPath
	{
		auto path = QPainterPath();
		path.addRect(rect);

		return path;
	}

	auto makeParallelogramPattern(QRectF const& rect, qreal slope) -> QPainterPath
	{
		auto path = QPainterPath();

		path.moveTo(rect.left(), rect.bottom());
		path.lineTo(rect.left() + slope, rect.top());
		path.lineTo(rect.right(), rect.top());
		path.lineTo(rect.right() - slope, rect.bottom());
		path.lineTo(rect.left(), rect.bottom());

		return path;
	}

	auto makeRhombusPattern(QRectF const& rect) -> QPainterPath
	{
		auto path = QPainterPath();

		path.moveTo(rect.center().x(), rect.top());
		path.lineTo(rect.right(), rect.center().y());
		path.lineTo(rect.center().x(), rect.bottom());
		path.lineTo(rect.left(), rect.center().y());
		path.lineTo(rect.center().x(), rect.top());

		return path;
	}

	auto makeTringlePattern(QRectF const& rect, ArrowType direction) -> QPainterPath
	{
		auto path = QPainterPath();

		switch (direction)
		{
		case UpArrow:
			path.moveTo(rect.left(), rect.bottom());
			path.lineTo(rect.right(), rect.bottom());
			path.lineTo(rect.center().x(), rect.top());
			path.lineTo(rect.left(), rect.bottom());
			break;

		case DownArrow:
			path.moveTo(rect.left(), rect.top());
			path.lineTo(rect.right(), rect.top());
			path.lineTo(rect.center().x(), rect.bottom());
			path.lineTo(rect.left(), rect.top());
			break;

		case LeftArrow:
			path.moveTo(rect.right(), rect.bottom());
			path.lineTo(rect.right(), rect.top());
			path.lineTo(rect.left(), rect.center().y());
			path.lineTo(rect.right(), rect.bottom());
			break;

		case RightArrow:
			path.moveTo(rect.left(), rect.bottom());
			path.lineTo(rect.left(), rect.top());
			path.lineTo(rect.right(), rect.center().y());
			path.lineTo(rect.left(), rect.bottom());
			break;

		default:
			assert(false && "tringle type isn't a valid value.");
		}

		return path;
	}
}
