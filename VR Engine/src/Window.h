#pragma once
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include<GLM\glm.hpp>


#include <chrono>

#define MAX_KEYS	1024
#define Max_BUTTONS 32

class Window
{
public:
	static int Width, Height;

	const static float FOV;
	const static float NEAR_PLANE;
	const static float FAR_PLANE;

private:
	friend struct GLFWwindow;
	GLFWwindow * m_Window;
	
	std::string m_Title;

	static bool m_Keys[1024];
	static bool m_MouseButtons[Max_BUTTONS];
	static double m_MouseX, m_MouseY;
	static double m_MouseDX, m_MouseDY;
	static double m_ScrollX, m_ScrollY;

	static float m_Delta;

public:

	Window(int width, int height, std::string& title);
	~Window();

	bool Init();
	void Update();

	GLFWwindow* GetWindow()const { return m_Window; }

	static float GetDelta() { return m_Delta; }

	inline static double GetScrollX() { return m_ScrollX; }
	inline static double GetScrollY() { return m_ScrollY; }

	inline static double GetDX() { return m_MouseDX; }
	inline static double GetDY() { return m_MouseDY; }
};

