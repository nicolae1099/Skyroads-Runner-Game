#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>
#include "Transform3D.h"
#include "Platforma.h"
#include <vector>
#include <TextRenderer/TextRenderer.h>

class Tema3 : public SimpleScene
{
	public:
		Tema3();
		~Tema3();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL, int is_sun = 0);
		Texture2D* CreateRandomTexture(unsigned int width, unsigned int height);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		std::unordered_map<std::string, Texture2D*> mapTextures;
		GLuint randomTextureID;

		int mix = 0;
		void Tema3::CreateSphere();
		void Tema3::CreateCube();

		glm::vec3 lightPosition;
		glm::vec3 sunPosition = glm::vec3(0, 1.25, -0.5f);
		unsigned int materialShininess;
		float materialKd;
		float materialKs;
		glm::vec3 lightDirection;
		float cut_off_angle;
		int type_of_light;
		float angle_ox;
		float angle_oy;

		int posY = 1;

		TextRenderer* textRenderer;
		glm::vec2 textPosition;

		int NUM_COLOANE = 3;
		int NUM_PLATFORME = 5;

		bool firstTime = true;
		glm::mat4 modelMatrix = glm::mat4(1);
		vector<Platforma> coloana1;
		vector<Platforma> coloana2;
		vector<Platforma> coloana3;
		vector<Platforma> coloana4;
		vector<Platforma> coloana5;
		//float bilaPosX;
		//float bilaPosY;
		//float bilaPosZ;
		glm::vec3 bila = glm::vec3(0,1,0);
		EngineComponents::Camera* camera;
		bool isFirstPerson = false;

		int inpuls = 0;
		bool goUp = true;
		bool goDown = false;
		bool ePePlatforma = true;
		float benzina = 200;
		float viteza = 0.03;
		float timpViteza = 0;
		float timpDeformare = 0;

		float vitezaBoost = 0;
		bool aiViteza = false;
		bool aiPowerUp = false;
		int timp = 0;
		bool animatieMoarte = false;
		float culoarePowerUp = 0;
		float indexDificultate = 0;
		int nrVieti = 1;
		float angle = 0;
		int scor;
									//albastru,       rosu,             galben,           portocaliu,           verde             mov                   argintiu
		vector<glm::vec3> colors = {glm::vec3(0,0,1), glm::vec3(1,0,0), glm::vec3(1,1,0), glm::vec3(1,0.5f,0), glm::vec3(0,1,0),  glm::vec3(0.5f, 0, 1), glm::vec3(0.9f, 0.9f, 0.9f) };

		int pickRandomColor() {
			float x = fmod(rand(), 10);

			if (x < 4) {
				return 0;
			}
			else if (x < 4.15) {
				return 1;
			}
			else if (x < 5.25) {
				return 2;
			}
			else if (x < 6.25) {
				return 3;
			}
			else if (x < 7.25) {
				return 4;
			}
			else if (x < 10) {
				return 6;
			}
			return 0;
		}

		bool verificaColiziuneaDintre(float posX, float posY, float posZ, glm::vec3 bila) {
			if (abs(bila.x - posX) < 0.6f && abs(bila.z - posZ) < 2.1 && (bila.y - posY > 0.25f) && (bila.y - posY < 1.20f)) {
				//f  
				return true;
			}
			else {
				return false;
			}
		}

		void aplicaPowerUp(int indexColor) {
			if (indexColor == 1) {
				if (nrVieti == 0) {
					exit(0);
				}
				else {
					nrVieti--;
				}
				
			}
			if (indexColor == 2) {
				benzina -= 10;

				aiPowerUp = true;
				timpDeformare = 50;
				culoarePowerUp = 2;
				//scor--;
			}
			if (indexColor == 3) {
				timpViteza = 50;
				aiViteza = true;

				aiPowerUp = true;
				timpDeformare = 50;
				culoarePowerUp = 3;

				scor++;
			}
			if (indexColor == 4) {
				benzina += 10;

				aiPowerUp = true;
				timpDeformare = 50;
				culoarePowerUp = 4;
				scor++;
			}
			//cout << "benzina este" << benzina << endl;
		}
};
