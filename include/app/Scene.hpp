#pragma once
#include <app/common.hpp>
#include <widget/OpaqueWidget.hpp>
#include <app/RackScrollWidget.hpp>
#include <app/RackWidget.hpp>


namespace rack {
namespace app {


struct Scene : widget::OpaqueWidget {
	struct Internal;
	Internal* internal;

	// Convenience variables for accessing important widgets
	RackScrollWidget* rackScroll;
	RackWidget* rack;
	widget::Widget* menuBar;
	widget::Widget* moduleBrowser;
	widget::Widget* tipWindow;
	widget::Widget* frameRateWidget;

	double lastAutosaveTime = 0.0;
	/** The last mouse position in the Scene */
	math::Vec mousePos;

	Scene();
	~Scene();
	void step() override;
	void draw(const DrawArgs& args) override;
	void onHover(const event::Hover& e) override;
	void onDragHover(const event::DragHover& e) override;
	void onHoverKey(const event::HoverKey& e) override;
	void onPathDrop(const event::PathDrop& e) override;
};


} // namespace app
} // namespace rack
