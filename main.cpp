#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <sstream>
#include <type_traits>
/*
class MyClass {
public:
    // Basic data members
    float myFloat;
    int myInt;
    double myDouble;
    char myChar;
    std::string myString;

    // Vectors
    std::vector<float> myFloatVector;
    std::vector<std::string> myStringVector;

    // Method to serialize the class to a string
    std::string serialize() const {
        std::string result;
        result += CoreX::Serialize::Serialize_Text(myFloat) + char(2);
        result += CoreX::Serialize::Serialize_Text(myInt) + char(2);
        result += CoreX::Serialize::Serialize_Text(myDouble) + char(2);
        result += CoreX::Serialize::Serialize_Text(myChar) + char(2);
        result += CoreX::Serialize::Serialize_Text(myString) + char(2);
        result += CoreX::Serialize::Serialize_Text(myFloatVector) + char(2);

        result += CoreX::Serialize::Serialize_Text(myStringVector.size()) + char(2);
        //// Serialize each string in the string vector individually
        for (const auto& str : myStringVector) {
            result += CoreX::Serialize::Serialize_Text(str) + char(2);
        }

        return result;
    }

    // Static method to deserialize a string back into a MyClass object
    static MyClass deserialize(const std::string& data) {
        std::istringstream iss(data);
        MyClass obj;

        std::string temp;

        // Deserialize each field in the same order as serialization
        std::getline(iss, temp, char(2));
        obj.myFloat = CoreX::Serialize::Deserialize_Text<float>(temp);

        std::getline(iss, temp, char(2));
        obj.myInt = CoreX::Serialize::Deserialize_Text<int>(temp);

        std::getline(iss, temp, char(2));
        obj.myDouble = CoreX::Serialize::Deserialize_Text<double>(temp);

        std::getline(iss, temp, char(2));
        obj.myChar = CoreX::Serialize::Deserialize_Text<char>(temp);

        std::getline(iss, temp, char(2));
        obj.myString = CoreX::Serialize::Deserialize_Text<std::string>(temp);
        // Deserialize each float in the float vector
        std::getline(iss, temp, char(2));
        obj.myFloatVector = CoreX::Serialize::Deserialize_Text<std::vector<float>>(temp);

        std::getline(iss, temp, char(2));
        int size = CoreX::Serialize::Deserialize_Text<int>(temp);
        //// Deserialize each string in the string vector
        for (size_t i = 0; i < size; ++i) {
            std::getline(iss, temp, char(2));
            obj.myStringVector.push_back(CoreX::Serialize::Deserialize_Text<std::string>(temp));
        }

        return obj;
    }

    std::string BSerialize() const {
        std::string result;
        result += CoreX::Serialize::Serialize_Binary(myFloat);
        result += CoreX::Serialize::Serialize_Binary(myInt);
        result += CoreX::Serialize::Serialize_Binary(myDouble);
        result += CoreX::Serialize::Serialize_Binary(myChar);
        result += CoreX::Serialize::Serialize_Binary(myString);
        result += CoreX::Serialize::Serialize_Binary(myFloatVector);
       // result += CoreX::Serialize::Serialize_Binary(myStringVector);
        return result;
    }

    // Custom deserialize function for MyClass
    static MyClass BDeserialize(const std::string& data) {
        std::string remainingData = data;
        MyClass obj;
        // Deserialize each member one by one
        obj.myFloat = CoreX::Serialize::Deserialize_Binary<float>(remainingData);
        obj.myInt = CoreX::Serialize::Deserialize_Binary<int>(remainingData);
        obj.myDouble = CoreX::Serialize::Deserialize_Binary<double>(remainingData);
        obj.myChar = CoreX::Serialize::Deserialize_Binary<char>(remainingData);
        obj.myString = CoreX::Serialize::Deserialize_Binary<std::string>(remainingData);
        obj.myFloatVector = CoreX::Serialize::Deserialize_Binary<std::vector<float>>(remainingData);
        //remainingData = remainingData.substr(CoreX::Serialize::Serialize_Binary(obj.myFloatVector).size());

       // myStringVector = CoreX::Deserialize_Binary<std::vector<std::string>>(remainingData);
        // No need to update remainingData as we have reached the end
        return obj;
    }
};*/

