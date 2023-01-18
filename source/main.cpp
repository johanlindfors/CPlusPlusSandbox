/*
 * GL01Hello.cpp: Test OpenGL C/C++ Setup
 */
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <iostream>
#include <filesystem.h>
#include <shader.h>

glm::mat4 getProjectionMatrix()
{
    return glm::perspective(glm::radians(45.0f), (float)800.0f / (float)600.0f, 0.1f, 100.0f);
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 getViewMatrix()
{
    return glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

int main(int argc, char **argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    auto window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("model.vs", "model.fs"); 

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions            // normals          // texture coords
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,  0.5f, 0.75f,
        0.5f, -0.5f, -0.5f,     0.0f, 0.0f, -1.0f,  0.0f, 0.75f,
        0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f,  0.0f, 0.25f,
        0.5f, 0.5f, -0.5f,      0.0f, 0.0f, -1.0f,  0.0f, 0.25f,
        -0.5f, 0.5f, -0.5f,     0.0f, 0.0f, -1.0f,  0.5f, 0.25f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f, -1.0f,  0.5f, 0.75f,

        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 0.75f,
        0.5f, -0.5f, 0.5f,      0.0f, 0.0f, 1.0f,   1.0f, 0.25f,
        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 1.0f,   0.5f, 0.25f,
        0.5f, 0.5f, 0.5f,       0.0f, 0.0f, 1.0f,   0.5f, 0.25f,
        -0.5f, 0.5f, 0.5f,      0.0f, 0.0f, 1.0f,   0.5f, 0.75f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f,   1.0f, 0.75f,

        -0.5f, 0.5f, 0.5f,      -1.0f, 0.0f, 0.0f,  1.0f, 0.25f,
        -0.5f, 0.5f, -0.5f,     -1.0f, 0.0f, 0.0f,  0.5f, 0.25f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,  0.5f, 0.75f,
        -0.5f, -0.5f, -0.5f,    -1.0f, 0.0f, 0.0f,  0.5f, 0.75f,
        -0.5f, -0.5f, 0.5f,     -1.0f, 0.0f, 0.0f,  1.0f, 0.75f,
        -0.5f, 0.5f, 0.5f,      -1.0f, 0.0f, 0.0f,  1.0f, 0.25f,

        0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 0.0f,   1.0f, 0.25f,
        0.5f, 0.5f, -0.5f,      1.0f, 0.0f, 0.0f,   1.0f, 0.75f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,   0.5f, 0.75f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,   0.5f, 0.75f,
        0.5f, -0.5f, 0.5f,      1.0f, 0.0f, 0.0f,   0.5f, 0.25f,
        0.5f, 0.5f, 0.5f,       1.0f, 0.0f, 0.0f,   1.0f, 0.25f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 0.75f,
        0.5f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,  0.5f, 0.75f,
        0.5f, -0.5f, 0.5f,      0.0f, -1.0f, 0.0f,  0.5f, 0.25f,
        0.5f, -0.5f, 0.5f,      0.0f, -1.0f, 0.0f,  0.5f, 0.25f,
        -0.5f, -0.5f, 0.5f,     0.0f, -1.0f, 0.0f,  0.0f, 0.25f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f, 0.0f,  0.0f, 0.75f,

        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,   0.0f, 0.25f,
        0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,   0.0f, 0.75f,
        0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 0.0f,   0.5f, 0.75f,
        0.5f, 0.5f, 0.5f,       0.0f, 1.0f, 0.0f,   0.5f, 0.75f,
        -0.5f, 0.5f, 0.5f,      0.0f, 1.0f, 0.0f,   0.5f, 0.25f,
        -0.5f, 0.5f, -0.5f,     0.0f, 1.0f, 0.0f,   0.0f, 0.25f
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 36, static_cast<void*>(&vertices[0]), GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coordinate attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;

    unsigned char *data = stbi_load("coderox.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        ourShader.use();

        // lighting
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

        ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        ourShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        // view/projection transformations
        ourShader.setMat4("projection", getProjectionMatrix());
        ourShader.setMat4("view", getViewMatrix());

        // world transformation
        glm::mat4 world = glm::mat4(1.0f);
        auto angle = glm::radians(135.0f);
        world = glm::rotate(world, angle, glm::vec3( 1.1f, 1.1, 0.0f ));
        ourShader.setMat4("model", world);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
    }
    glfwTerminate();

    return 0;
}