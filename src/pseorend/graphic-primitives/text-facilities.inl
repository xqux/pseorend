#pragma once
#ifndef   PSEOREND_GRAPHIC_PRIMITIVES_TEXT_FACILITIES_INL
#define   PSEOREND_GRAPHIC_PRIMITIVES_TEXT_FACILITIES_INL


// qt
#include <QPainter>


// service functions,
// these functions compresses the code
namespace pseorend::graphic_primitives::text_facilities
{
	inline auto isFitTextSize(QSizeF const& boundedTextRect,
	                          QSizeF const& textRect) -> bool
	{
		return boundedTextRect.width() > textRect.width() &&
		       boundedTextRect.height() > textRect.height();
	}

	inline auto isFitText(QString const& text, QRectF const& textBoundedRect,
	                      QFontMetricsF const& metrics) -> bool
	{
		if (text.isEmpty())
		{ return false; }

		return isFitTextSize(textBoundedRect.size(),
		                     metrics.boundingRect(text).size());
	}

	inline auto isFitTextRect(QString const& text, QString const& defaultText,
	                          QRectF const& textBoundedRect,
	                          QFontMetricsF const& metrics) -> bool
	{
		if (text.isEmpty())
		{ return false; }

		return isFitTextSize(textBoundedRect.size(), metrics.boundingRect(text).size()) ||
		       isFitTextSize(textBoundedRect.size(), metrics.boundingRect(defaultText).size());
	}

	// try to draw at least something
	template <typename T, typename Fn>
	inline auto drawText(T* obj, QPainter* painter, Fn tryDrawText)
	{
		assert(obj != nullptr && painter != nullptr &&
		       "incorrectly passed values for drawing a primitive");

		// draw according to font size
		auto metrics = painter->fontMetrics();
		auto textBoundedRect = obj->textBoundedRect();

		if (!obj->text().isEmpty())
		{
			if (!tryDrawText(obj, painter, metrics, textBoundedRect, obj->text()))
			{ tryDrawText(obj, painter, metrics, textBoundedRect, obj->defaultText()); }
		}
	}
}


#endif // PSEOREND_GRAPHIC_PRIMITIVES_TEXT_FACILITIES_INL
