// related header
#include "GraphicPrimitive.hpp"

// qt
#include <QGraphicsSceneHoverEvent>


// GraphicPrimitive
using pseorend::graphic_primitives::GraphicPrimitive;

// qt class enum
using Qt::Modifier::ALT;
using Qt::Modifier::CTRL;
using Qt::Modifier::SHIFT;

using Qt::KeyboardModifier::AltModifier;
using Qt::KeyboardModifier::ControlModifier;
using Qt::KeyboardModifier::ShiftModifier;


#if defined(PSEOREND_HOVER_MODE_ENABLED) && PSEOREND_HOVER_MODE_ENABLED

GraphicPrimitive::GraphicPrimitive(QObject* parent)
	: QObject(parent), QGraphicsItem()
	, m_text(), m_pen(), m_brush()
{ QGraphicsItem::setAcceptHoverEvents(true); }

void GraphicPrimitive::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
	auto constexpr alt_ok = (static_cast<int>(ALT) == static_cast<int>(AltModifier));
	auto constexpr ctrl_ok = (static_cast<int>(CTRL) == static_cast<int>(ControlModifier));
	auto constexpr shift_ok = (static_cast<int>(CTRL) == static_cast<int>(ControlModifier));

	static_assert(alt_ok && ctrl_ok && shift_ok,
	              "The used elements of enum Qt::Modifier and "
	              "enum Qt::KeyboardModifier must match!");

#ifdef    PSEOREND_HOWER_MODE_MODKEY

	auto fl = static_cast<Qt::KeyboardModifier>(
		PSEOREND_HOWER_MODE_MODKEY
	);

	if (!event->modifiers().testFlag(fl))
	{ return; }

#endif // PSEOREND_HOWER_MODE_MODKEY

	QGraphicsItem::setToolTip(m_text);
}

#else  // PSEOREND_HOVER_MODE_ENABLED

GraphicPrimitive::GraphicPrimitive(QObject* parent)
	: QObject(parent), QGraphicsItem()
	, m_text(), m_pen(), m_brush() {}

void GraphicPrimitive::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{ (void)event; }

#endif // PSEOREND_HOVER_MODE_ENABLED
