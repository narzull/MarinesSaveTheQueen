#ifndef _COLOR_HPP_
#define _COLOR_HPP_

//Main Color struct
namespace renderer{
struct Color{
	static Color Red(){return Color(255,0,0);};
	static Color Green(){return Color(0,255,0);};
	static Color Blue(){return Color(0,0,255);};
	static Color Black(){return Color(0,0,0);};
	static Color White(){return Color(255,255,255);};
	static Color Yellow(){return Color(255,255,0);};
	static Color Pink(){return Color(255,0,255);};
	static Color Cyan(){return Color(0,255,255);};
	static Color Gray(){return Color(75,75,75);};
	//Constructor
	Color(float r, float g, float b):m_R(r), m_G(g), m_B(b){};
	Color():m_R(255), m_G(255), m_B(255){};
	//Attribute
	float m_R;
	float m_G;
	float m_B;
};
}//namespace api

#endif
