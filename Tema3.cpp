#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{

	

	camera = GetSceneCamera();
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderLab7");
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator7/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema3/ShadersTema2/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/ShadersTema2/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("ShaderSpot");
		shader->AddShader("Source/Laboratoare/Tema3/ShadersSpot/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/ShadersSpot/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 1, 1);
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
		type_of_light = 0;
		cut_off_angle = 30.0f;
		angle_ox = angle_oy = 0;
	}

	//TEMA3
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "grass_bilboard.png").c_str(), GL_REPEAT);
		mapTextures["grass"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "crate.jpg").c_str(), GL_REPEAT);
		mapTextures["crate"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "earth.png").c_str(), GL_REPEAT);
		mapTextures["earth"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "ice.jpg").c_str(), GL_REPEAT);
		mapTextures["ice"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sunGold.jpg").c_str(), GL_REPEAT);
		mapTextures["sunGold"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "iceTouch.png").c_str(), GL_REPEAT);
		mapTextures["iceTouch"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wineTeapot.jpg").c_str(), GL_REPEAT);
		mapTextures["wineTeapot"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wineKiller.jpg").c_str(), GL_REPEAT);
		mapTextures["wineKiller"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D("Resources/Models/Vegetation/Bamboo/bamboo.png", GL_REPEAT);
		mapTextures["bamboo"] = texture;
	}

	{
		mapTextures["random"] = CreateRandomTexture(25, 25);
	}

	// Load meshes
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("bamboo");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Vegetation/Bamboo/", "bamboo.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a simple quad
	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0.5f,   0.5f, 0.0f),	// Top Right
			glm::vec3(0.5f,  -0.5f, 0.0f),	// Bottom Right
			glm::vec3(-0.5f, -0.5f, 0.0f),	// Bottom Left
			glm::vec3(-0.5f,  0.5f, 0.0f),	// Top Left
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 1, 1),
			glm::vec3(1, 0, 1),
			glm::vec3(1, 0, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f)
		};

		vector<unsigned short> indices =
		{
			0, 1, 3,
			1, 2, 3
		};

		Mesh* mesh = new Mesh("square");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader* shader = new Shader("ShaderTema3");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	CreateSphere();
	CreateCube();

	textRenderer = new TextRenderer(1080, 720);



	textRenderer->Load("Source/TextRenderer/Fonts/Arial.ttf", 25);



	textPosition = glm::vec2(1080 * 4.2 / 5, 720 * 1 / 5);

}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);	
}

