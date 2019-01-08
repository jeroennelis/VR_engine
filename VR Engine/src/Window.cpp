#include "Window.h"

int Window::Height = 0;
int Window::Width = 0;
bool Window::m_Keys[MAX_KEYS];
bool Window::m_MouseButtons[Max_BUTTONS];
double Window::m_MouseX;
double Window::m_MouseY;
float Window::m_Delta;
double Window::m_ScrollX;
double Window::m_ScrollY;
double Window::m_MouseDX;
double Window::m_MouseDY;

const float Window::FOV = 70;
const float Window::NEAR_PLANE = 0.1f;
const float Window::FAR_PLANE = 1000.f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);

Window::Window(int width, int height, std::string & title)
	:m_Title(title)
{
	Width = width;
	Height = height;
	for (int i = 0; i < MAX_KEYS; i++)
		m_Keys[i] = false;
	for (int i = 0; i < Max_BUTTONS; i++)
		m_MouseButtons[i] = false;

	
}

Window::~Window()
{
	glfwTerminate();
}


bool Window::Init()
{
	/* Initialize the library */
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	m_Window = glfwCreateWindow(Width, Height, m_Title.c_str(), NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "glew error!" << std::endl;
	glfwSetTime(0);
	return true;
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	
}


