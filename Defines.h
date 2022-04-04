#pragma once

#include <QColor>
#include <QFont>

namespace GuiMetrics {
	constexpr float ItemHeight = 40.0f;
	constexpr float ItemHalfHeight = ItemHeight / 2.0;

	constexpr float TextHorMargin = 20.0f;
	constexpr float NonTerminalRoundRad = 15.0f;
	constexpr float SpacerWidth = 50.0f;
	constexpr float VerticalItemSpacing = 25.0f;

	namespace EndPointMetrics {
		constexpr float InnerRadius = 5.0f;
		constexpr float OuterRadius = 8.0f;
		constexpr float WidthFraction = 0.8;
	}

	namespace LoggerButton {
		constexpr QColor BackroundColor = QColor(211, 211, 211);
		const QFont TextFont = QFont("Seqoe UI", 12);
		constexpr QColor HighlightColor = QColor(255, 0, 0, 125);
		constexpr int HighlightDuration = 1000;
	}
}
