#pragma once
#include "Create1.h"
#include "Windows.h"
#include <map>
#include <GLFW/glfw3.h>
#include <time.h>
using namespace std;
namespace Create1 {
    struct Vector3 {
    public:
        float x, y, z;
        Vector3() {
            x = 0;
            y = 0;
            z = 0;
        }
        Vector3(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        Vector3 Clamp(Vector3 coord, float min, float max) {

            coord.x = coord.x > max ? max : coord.x < min ? min : coord.x;
            coord.y = coord.y > max ? max : coord.y < min ? min : coord.y;
            coord.z = coord.z > max ? max : coord.z < min ? min : coord.z;
            return coord;
        }
        Vector3 operator+=(Vector3 other) {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        Vector3 operator-=(Vector3 other) {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        Vector3 operator+(Vector3 other) {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        Vector3 operator-(Vector3 other) {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        
        Vector3 operator+=(float other) {
            return Vector3(x + other, y + other, z + other);
        }
        Vector3 operator-=(float other) {
            return Vector3(x - other, y - other, z - other);
        }
        Vector3 operator+(float other) {
            return Vector3(x + other, y + other, z + other);
        }
        Vector3 operator-(float other) {
            return Vector3(x - other, y - other, z - other);
        }
        Vector3 operator*=(float other) {
            return Vector3(x * other, y * other, z * other);
        }
        Vector3 operator*(float other) {
            return Vector3(x * other, y * other, z * other);
        }
        Vector3 operator/=(float other) {
            return Vector3(x / other, y / other, z / other);
        }
        Vector3 operator/(float other) {
            return Vector3(x / other, y / other, z / other);
        }
    };
    struct Line {
    public:
        Vector3 start, end;
        Line() {
            start = Vector3();
            end = Vector3();
        }
        Line(Vector3 start, Vector3 end) {
            this->start = start;
            this->end = end;
        }
    }; 
    class Transform
    {
    public:
        Vector3 position, eulerAngles, scale;
        Transform()
        {
            position = Vector3();
            eulerAngles = Vector3();
            scale = Vector3();
        }

    };
    class GameObject
    {
    public:
        Transform transform;
        void* attachments[];
        GameObject(void(*Start)(), void* attachments[]) {
            Start();
            *(this->attachments) = attachments;
        }
    };
    static Transform camera;
    static class Renderer {
    public:
        
        static void MakeLines(Line lines[]) {

            glColor3f(1.0, 0.0, 1.0);
            glLineWidth(2.5);
            glBegin(GL_LINES);
            for (int i = 0; i < sizeof(lines); i++) {
                Vector3 start = lines[i].start - camera.position;
                Vector3 end = lines[i].end - camera.position;
                
                glVertex3d(start.x, start.y, start.z);
                glVertex3d(end.x, end.y, end.z);
            }

            glEnd();

        }

        static void Render() {
            MakeLines(new Line[4]{  Line(Vector3(0,0, 0),Vector3(0,1,0)),
                                    Line(Vector3(0,1,0),Vector3(1,1,0)),
                                    Line(Vector3(1,1,0),Vector3(1,0,0)), 
                                    Line(Vector3(1,0,0),Vector3(0,0,0)) });
        }
    };
    float deltaTime;
    float oldTime;
    static class GL
	{
        public:
            static int init(void(*update)(), const char* title)
            {
                GLFWwindow* window;

                /* Initialize the library */
                if (!glfwInit())
                    return -1;

                /* Create a windowed mode window and its OpenGL context */
                window = glfwCreateWindow(640, 480, title, NULL, NULL);
                if (!window)
                {
                    glfwTerminate();
                    return -1;
                }

                /* Make the window's context current */
                glfwMakeContextCurrent(window);
                /* Loop until the user closes the window */
                while (!glfwWindowShouldClose(window))
                {

                    glClear(GL_COLOR_BUFFER_BIT);
                    Renderer::Render();
                    /* Swap front and back buffers */
                    glfwSwapBuffers(window);
                    update();
                    /* Poll for and process events */
                    glfwPollEvents();
                    deltaTime = clock() * .01 - oldTime;
                    oldTime = clock() * .01;
                }

                glfwTerminate();
                return 0;
            }
    };
    
}

