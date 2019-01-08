#pragma once
#include "Texture.h"
class ModelTexture :
	public Texture
{
private:
	float m_ShineDamper = 1;
	float m_Reflectivity = 0;

	bool m_Transparancy = false;
	bool m_FakeLighting = false;

	int m_NrOfRows = 1;

public:
	ModelTexture(const std::string& path);
	~ModelTexture();

	inline float GetShineDamper() const { return m_ShineDamper; }
	inline float GetReflectivity() const { return m_Reflectivity; }
	inline bool IsTransparant() const { return m_Transparancy; }
	inline bool UsingFakeLighting() const { return m_FakeLighting; }
	inline int GetNrOfRows()const { return m_NrOfRows; }


	inline void SetShineDamper(const float value) { m_ShineDamper = value; }
	inline void SetReflectivity(const float value) { m_Reflectivity = value; }
	inline void SetTransparancy(const bool value) { m_Transparancy = value; }
	inline void SetFakeLighting(const bool value) { m_FakeLighting = value; }
	inline void SetNrOFRows(const int value) { m_NrOfRows = value; }
};

