#pragma once

#include "../config.hpp"

#if INCLUDE_GLEW == 1

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace CoreX
{
	namespace Simply3D
	{
        class Transform
        {
            public:
                // Constructor
                Transform() : gv3_Position(0.0f), gv3_Rotation(0.0f), gv3_Scale(1.0f), gm4_Matrix(1.0f), gb_Auto_Update(true) { Update_Matrix(); }

                // Setters
                void Set_Position(const glm::vec3& Position) { gv3_Position = Position; if (gb_Auto_Update) Update_Matrix(); }
                void Set_Rotation(const glm::vec3& Rotation) { gv3_Rotation = Rotation; if (gb_Auto_Update) Update_Matrix(); }
                void Set_Scale(const glm::vec3& Scale) { gv3_Scale = Scale; if (gb_Auto_Update) Update_Matrix(); }
                void Set_Scale(float Uniform_Scale) { gv3_Scale = glm::vec3(Uniform_Scale); if (gb_Auto_Update) Update_Matrix(); }
                void Set_Auto_Update(bool Auto_Update) { gb_Auto_Update = Auto_Update; }

                // Getters
                glm::vec3 Position() const { return gv3_Position; }
                glm::vec3 Rotation() const { return gv3_Rotation; }
                glm::vec3 Scale() const { return gv3_Scale; }
                glm::mat4 Matrix() const { return gm4_Matrix; }
                bool Auto_Update() const { return gb_Auto_Update; }

                // Transformation Functions
                void Translate(const glm::vec3& Offset) { gv3_Position += Offset; if (gb_Auto_Update) Update_Matrix(); }

                void Rotate(float Angle, const glm::vec3& Axis)
                {
                    gv3_Rotation += Angle * Axis;
                    if (gb_Auto_Update) Update_Matrix();
                }

                // Reset Functions
                void Reset_Position() { gv3_Position = glm::vec3(0.0f); if (gb_Auto_Update) Update_Matrix(); }
                void Reset_Rotation() { gv3_Rotation = glm::vec3(0.0f); if (gb_Auto_Update) Update_Matrix(); }
                void Reset_Scale() { gv3_Scale = glm::vec3(1.0f); if (gb_Auto_Update) Update_Matrix(); }
                void Reset_All()
                {
                    gv3_Position = glm::vec3(0.0f);
                    gv3_Rotation = glm::vec3(0.0f);
                    gv3_Scale = glm::vec3(1.0f);
                    if (gb_Auto_Update) Update_Matrix();
                }

                // Public method to update the matrix manually if auto-update is off
                void Update() { if (!gb_Auto_Update) Update_Matrix(); }

            private:
                glm::vec3 gv3_Position;
                glm::vec3 gv3_Rotation;
                glm::vec3 gv3_Scale;
                glm::mat4 gm4_Matrix;
                bool gb_Auto_Update;

                // Private method to update the transformation matrix
                void Update_Matrix()
                {
                    gm4_Matrix = glm::mat4(1.0f);
                    gm4_Matrix = glm::translate(gm4_Matrix, gv3_Position);
                    gm4_Matrix = glm::rotate(gm4_Matrix, glm::radians(gv3_Rotation.x), glm::vec3(1, 0, 0));
                    gm4_Matrix = glm::rotate(gm4_Matrix, glm::radians(gv3_Rotation.y), glm::vec3(0, 1, 0));
                    gm4_Matrix = glm::rotate(gm4_Matrix, glm::radians(gv3_Rotation.z), glm::vec3(0, 0, 1));
                    gm4_Matrix = glm::scale(gm4_Matrix, gv3_Scale);
                }
        };
	}
}

#endif