/*
int main() 
{


    MyClass obj;
    obj.myFloat = 1.23f;
    obj.myInt = 42;
    obj.myDouble = 3.14159;
    obj.myChar = 'A';
    obj.myString = "Hello World\n and a happy new yar";
    obj.myFloatVector;
    for (int C1 = 0; C1 < 1000000; C1++)
        obj.myFloatVector.push_back(C1 * 0.99f);
    obj.myStringVector = { "one", "two", "three" };

    // Serialize the object
    std::string serializedData = obj.BSerialize();
    //std::cout << "Serialized Data: " << serializedData << std::endl;
    CoreX::FileIO::Save("Test.txt", serializedData);

    MyClass newObj = MyClass::BDeserialize(CoreX::FileIO::Load("test.txt"));

    //std::cout << "New Serialized Data: " << newObj.serialize() << std::endl;

    return 0;
}
*/

#include "corex/glew/glew.h"
#include "corex/glfw/glfw.h"
#include "corex/imgui/imgui.h"
#include "corex/glew/shader.h"
#include "corex/glew/framebuffer.h"
#include "corex/glew/texture.h"
#include "corex/simply3d/simply3d.h"

const char* vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 position;

out vec2 TexCoords;

void main()
{
    TexCoords = position.xy * 0.5 + 0.5; // Normalize to [0,1] range
    gl_Position = vec4(position, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

in vec2 TexCoords;
out vec4 color;

uniform float u_Time;
uniform float u_AspectRatio;
uniform vec2 u_Size;
uniform vec2 u_Mouse;

vec3 pallet(float t)
{
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263, 0.416, 0.557);

    return a + b*cos(6.28318 *(c*t+d));
}

void main()
{   
    vec2 uv = TexCoords;
    uv = uv - 0.5;
    uv = uv * 2;
    uv += TexCoords + 0.5 * cos( 0.1 * u_Time + fract(uv) * 0.21);
    uv -= TexCoords + 0.5 * sin( 0.4 * u_Time + fract(uv) * 0.0113);
    vec2 uv0 = uv;
    vec3 finalcolor = vec3(0.0);

    for (float i = 0.0; i < 4.0; i++)
    {

    uv = fract(uv * 1.46) - 0.5;
    
    float d = length(uv) - 0.5;
    vec3 mycolor = pallet(length(uv0) + u_Time * 0.4 + i * 0.4);

    
    d = sin(d * 8.0 + u_Time)/8.0;
    d = abs(d);
    //d = smoothstep(0.0, 0.1, d);
    d = 0.011/d;
    d = pow(d, 1.2);

    finalcolor += mycolor * d;
    }

    color = vec4(finalcolor, 3.0); // Color varies between blue and red
}
)";

const char* mandelbrotFragmentShaderSource = R"(
#version 430 core

in vec2 TexCoords;
out vec4 fragColor;

uniform float u_Time;
uniform vec2 u_Resolution;

float mandel(vec2 uv)
{
    float max = int(100.0 + log(u_Time) * 50.0);
    vec2 c = 4.0 * uv - vec2(0.7, 0.0);
    vec2 z = vec2(0.0);
   // c = c/pow(u_Time, 4.0) - vec2(0.65, 0.45);
    float iter = 0.0;
    for (float i; i < max; i++)
    {
        z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
        if (dot(z, z) > 4.0) return iter/max; 
        iter++;
    }
    return 0.0;
}

const int maxIterations = 100;

void main()
{
    vec2 uv  = (gl_FragCoord.xy - 0.5 * u_Resolution.xy) / u_Resolution.xy;
    uv = (uv / u_Time);
    vec3 col = vec3(0.0);

    float m = mandel(uv);
    
    col.xy += m;    
    col = pow(col, vec3(0.45));

    fragColor = vec4(col, 1.0);
}
)";

const char* mandelbrotFragmentShaderSource_Online = R"(
#version 430 core

in vec2 TexCoords;
out vec4 fragColor;

uniform float u_Time;
uniform vec2 u_Resolution;

