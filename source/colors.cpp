#include "../../include/colors"

namespace sdl
{
    bool color_t::operator==(const color_t& other) const
	{
		return
		r == other.r &&
		g == other.g &&
		b == other.b;
	}

	namespace colors 
	{
		std::vector<color_t> get_primary()
		{
			std::vector<color_t> primary =
			{
				colors::RED,
				colors::YELLOW,
				colors::BLUE
			};
			return primary;
		}


		std::vector<color_t> get_secondary()
		{
			std::vector<color_t> secondary =
			{
				colors::ORANGE,
				colors::GREEN,
				colors::PURPLE,
			};
			return secondary;
		}

		std::vector<color_t> get_foundational()
		{
			std::vector<color_t> foundational =
			{
				colors::ORANGE,
				colors::RED,
				colors::GREEN,
				colors::YELLOW,
				colors::PURPLE,
				colors::BLUE
			};
			return foundational;
		}

		std::vector<color_t> get_all()
		{
			std::vector<color_t> all =
			{
				colors::BLACK,
				colors::WHITE,
				colors::RED,
				colors::GREEN,
				colors::BLUE,
				colors::YELLOW,
				colors::CYAN,
				colors::MAGENTA,
				colors::GRAY,
				colors::ORANGE,
				colors::BROWN,
				colors::PINK,
				colors::PURPLE,
				colors::VIOLET,
				colors::INDIGO,
				colors::GOLD,
				colors::SILVER,
				colors::MAROON,
				colors::OLIVE,
				colors::TEAL,
				colors::NAVY,
				colors::LAVENDER,
				colors::BEIGE,
				colors::TURQUOISE,
				colors::SALMON,
				colors::CRIMSON,
				colors::CORAL,
				colors::MINT,
				colors::PEACH,
				colors::CHARTREUSE,
				colors::AQUAMARINE,
				colors::LIME,
				colors::TOMATO,
				colors::WHEAT
			};
			return all;
		}
	}
}