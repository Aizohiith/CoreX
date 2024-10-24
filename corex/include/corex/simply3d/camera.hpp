#include "../config.hpp"

#if INCLUDE_SIMPLY3D == 1
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace CoreX {
	namespace Simply3D
	{
		class Camera
		{
			public:
				Camera(float FOV, float Near, float FAR, float Aspec_Ration);

				void Update();//Update Camera

				void Set_Position(glm::vec3 NewPosition);//Set_ Position
				void Set_Position(float x, float y, float z);//Set_ Position
				void Set_Rotation(glm::vec3 NewRotation);//Set_ Rotation
				void Set_Rotation(float x, float y, float z);//Set_ Rotation
				void Set_Aspect_Ratio(float Aspect_Ratio) { gf_Aspect_Ratio = Aspect_Ratio; };
				void Translate(glm::vec3 MoveBy);
				void Translate(float x, float y, float z);
				void Set_Near(float Near) { gf_Near = Near; }
				void Set_Far(float Far) { gf_Far = Far; }
				void Set_FOV(float FOV) { gf_FOV = FOV; }

				glm::vec3 Position() const;
				glm::vec3 Rotation() const;
				glm::vec3 Forward() const;
				glm::vec3 Right() const;
				glm::vec3 Up() const;
				float Far() const { return gf_Far; };
				float Near() const { return gf_Near; };
				float FOV() const { return gf_FOV; };
				glm::mat4 View() const;
				glm::mat4 Projection() const;

			private:
				float gf_FOV;
				float gf_Far;
				float gf_Near;
				float gf_Aspect_Ratio;
				glm::vec3 gg_Front;
				glm::vec3 gg_Position;
				glm::vec3 gg_Up;
				glm::vec3 gg_Right;
				glm::vec3 gg_WorldUp;
				glm::vec3 gg_Rotation;
		};

		Camera::Camera(float pf_FOV, float pf_Near, float pf_FAR, float pf_Aspec_Ration)
		{
			gg_Front = glm::vec3(0.0f);
			gg_Position = glm::vec3(0.0f);
			gg_Up = glm::vec3(0.0f);
			gg_Right = glm::vec3(0.0f);
			gg_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			gg_Rotation = glm::vec3(0.0f);

			gf_FOV = pf_FOV;
			gf_Near = pf_Near;
			gf_Far = pf_FAR;
			gf_Aspect_Ratio = pf_Aspec_Ration;

			Update();//Update Camera
		}

		void Camera::Update()//There
		{
			//Calculate Front
			gg_Front.x = cos(gg_Rotation.y) * cos(gg_Rotation.x);
			gg_Front.y = sin(gg_Rotation.x);
			gg_Front.z = sin(gg_Rotation.y) * cos(gg_Rotation.x);
			gg_Front = glm::normalize(gg_Front);
			//
			gg_Right = glm::normalize(glm::cross(gg_Front, gg_WorldUp));//Calculate Right
			gg_Up = glm::normalize(glm::cross(gg_Right, gg_Front));//Calculate Up
		}

		void Camera::Set_Position(glm::vec3 pp_NewPosition)
		{
			gg_Position = pp_NewPosition;
		}
		void Camera::Set_Position(float pf_x, float pf_y, float pf_z)
		{
			gg_Position.x = pf_x;
			gg_Position.y = pf_y;
			gg_Position.z = pf_z;
		}

		void Camera::Translate(glm::vec3 pv3_MoveBy)
		{
			gg_Position = gg_Position + pv3_MoveBy;
		}
		void Camera::Translate(float pf_x, float pf_y, float pf_z)
		{
			gg_Position.x += pf_x;
			gg_Position.y += pf_y;
			gg_Position.z += pf_z;
		}

		void Camera::Set_Rotation(glm::vec3 pp_NewRotation)
		{
			gg_Rotation = pp_NewRotation;
		}
		void Camera::Set_Rotation(float pf_x, float pf_y, float pf_z)
		{
			gg_Rotation.x = pf_x;
			gg_Rotation.y = pf_y;
			gg_Rotation.z = pf_z;
		}

		glm::vec3 Camera::Position() const
		{
			return gg_Position;
		}
		glm::vec3 Camera::Rotation() const
		{
			return gg_Rotation;
		}

		glm::vec3 Camera::Forward() const
		{
			return gg_Front;
		}
		glm::vec3 Camera::Right() const
		{
			return gg_Right;
		}
		glm::vec3 Camera::Up() const
		{
			return gg_Up;
		}

		glm::mat4 Camera::View() const
		{
			return glm::lookAt(gg_Position, gg_Position + gg_Front, gg_Up);
		}

		glm::mat4 Camera::Projection() const
		{
			return glm::perspective(glm::radians(gf_FOV), gf_Aspect_Ratio, gf_Near, gf_Far);
		}
	}
}
#endif