// related header
#include "drawing-toolkit.hpp"

// project's headers
#include "graphic-primitives/syntactic-blocks.hpp"
#include "graphic-primitives/syntactic-relations.hpp"


// drawing-toolkit
using namespace pseo::rend;

using std::size_t;

using Qt::BrushStyle;
using Qt::GlobalColor;
using Qt::PenCapStyle;
using Qt::PenJoinStyle;
using Qt::PenStyle;


PseoFigureFeatures::PseoFigureFeatures() noexcept
	: size(qreal(250.0), qreal(100.0))
	, indent(qreal(50.0))
	, ioSlope(qreal(50.0))
	, colors()
{
	try
	{
		// https://www.schemecolor.com/right-path.php
		colors[0] = QColor(251, 241, 182);
		colors[1] = QColor(199, 229, 198);
		colors[2] = QColor(200, 207, 231);
		colors[3] = QColor(229, 218, 242);
	}
	catch (...)
	{}
}


PseoArrowFeatures::PseoArrowFeatures() noexcept
	: textIndent(qreal(10.0))
	, spanRelativelyFigure(qreal(0.9))
	, headSpan(qreal(6.0)) {}


PseoToolkit::PseoToolkit() noexcept
	: figure(), arrow() {}

PseoToolkit::PseoToolkit(PseoFigureFeatures const& figure,
                         PseoArrowFeatures const& arrow) noexcept
	: figure(figure), arrow(arrow) {}

auto PseoToolkit::brush(PseoBlock::Style style) const -> QBrush
{
	auto index = static_cast<size_t>(style);
	assert(index < 5 && "impossible branch of program execution.");

	return QBrush(figure.colors[index]);
}

auto PseoToolkit::pen() const -> QPen
{
	auto pen = QPen(QBrush(QColor(GlobalColor::black)),
	                qreal(3),
	                PenStyle::SolidLine,
	                PenCapStyle::RoundCap,
	                PenJoinStyle::RoundJoin);

	return pen;
}
