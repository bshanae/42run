#include "symbol.h"

#include "UI/rectangle/rectangle.h"
#include "UI/font/renderer.h"

using namespace		UI;

					font::symbol::symbol(FT_Face &face)
{
	size = ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
	bearing = ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
	advance = (int)((unsigned int)face->glyph->advance.x >> 6u);

	auto			texture = make_unique<model::texture>();

	texture->use(true);

	glTexImage2D
	(
		GL_TEXTURE_2D, 0, GL_RED,
		face->glyph->bitmap.width, face->glyph->bitmap.rows,
		0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture->use(false);

	rectangle = make_shared<UI::rectangle>(tag<UI::font::renderer>(), texture);
	rectangle->instance->scale(vec3(size.x * 0.5, size.y * 0.5, 1.f));
	rectangle->start();
}