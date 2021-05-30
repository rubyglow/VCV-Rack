#include <app/LightWidget.hpp>
#include <color.hpp>
#include <settings.hpp>


namespace rack {
namespace app {


void LightWidget::draw(const DrawArgs& args) {
	float radius = std::min(box.size.x, box.size.y) / 2.0;
	nvgBeginPath(args.vg);
	nvgCircle(args.vg, radius, radius, radius);

	// Background
	if (bgColor.a > 0.0) {
		// TODO Set color in TGrayModuleLightWidget instead.
		nvgFillColor(args.vg, color::mult(bgColor, 0.5));
		// nvgFillColor(args.vg, bgColor);
		nvgFill(args.vg);
	}

	// Border
	if (borderColor.a > 0.0) {
		nvgStrokeWidth(args.vg, 0.5);
		nvgStrokeColor(args.vg, borderColor);
		nvgStroke(args.vg);
	}

	// Child widgets
	// TODO Upload new graphics instead of use this hack.
	// nvgGlobalAlpha(args.vg, 0.5);
	TransparentWidget::draw(args);

	// Dynamic light and halo
	nvgGlobalAlpha(args.vg, 1.0);
	// Use the formula `lightColor * (1 - dest) + dest` for blending
	nvgGlobalCompositeBlendFunc(args.vg, NVG_ONE_MINUS_DST_COLOR, NVG_ONE);
	drawLight(args);
	drawHalo(args);
}

void LightWidget::drawLight(const DrawArgs& args) {
	// Foreground
	if (color.a > 0.0) {
		float radius = std::min(box.size.x, box.size.y) / 2.0;
		nvgBeginPath(args.vg);
		nvgCircle(args.vg, radius, radius, radius);

		nvgFillColor(args.vg, color);
		nvgFill(args.vg);
	}
}

void LightWidget::drawHalo(const DrawArgs& args) {
	const float halo = settings::haloBrightness;
	if (halo == 0.f)
		return;

	float radius = std::min(box.size.x, box.size.y) / 2.0;
	float oradius = std::min(radius * 5.f, 30.f);

	nvgBeginPath(args.vg);
	nvgRect(args.vg, radius - oradius, radius - oradius, 2 * oradius, 2 * oradius);

	NVGcolor icol = color::mult(color, halo);
	NVGcolor ocol = nvgRGBA(0, 0, 0, 0);
	NVGpaint paint = nvgRadialGradient(args.vg, radius, radius, radius, oradius, icol, ocol);
	nvgFillPaint(args.vg, paint);
	nvgFill(args.vg);
}


} // namespace app
} // namespace rack
