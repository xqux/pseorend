#pragma once
#ifndef   PSEOREND_DRAWING_TOOLKIT_HPP
#define   PSEOREND_DRAWING_TOOLKIT_HPP


// qt
#include <QBrush>
#include <QPen>

// pseolang
#include <pseolang/representation.hpp>


namespace pseorend::details
{
	using pseolang::PseoBlock;


	// all the fields that are needed to draw the figure
	class PseoFigureFeatures
	{
	public: // creation and destruction of objects
		explicit PseoFigureFeatures() noexcept;
		~PseoFigureFeatures() noexcept = default; // no virtual

	public: // members
		QSizeF size;
		qreal indent;
		qreal ioSlope;

		// ALG, PROCESS, IO, DECISION
		QColor colors[4];
	};

	// all the fields that are needed to draw the arrow
	class PseoArrowFeatures
	{
	public: // creation and destruction of objects
		explicit PseoArrowFeatures() noexcept;
		~PseoArrowFeatures() noexcept = default; // no virtual

	public: // members
		qreal textIndent;
		qreal spanRelativelyFigure;
		qreal headSpan;
	};

	// the class providing QPen and QBrush,
	// concatenates PseoFigureFeatures and PseoArrowFeatures
	class PseoToolkit
	{
	public: // creation and destruction of objects
		explicit PseoToolkit() noexcept;
		explicit PseoToolkit(PseoFigureFeatures const& figure,
		                     PseoArrowFeatures const& arrow) noexcept;

		~PseoToolkit() noexcept = default; // no virtual

	public: // get drawing tools
		auto brush(PseoBlock::Style style) const -> QBrush;
		auto pen() const -> QPen;

	public: // members
		PseoFigureFeatures figure;
		PseoArrowFeatures arrow;
	};
}

namespace pseo::rend
{
	using details::PseoFigureFeatures;
	using details::PseoArrowFeatures;
	using details::PseoToolkit;
}


#endif // PSEOREND_DRAWING_TOOLKIT_HPP
