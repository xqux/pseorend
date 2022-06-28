#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_TEXTLIMITER_HPP
#define   PSEOREND_GRAPHIC_PRIMITIVES_TEXTLIMITER_HPP


// qt
#include <QRectF>
#include <QString>


// reserve qt types
class QFontMetrics;


namespace pseorend::graphic_primitives
{
	// this class is the convention of restricting
	// geometric primitives to some rectangle
	class TextLimiter
	{
	protected: // creation and destruction of objects
		~TextLimiter() = default;

	public: // text to be displayed if the set text could not be displayed
		static auto defaultText() -> QString
		{ return QString("\u00B7\u00B7\u00B7"); }

	public: // text limit rectangle
		virtual auto textBoundedRect() const -> QRectF = 0;

	public: // checking text to display
		virtual auto isFitText(QFontMetrics const& metrics) const -> bool = 0;
		virtual auto isFitTextRect(QFontMetrics const& metrics) const -> bool = 0;
	};
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_TEXTLIMITER_HPP