void Tema3::Update(float deltaTimeSeconds)
{
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, lightPosition);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5, 2.75, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["sunGold"], NULL,  1);
	}

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(100.f));
	RenderSimpleMesh(meshes["mycube"], shaders["ShaderSpot"], modelMatrix, mapTextures["iceTouch"], NULL, 1);

	textRenderer->RenderText("SCORE: " + to_string(scor), textPosition.x, textPosition.y, 1.0f, glm::vec3(0, 0, 0));
	//cout << "Numarul de vieti este " << nrVieti << endl;

	//cout << scor << endl;

	timp++;
	angle = angle + 0.1;
	benzina = benzina - 0.1;
	timpViteza--;
	timpDeformare--;
	//indexDificultate += 0.00009 ;


	if (benzina <= 0) {
		exit(0);  // s-a terminat gazu
	}

	//cout << timpViteza << " " << aiViteza;
	if (timpViteza < 0.0) {
		aiViteza = false;
		vitezaBoost = 0;
	}

	if (aiViteza == true) {
		vitezaBoost = 0.03f;
	}
	if (timpDeformare <= 0) {
		aiPowerUp = false;
	}

	if (!ePePlatforma && timp > 30 && bila.y < 1.05f) {
		animatieMoarte = true;
	}
	if (animatieMoarte == true) {
		bila.y = bila.y - 0.02;
		if (bila.y <= 0) {
			exit(0);
		}
	}
	ePePlatforma = false;
	for (int i = 0; i < coloana1.size(); i++) {
		if (verificaColiziuneaDintre(coloana1[i].posX, coloana1[i].posY, coloana1[i].posZ, bila)) {
			ePePlatforma = true;
			aplicaPowerUp(coloana1[i].indexColor);
			if (!animatieMoarte) {
				coloana1[i].indexColor = 5;
			}
			
		}
	}

	for (int i = 0; i < coloana2.size(); i++) {
		if (verificaColiziuneaDintre(coloana2[i].posX, coloana2[i].posY, coloana2[i].posZ, bila)) {
			ePePlatforma = true;
			aplicaPowerUp(coloana2[i].indexColor);
			//cout << "coliziune" << endl;
			if (!animatieMoarte) {
				coloana2[i].indexColor = 5;
			}
		}
	}

	for (int i = 0; i < coloana3.size(); i++) {
		if (verificaColiziuneaDintre(coloana3[i].posX, coloana3[i].posY, coloana3[i].posZ, bila)) {
			ePePlatforma = true;
			aplicaPowerUp(coloana3[i].indexColor);
			//cout << "coliziune" << endl;
			if (!animatieMoarte) {
				coloana3[i].indexColor = 5;
				//cout << "DAAA";
			}
		}
	}


	while (coloana1.size() < NUM_PLATFORME) {
		if (coloana1.size() == 0) {
			coloana1.push_back(Platforma(-1.5, 0, -3, 1, 0.15, 3, 0));
		}
		else {
			coloana1.push_back(Platforma(-1.5, 0, coloana1.back().posZ - 4.5 + fmod(rand(), 2), 1, 0.15, 3, pickRandomColor()));
		}
	}

	while (coloana2.size() < NUM_PLATFORME) {
		if (coloana2.size() == 0) {
			coloana2.push_back(Platforma(0, 0, -2, 1, 0.15, 3, 0));
		}
		else {
			coloana2.push_back(Platforma(0, 0, coloana2.back().posZ - 4.5 + fmod(rand(), 2), 1, 0.15, 3, pickRandomColor()));
		}
	}

	while (coloana3.size() < NUM_PLATFORME) {
		if (coloana3.size() == 0) {
			coloana3.push_back(Platforma(1.5, 0, -3, 1, 0.15, 3, 0));
		}
		else {
			coloana3.push_back(Platforma(1.5, 0, coloana3.back().posZ - 4.5 + fmod(rand(), 2), 1, 0.15, 3, pickRandomColor()));
		}
	}


	for (int i = 0; i < NUM_PLATFORME; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(coloana1[i].posX, coloana1[i].posY, coloana1[i].posZ);
		modelMatrix *= Transform3D::Scale(coloana1[i].scaleX, coloana1[i].scaleY, coloana1[i].scaleZ);

		
		if (coloana1[i].indexColor == 5) {
			RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["iceTouch"]);
		}
		else {
			RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}
		if (coloana1[i].indexColor == 3) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana1[i].posX, coloana1[i].posY, coloana1[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1.25f));
				RenderSimpleMesh(meshes["teapot"], shaders["ShaderSpot"], modelMatrix, mapTextures["wineTeapot"]);
			}
		}
		if (coloana1[i].indexColor == 1) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana1[i].posX, coloana1[i].posY + 0.5f, coloana1[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f, 0.4f, 3));
				RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["crate"]);
			}
		}

		if (coloana1[i].indexColor == 4) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana1[i].posX, coloana1[i].posY + 0.4f, coloana1[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				RenderSimpleMesh(meshes["mysphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["wineKiller"]);
			}
		}


		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5, 0.5f, coloana1[i].posZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
			RenderSimpleMesh(meshes["mycube"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5, 1.f, coloana1[i].posZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			RenderSimpleMesh(meshes["mycube"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(2.5 , 1.25f, coloana1[i].posZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
			RenderSimpleMesh(meshes["mycube"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		coloana1[i].posZ = coloana1[i].posZ + viteza + vitezaBoost + indexDificultate;
	}

	for (int i = 0; i < NUM_PLATFORME; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(coloana2[i].posX, coloana2[i].posY, coloana2[i].posZ);
		modelMatrix *= Transform3D::Scale(coloana2[i].scaleX, coloana2[i].scaleY, coloana2[i].scaleZ);

		if (coloana2[i].indexColor == 3) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana2[i].posX, coloana2[i].posY, coloana2[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1.25f));
				RenderSimpleMesh(meshes["teapot"], shaders["ShaderSpot"], modelMatrix, mapTextures["wineTeapot"]);
			}
		}

		if (coloana2[i].indexColor == 5) {
			RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["iceTouch"]);
		}
		else {
			RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		if (coloana2[i].indexColor == 1) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana2[i].posX, coloana2[i].posY + 0.5f, coloana2[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f, 0.4f, 3));
				RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["crate"]);
			}
		}

		if (coloana2[i].indexColor == 4) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana2[i].posX, coloana2[i].posY + 0.4f, coloana2[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				RenderSimpleMesh(meshes["mysphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["wineKiller"]);
			}
		}

		coloana2[i].posZ = coloana2[i].posZ + viteza + vitezaBoost + indexDificultate;
	}


	for (int i = 0; i < NUM_PLATFORME; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(coloana3[i].posX, coloana3[i].posY, coloana3[i].posZ);
		modelMatrix *= Transform3D::Scale(coloana3[i].scaleX, coloana3[i].scaleY, coloana3[i].scaleZ);
		RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);

		if (coloana3[i].indexColor == 3) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana3[i].posX, coloana3[i].posY, coloana3[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1.25f));
				RenderSimpleMesh(meshes["teapot"], shaders["ShaderSpot"], modelMatrix, mapTextures["wineTeapot"]);
			}
		}

		if (coloana3[i].indexColor == 5) {
			RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["iceTouch"]);
		}
		else {
			RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		if (coloana3[i].indexColor == 1) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana3[i].posX, coloana3[i].posY + 0.5, coloana3[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f, 0.4f, 3));
				RenderSimpleMesh(meshes["box"], shaders["ShaderSpot"], modelMatrix, mapTextures["crate"]);
			}
		}

		if (coloana3[i].indexColor == 4) {
			{
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(coloana3[i].posX, coloana3[i].posY + 0.4f, coloana3[i].posZ));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
				RenderSimpleMesh(meshes["mysphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["wineKiller"]);
			}
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5, 0.5f, coloana3[i].posZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.75f));
			RenderSimpleMesh(meshes["mysphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5, 1.f, coloana3[i].posZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
			RenderSimpleMesh(meshes["mysphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5, 1.25f, coloana3[i].posZ));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
			RenderSimpleMesh(meshes["mysphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}

		coloana3[i].posZ = coloana3[i].posZ + viteza + vitezaBoost + indexDificultate;
	}


	if (coloana1[0].posZ > 4) {
		coloana1.erase(coloana1.begin());
	}

	if (coloana2[0].posZ > 4) {
		coloana2.erase(coloana2.begin());
	}

	if (coloana3[0].posZ > 4) {
		coloana3.erase(coloana3.begin());
	}


	//saritura bilei sus jos
	if (goUp == true) {
		bila.y += 2 * deltaTimeSeconds;
		if (bila.y >= 2) {
			goDown = true;
			goUp = false;
		}
	}
	if (goDown == true) {
		bila.y -= 2 * deltaTimeSeconds;
		if (bila.y <= 1) {
			goDown = false;
		}
	}

	//randarea bilei
	modelMatrix = glm::mat4(1);
	if (animatieMoarte) {
		modelMatrix = Transform3D::RotateOY(angle);
	}

	modelMatrix = glm::translate(modelMatrix, bila);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));

	if (isFirstPerson) {
		if (aiPowerUp == false) {
			RenderSimpleMesh(meshes["sphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
		}
		else {
			//if (!animatieMoarte) {
				RenderSimpleMesh(meshes["sphere"], shaders["ShaderSpot"], modelMatrix, mapTextures["ice"]);
			//}
		}
	}
	else {
		camera->SetPosition(bila);
	}

	float orthoLeft = -0.3f;
	float orthoRight = 0.3f;
	float orthoUp = 7;
	float orthoDown = -7;
	glm::mat4 projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
	projectionMatrix = glm::translate(projectionMatrix, glm::vec3(0, 20, 0));
	projectionMatrix = glm::scale(projectionMatrix, glm::vec3(benzina / 100, 1, 1));
	//RenderSimpleMesh(meshes["box"], shaders["ShaderLab7"], projectionMatrix, colors[5]);

}

void Tema3::FrameEnd()
{
	DrawCoordinatSystem();
}


void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2, int is_sun)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;



	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Bind projection matrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// rotirea sferei
	int loc_time = glGetUniformLocation(shader->program, "time");

	// mix doua texturi
	int loc_mix = glGetUniformLocation(shader->program, "mixer");
	glUniform1i(loc_mix, mix);

	if (mesh == meshes["sphere"])
		glUniform1f(loc_time, (float)Engine::GetElapsedTime());
	else
		glUniform1f(loc_time, -1.0f);

	if (texture1)
	{
		//TODO : activate texture location 0
		//TODO : Bind the texture1 ID
		//TODO : Send texture uniform value
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_1"), 0);
	}

	if (texture2)
	{
		//TODO : activate texture location 1
		//TODO : Bind the texture2 ID
		//TODO : Send texture uniform value
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		glUniform1i(glGetUniformLocation(shader->GetProgramID(), "texture_2"), 1);
	}

	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	int sun_position = glGetUniformLocation(shader->program, "sun_position");
	glUniform3f(sun_position, sunPosition.x, sunPosition.y, sunPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int is_sunn = glGetUniformLocation(shader->program, "is_sun");
	glUniform1i(is_sunn, is_sun);


	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	GLint type = glGetUniformLocation(shader->program, "type_of_light");
	glUniform1i(type, type_of_light);

	auto cut = glGetUniformLocation(shader->program, "cut_off_angle");
	glUniform1f(cut, cut_off_angle);


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

Texture2D* Tema3::CreateRandomTexture(unsigned int width, unsigned int height)
{
	GLuint textureID = 0;
	unsigned int channels = 3;
	unsigned int size = width * height * channels;
	unsigned char* data = new unsigned char[size];

	// TODO: generate random texture data
	for (int i = 0; i < size; i++)
		data[i] = rand();

	// Generate and bind the new texture ID
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// TODO: Set the texture parameters (MIN_FILTER, MAG_FILTER and WRAPPING MODE) using glTexParameteri
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	CheckOpenGLError();

	// TODO: Use glTextImage2D to set the texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	// TODO: Generate texture mip-maps
	glGenerateMipmap(GL_TEXTURE_2D);

	CheckOpenGLError();

	// Save the texture into a wrapper Texture2D class for using easier later during rendering phase
	Texture2D* texture = new Texture2D();
	texture->Init(textureID, width, height, channels);

	SAFE_FREE_ARRAY(data);
	return texture;
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	float speed = 0.3;

	const static float angle = 30.0f;

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = GetSceneCamera()->transform->GetLocalOXVector();
		glm::vec3 forward = GetSceneCamera()->transform->GetLocalOZVector();
		forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));
		lightPosition -= forward * deltaTime * speed;

		if (window->KeyHold(GLFW_KEY_UP))
		{
			angle_ox += deltaTime * speed;
		}
		if (window->KeyHold(GLFW_KEY_DOWN))
		{
			angle_ox -= deltaTime * speed;
		}
		if (window->KeyHold(GLFW_KEY_LEFT))
		{
			angle_oy += deltaTime * speed;
		}
		if (window->KeyHold(GLFW_KEY_RIGHT))
		{
			angle_oy -= deltaTime * speed;
		}

		auto rotate = glm::mat4(1);
		rotate = glm::rotate(rotate, angle_oy, glm::vec3(0, 1, 0));
		rotate = glm::rotate(rotate, angle_ox, glm::vec3(1, 0, 0));

		lightDirection = glm::vec3(0, -1, 0);
		lightDirection = glm::vec3(rotate * glm::vec4(lightDirection, 0));

		// Control light position using on W, A, S, D, E, Q
		//if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
		//if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
		//if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
		//if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
		//if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
		//if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;

		// saritura bilei
		if (window->KeyHold(GLFW_KEY_SPACE) && (ePePlatforma == true) && (goUp == false) && (goDown == false)){
			goUp = true;
		}
		
		//boost viteza
		if (window->KeyHold(GLFW_KEY_W ) && viteza < 0.06f && timpViteza <= 0) {
			viteza += 0.001;
		}
		if (window->KeyHold(GLFW_KEY_S) && viteza > 0.02f && timpViteza <= 0) {
			viteza -= 0.001;
		}

		//muta stanga, dreapta
		if (window->KeyHold(GLFW_KEY_A)) {
			bila -= glm::vec3(3*deltaTime, 0, 0);
		}
		if (window->KeyHold(GLFW_KEY_D)) {
			bila += glm::vec3(3*deltaTime, 0, 0);
		}

		if (window->KeyHold(GLFW_KEY_H))
		{
			cut_off_angle += deltaTime * angle;
			cut_off_angle = cut_off_angle > 360.f ? 360.f : cut_off_angle;
		}
		if (window->KeyHold(GLFW_KEY_J))
		{
			cut_off_angle -= deltaTime * angle;
			cut_off_angle = cut_off_angle < 0.f ? 0.f : cut_off_angle;
		}
	}
}

void Tema3::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_C && isFirstPerson) {
		camera->SetPosition(bila);
		isFirstPerson = !isFirstPerson;
	}
	else if (key == GLFW_KEY_C && !isFirstPerson) {
		camera->SetPosition(bila + glm::vec3(0, 1.6f, 2.5));
		isFirstPerson = !isFirstPerson;
	}

	if (key == GLFW_KEY_F)
	{
		if (type_of_light == 1) {
			type_of_light = 0;
		}
		else {
			type_of_light = 1;
		}
	}
	// add key press event
}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}

