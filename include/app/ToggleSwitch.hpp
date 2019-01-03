#pragma once
#include "app/common.hpp"
#include "app/ParamWidget.hpp"


namespace rack {


/** A switch that cycles through each mechanical position */
struct ToggleSwitch : virtual ParamWidget {
	void onDragStart(const event::DragStart &e) override;
};


} // namespace rack