// Define zoom locations
const vec2 MINIBROT_C = vec2(-1.98542425, 0.0);
const vec2 MINIBROT_SCALE = vec2(5.81884941e-5, 0.0);
const vec2 MINIBROT_A = vec2(-161.347726, 0.0);
const float MINIBROT_PERIOD = 5.0;

const float MINIBROT_R = 8.0;
const float MINIBROT_R2 = 32.0;
const int BASE_ITER = 100; // Base iterations, dynamically scaled
const float BAILOUT = 32.0;

// Helper functions for complex numbers
vec2 cmul(vec2 a, vec2 b) {
    return vec2(dot(a, vec2(1.0, -1.0) * b), dot(a, b.yx));
}

vec2 cdiv(vec2 a, vec2 b) {
    return vec2(dot(a, b), dot(a.yx, vec2(1.0, -1.0) * b)) / dot(b, b);
}

void main()
{
    vec2 fragCoord = gl_FragCoord.xy;
    float t = u_Time * u_Time / (u_Time + 1.0);
    float s = -log(length(MINIBROT_SCALE));
    int n = int(ceil(t / s));
    float zoom = exp(-(t - s * float(n)));
    float theta = float(n) * atan(MINIBROT_SCALE.y, MINIBROT_SCALE.x);
    vec2 C = cmul(MINIBROT_C, cdiv(vec2(1.0, 0.0), vec2(1.0, 0.0) - MINIBROT_SCALE));
    vec2 dc = vec2(cos(theta), -sin(theta)) * 10.0 * zoom / length(u_Resolution);
    vec2 c = C + cmul(dc, vec2(1.0, -1.0) * (fragCoord - u_Resolution * 0.5));

    // Calculate dynamic iteration limit based on zoom level
    int maxIterations = int(BASE_ITER * log2(zoom) * 2.0);
    maxIterations = clamp(maxIterations, BASE_ITER, 1000); // Clamp to a reasonable max

    while (n > 0 && dot(c - MINIBROT_C, c - MINIBROT_C) > MINIBROT_R2) {
        c = MINIBROT_C + cmul(c, MINIBROT_SCALE);
        dc = cmul(dc, MINIBROT_SCALE);
        n--;
    }

    vec2 z = vec2(0.0);
    vec2 dz = dc;
    int i = 0;
    float i2 = 0.0;
    float escapeRadius = n == 0 ? BAILOUT : MINIBROT_R;

    while (i < maxIterations) {
        if (dot(z, z) > escapeRadius) {
            if (n == 0) {
                break;
            } else {
                z = cdiv(z, MINIBROT_A);
                dz = cdiv(dz, MINIBROT_A);
                c = MINIBROT_C + cmul(c, MINIBROT_SCALE);
                dc = cmul(dc, MINIBROT_SCALE);
                n--;
                i2 *= MINIBROT_PERIOD;
                escapeRadius = n == 0 ? BAILOUT : MINIBROT_R;
            }
        }
        dz = 2.0 * cmul(dz, z) + dc;
        z = cmul(z, z) + c;
        i++;
        i2++;
    }

    // Coloring based on iterations and distance estimation
    float d = !(i < maxIterations) ? 0.0 : sqrt(dot(z, z) / dot(dz, dz)) * 0.5 * log(dot(z, z));
    vec3 color = vec3((1.0 - d) * (0.5 + 0.5 * cos(log(1.0 + i2 * 2.0e-5))));
    fragColor = vec4(color, 1.0);
}
)";



const char* fragmentShaderMesh = R"(
#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f);
}

)";


const char* vertexShaderMesh = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = vec3(1.0);
}

)";

#include <chrono>
#include "corex/core/serialize.hpp"
#include "corex/core/fileio.hpp"
#include "corex/core/console.hpp"

// Timer using chrono
auto start = std::chrono::high_resolution_clock::now();
CoreX::Simply3D::Shader shader;

CoreX::GLFW::Window* My_Window;