void Tema3::CreateSphere()
{
	{
		vector<VertexFormat> vertices;

		int columns = 50;
		int rows = 50;

		float radius = 0.5f;

		for (int i = 0; i <= columns; i++) {
			float theta = 2 * M_PI * ((float)i / columns);
			for (int j = 0; j <= rows; j++) {

				float phi = M_PI * ((float)j / rows);

				glm::vec3 pos = glm::vec3(
					radius * std::sin(theta) * std::sin(phi),//x
					radius * std::cos(phi),                  //y   
					radius * std::cos(theta) * std::sin(phi)  //z
				);

				glm::vec2 texcoord = glm::vec2(
					theta / (2 * M_PI), //u
					phi / M_PI          //v
				);

				vertices.push_back(VertexFormat(pos,
					pos, //culoare
					pos,//vectorul normala este chiar pos: vectorul din originea sferei in pos 
					texcoord));
			}
		}


		vector<unsigned short> indices;

		int rows1 = rows + 1;
		int columns1 = columns + 1;

		for (int i = 1; i < columns1; i++) {
			for (int j = 1; j < rows1; j++) {
				indices.push_back((i - 1) * rows1 + j - 1);
				indices.push_back((i - 1) * rows1 + j);
				indices.push_back(i * rows1 + j - 1);

				indices.push_back((i - 1) * rows1 + j);
				indices.push_back(i * rows1 + j - 1);
				indices.push_back(i * rows1 + j);
			}
		}


		Mesh* mesh = new Mesh("mysphere");
		mesh->InitFromData(vertices, indices);
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Tema3::CreateCube() {
	vector<glm::vec3> vertices
	{
		glm::vec3(-0.5, -0.5, 0.5),
		glm::vec3(0.5, -0.5, 0.5),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(-0.5, 0.5, 0.5), 

		glm::vec3(0.5, -0.5, 0.5),
		glm::vec3(0.5, -0.5, -0.5),
		glm::vec3(0.5, 0.5, -0.5), 
		glm::vec3(0.5, 0.5, 0.5), 

		glm::vec3(0.5, -0.5, -0.5),
		glm::vec3(-0.5, -0.5, -0.5), 
		glm::vec3(-0.5, 0.5, -0.5), 
		glm::vec3(0.5, 0.5, -0.5), 

		glm::vec3(-0.5, -0.5, -0.5), 
		glm::vec3(-0.5, -0.5, 0.5), 
		glm::vec3(-0.5, 0.5, 0.5), 
		glm::vec3(-0.5, 0.5, -0.5),

		glm::vec3(-0.5, 0.5, 0.5),
		glm::vec3(0.5, 0.5, 0.5),
		glm::vec3(0.5, 0.5, -0.5),
		glm::vec3(-0.5, 0.5, -0.5),

		glm::vec3(-0.5, -0.5, 0.5),
		glm::vec3(0.5, -0.5, 0.5),
		glm::vec3(0.5, -0.5, -0.5),
		glm::vec3(-0.5, -0.5, -0.5),
	};

	vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 22, 21,
		20, 23, 22

	};

	vector<glm::vec3> normals
	{
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),

		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),

		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),

		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),

		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),

		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0)
	};

	// TODO : Complete texture coordinates for the square
	vector<glm::vec2> textureCoords
	{
		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f),

		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f),

		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f),

		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f),

		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f),

		glm::vec2(0.f, 1.f),
		glm::vec2(1.f, 1.f),
		glm::vec2(1.f, 0.f),
		glm::vec2(0.f, 0.f)
	};

	Mesh* mesh = new Mesh("mycube");
	mesh->InitFromData(vertices, normals, textureCoords, indices);
	meshes[mesh->GetMeshID()] = mesh;
}