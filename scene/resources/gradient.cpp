/*************************************************************************/
/*  gradient.cpp                                                         */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "gradient.h"

#include "core/core_string_names.h"

//setter and getter names for property serialization
#define COLOR_RAMP_GET_OFFSETS "get_offsets"
#define COLOR_RAMP_GET_COLORS "get_colors"
#define COLOR_RAMP_SET_OFFSETS "set_offsets"
#define COLOR_RAMP_SET_COLORS "set_colors"

Gradient::Gradient() {
	//Set initial color ramp transition from black to white
	points.resize(2);
	points[0].color = Color(0, 0, 0, 1);
	points[0].offset = 0;
	points[1].color = Color(1, 1, 1, 1);
	points[1].offset = 1;
	is_sorted = true;
}

Gradient::~Gradient() {
}

void Gradient::_bind_methods() {

	ClassDB::bind_method(D_METHOD("add_point", "offset", "color"), &Gradient::add_point);
	ClassDB::bind_method(D_METHOD("remove_point", "offset"), &Gradient::remove_point);

	ClassDB::bind_method(D_METHOD("set_offset", "point", "offset"), &Gradient::set_offset);
	ClassDB::bind_method(D_METHOD("get_offset", "point"), &Gradient::get_offset);

	ClassDB::bind_method(D_METHOD("set_color", "point", "color"), &Gradient::set_color);
	ClassDB::bind_method(D_METHOD("get_color", "point"), &Gradient::get_color);

	ClassDB::bind_method(D_METHOD("interpolate", "offset"), &Gradient::get_color_at_offset);

	ClassDB::bind_method(D_METHOD("get_point_count"), &Gradient::get_points_count);

	ClassDB::bind_method(D_METHOD(COLOR_RAMP_SET_OFFSETS, "offsets"), &Gradient::set_offsets);
	ClassDB::bind_method(D_METHOD(COLOR_RAMP_GET_OFFSETS), &Gradient::get_offsets);

	ClassDB::bind_method(D_METHOD(COLOR_RAMP_SET_COLORS, "colors"), &Gradient::set_colors);
	ClassDB::bind_method(D_METHOD(COLOR_RAMP_GET_COLORS), &Gradient::get_colors);

	ADD_PROPERTY(PropertyInfo(Variant::POOL_REAL_ARRAY, "offsets"), COLOR_RAMP_SET_OFFSETS, COLOR_RAMP_GET_OFFSETS);
	ADD_PROPERTY(PropertyInfo(Variant::POOL_COLOR_ARRAY, "colors"), COLOR_RAMP_SET_COLORS, COLOR_RAMP_GET_COLORS);
}

std::vector<float> Gradient::get_offsets() const {
	std::vector<float> offsets;
	offsets.resize(points.size());
	for (int i = 0; i < points.size(); i++) {
		offsets[i] = points[i].offset;
	}
	return offsets;
}

std::vector<Color> Gradient::get_colors() const {
	std::vector<Color> colors;
	colors.resize(points.size());
	for (int i = 0; i < points.size(); i++) {
		colors[i] = points[i].color;
	}
	return colors;
}

void Gradient::set_offsets(const std::vector<float> &p_offsets) {
	points.resize(p_offsets.size());
	for (int i = 0; i < points.size(); i++) {
		points[i].offset = p_offsets[i];
	}
	is_sorted = false;
	emit_signal(CoreStringNames::get_singleton()->changed);
}

void Gradient::set_colors(const std::vector<Color> &p_colors) {
	if (points.size() < p_colors.size())
		is_sorted = false;
	points.resize(p_colors.size());
	for (int i = 0; i < points.size(); i++) {
		points[i].color = p_colors[i];
	}
	emit_signal(CoreStringNames::get_singleton()->changed);
}

std::vector<Gradient::Point> &Gradient::get_points() {
	return points;
}

void Gradient::add_point(float p_offset, const Color &p_color) {

	Point p;
	p.offset = p_offset;
	p.color = p_color;
	is_sorted = false;
	points.push_back(p);

	emit_signal(CoreStringNames::get_singleton()->changed);
}

void Gradient::remove_point(int p_index) {

	ERR_FAIL_INDEX(p_index, points.size());
	ERR_FAIL_COND(points.size() <= 2);
	points.erase(points.begin() + p_index);
	emit_signal(CoreStringNames::get_singleton()->changed);
}

void Gradient::set_points(std::vector<Gradient::Point> &p_points) {
	points = p_points;
	is_sorted = false;
	emit_signal(CoreStringNames::get_singleton()->changed);
}

void Gradient::set_offset(int pos, const float offset) {

	ERR_FAIL_COND(pos < 0);
	if (points.size() <= pos)
		points.resize(pos + 1);
	points[pos].offset = offset;
	is_sorted = false;
	emit_signal(CoreStringNames::get_singleton()->changed);
}

float Gradient::get_offset(int pos) const {
	ERR_FAIL_INDEX_V(pos, points.size(), 0.0);
	return points[pos].offset;
}

void Gradient::set_color(int pos, const Color &color) {
	ERR_FAIL_COND(pos < 0);
	if (points.size() <= pos) {
		points.resize(pos + 1);
		is_sorted = false;
	}
	points[pos].color = color;
	emit_signal(CoreStringNames::get_singleton()->changed);
}

Color Gradient::get_color(int pos) const {
	ERR_FAIL_INDEX_V(pos, points.size(), Color());
	return points[pos].color;
}

int Gradient::get_points_count() const {
	return points.size();
}