void Keys(const bool* keys, CoreX::Simply3D::Camera& Camera)
{

    static auto Time = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = now - start;
    float time = elapsed.count();

  //  std::string save = CoreX::Serialize::Serialize_Binary(vert) + CoreX::Serialize::Serialize_Binary(index);
  //  CoreX::FileIO::Save("Mesh.s3dm", save);

    if (time != 0)
    {
        Time = std::chrono::high_resolution_clock::now();
    }

    if (keys[KEY_S])
        Camera.Translate(-Camera.Forward() * time);
    if (keys[KEY_W])
        Camera.Translate(Camera.Forward() * time);
    if (keys[KEY_A])
        Camera.Translate(-Camera.Right() * time);
    if (keys[KEY_D])
        Camera.Translate(Camera.Right() * time);
    if (keys[KEY_F])
        My_Window->SetLockMouse(not My_Window->GetLockMouse());

}




int main()
{
    using namespace CoreX::GLFW;
    CoreX::Simply3D::Shader shader_sky;
 
    CoreX::Simply3D::Transform Demo_Transform;

    std::string Data = CoreX::FileIO::Load("Mesh.s3dm");
    std::vector<float >vert = CoreX::Serialize::Deserialize_Binary<std::vector<float>>(Data);
    std::vector<unsigned int>index = CoreX::Serialize::Deserialize_Binary<std::vector<unsigned int>>(Data);
    std::string save = CoreX::Serialize::Serialize_Binary(CoreX::Simply3D::Primitives::Cube.Vertices()) + CoreX::Serialize::Serialize_Binary(CoreX::Simply3D::Primitives::Cube.Indices());
    CoreX::FileIO::Save("cuve.bin", save);
    std::string Data2 = CoreX::FileIO::Load("Test.s3dm");
    vert = CoreX::Serialize::Deserialize_Text<std::vector<float>>(Data2);
    index = CoreX::Serialize::Deserialize_Text<std::vector<unsigned int>>(Data2);
    My_Window = new Window();
    My_Window->Initialize("Test");

    CoreX::GLEW::Initialize(My_Window->GetBufferWidth(), My_Window->GetBufferHeight());
    CoreX::ImGUI::Initilize(My_Window->GetWindow());
    CoreX::ImGUI::Modify_Config_Flags(ImGuiConfigFlags_DockingEnable);
    CoreX::ImGUI::Modify_Config_Flags(ImGuiConfigFlags_ViewportsEnable);


    CoreX::Simply3D::Camera Camera(45, 0.01f, 1000.0f, static_cast<int>(My_Window->GetBufferWidth() / My_Window->GetBufferHeight()));
    shader.Compile(CoreX::Simply3D::Basic_Vertex, CoreX::Simply3D::Basic_Fragment);
    shader_sky.Compile(CoreX::Simply3D::Basic_Skydome_Vertex, CoreX::Simply3D::Basic_Skydome_Fragment);
    //InitQuad();
    //initCube();
    CoreX::Simply3D::Mesh Cube;
    CoreX::Simply3D::Mesh Sky_Box;
    Sky_Box.Set_Data(CoreX::Simply3D::Primitives::Sphere.Vertices(), CoreX::Simply3D::Primitives::Sphere.Indices());
    Cube.Set_Data(CoreX::Simply3D::Primitives::Cube.Vertices(), CoreX::Simply3D::Primitives::Cube.Indices());

    
    CoreX::GLEW::Framebuffer Texture_Buffer;
    CoreX::GLEW::Texture Texture_Image(GL_TEXTURE_2D, My_Window->GetBufferWidth(), My_Window->GetBufferHeight());
    Texture_Image.Set_Parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    Texture_Image.Set_Parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Texture_Image.Set_Parameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    Texture_Image.Set_Parameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    Texture_Image.Bind_Framebuffer(GL_COLOR_ATTACHMENT0);

    GLuint depthStencilRenderbuffer;
    glGenRenderbuffers(1, &depthStencilRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, My_Window->GetBufferWidth(), My_Window->GetBufferHeight());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // Attach the renderbuffer as the depth and stencil attachment of the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRenderbuffer);
    Texture_Buffer.Unbind();

    
    while (not My_Window->ShouldClose())
    {
        glEnable(GL_DEPTH_TEST);
        glfwMakeContextCurrent(My_Window->GetWindow());
        My_Window->EventHandler();
        Camera.Set_Aspect_Ratio(static_cast<float>(My_Window->GetBufferWidth()) / static_cast<float>(My_Window->GetBufferHeight()));


        //Setup Mouse Pos
        static float lf_LastMouseX = -1;
        static float lf_LastMouseY = -1;
        if (lf_LastMouseX == -1 && lf_LastMouseY == -1)
        {
            My_Window->GetMousePos(lf_LastMouseX, lf_LastMouseY);
        }
        float lf_MouseX = 0;
        float lf_MouseY = 0;
        //
        My_Window->GetMousePos(lf_MouseX, lf_MouseY);//Get Current Mouse Pos
        //Calculate Delta Mouse
        float lf_DeltaMouseX = (lf_LastMouseX - lf_MouseX);
        float lf_DeltaMouseY = (lf_LastMouseY - lf_MouseY);
        //

        //Store Current Mouse Pos
        lf_LastMouseX = lf_MouseX;
        lf_LastMouseY = lf_MouseY;
        //

        Camera.Set_Rotation(Camera.Rotation().x + glm::radians(lf_DeltaMouseY * 0.1f), Camera.Rotation().y - glm::radians(lf_DeltaMouseX * 0.1f), 0.0f);
        if (Camera.Rotation().x > glm::radians(89.0f))
            Camera.Set_Rotation(glm::radians(89.0f), Camera.Rotation().y, Camera.Rotation().z);
        if (Camera.Rotation().x < glm::radians(-89.0f))
            Camera.Set_Rotation(glm::radians(-89.0f), Camera.Rotation().y, Camera.Rotation().z);


        Camera.Update();
        Keys(My_Window->GetKeys(), Camera);

        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = now - start;
        float time = elapsed.count();
        //Demo_Transform.Look_At(Camera.Position());
        Demo_Transform.Rotate(time * 100.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        CoreX::Console::Print_Line(time);
        start = std::chrono::high_resolution_clock::now();


        CoreX::ImGUI::Clear_Buffer();
      //  ImGui::Begin("OpenGL Render");
        //ImVec2 windowSize = ImGui::GetContentRegionAvail();

        //Texture_Buffer.Bind();
        CoreX::GLEW::Clear_Buffer(My_Window->GetBufferWidth(), My_Window->GetBufferHeight());
        

        glDepthMask(GL_FALSE);

        // Render the quad
        // Camera.Set_Aspect_Ratio(windowSize.x / windowSize.y);
        CoreX::Simply3D::Transform sky;
        sky.Set_Position(glm::vec3(0, -0.02, 0));
        shader_sky.Start();
        shader_sky.Set("projection", Camera.Projection());
        shader_sky.Set("view", glm::mat4(glm::mat3(Camera.View())));
        Sky_Box.Render();
        shader_sky.Stop();

        glDepthMask(GL_TRUE);

        shader.Start();
        shader.Set("projection", Camera.Projection());
        shader.Set("model", Demo_Transform.Matrix());
        shader.Set("view", Camera.View());
        Cube.Render();
        shader.Stop();
        //Texture_Buffer.Unbind();

       // CoreX::GLEW::Clear_Buffer(My_Window->GetBufferWidth(), My_Window->GetBufferHeight());
        


       // ImGui::Image((ImTextureID)(intptr_t)Texture_Image.ID(), windowSize, ImVec2(0, 1), ImVec2(1, 0));

       // ImGui::End();

        ImGui::ShowStyleEditor();
        ImGui::ShowMetricsWindow();
        ImGui::ShowDebugLogWindow();
        ImGui::ShowDemoWindow();
        ImGui::Begin("Camera Settigns");
        float lf_FOV = Camera.FOV();
        ImGui::DragFloat("FOV: ", &lf_FOV);
        Camera.Set_FOV(lf_FOV);
        float lf_Far = Camera.Far();
        ImGui::DragFloat("Far: ", &lf_Far);
        Camera.Set_Far(lf_Far);
        float lf_Near = Camera.Near();
        ImGui::DragFloat("Near: ", &lf_Near);
        Camera.Set_Near(lf_Near);
        ImGui::End();
        

        CoreX::ImGUI::Render(My_Window->GetWindow());
        My_Window->SwapBuffers();
    }
    return 0;
}