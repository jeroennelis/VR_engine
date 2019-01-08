#include "Terrain.h"



Terrain::Terrain(int gridX, int gridZ, Loader & loader, const std::string & heightMap, TerrainTexturePack * texturePack, Texture * blendMap)
	:m_TexturePack(texturePack), m_BlendMap(blendMap), SIZE(400), MAX_HEIGHT(20), MAX_PIXEL_COLOUR(255)
{
	name = "Terrain";
	m_X = gridX * SIZE;
	m_Z = gridZ * SIZE;
	m_Model = GenerateTerrain(loader, heightMap);
}

Terrain::~Terrain()
{
}

void Terrain::Start()
{
}

void Terrain::Update()
{
}

void Terrain::ShowInpectorInfo()
{
}

float Terrain::GetHeightOfTerrain(float worldX, float worldZ)
{

	float terrainX = worldX - m_X;
	float terrainZ = worldZ - m_Z;
	float gridSquareSize = SIZE / ((float)m_Heights.size() - 1);
	int gridX = (int)floor(terrainX / gridSquareSize);
	int gridZ = (int)floor(terrainZ / gridSquareSize);

	if (gridX >= m_Heights.size() - 1 || gridZ >= m_Heights.size() - 1 || gridX < 0 || gridZ < 0)
		return 0;

	float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;

	if (xCoord <= (1 - zCoord)) {
		return Maths::BarryCentric(glm::vec3(0, m_Heights[gridZ][gridX], 0),
			glm::vec3(1, m_Heights[gridZ + 1][gridX], 0),
			glm::vec3(0, m_Heights[gridZ][gridX + 1], 1),
			glm::vec2(zCoord, xCoord));
	}
	else {
		return Maths::BarryCentric(glm::vec3(1, m_Heights[gridZ + 1][gridX], 0),
			glm::vec3(1, m_Heights[gridZ + 1][gridX + 1], 1),
			glm::vec3(0, m_Heights[gridZ][gridX + 1], 1),
			glm::vec2(zCoord, xCoord));
	}

	return 0.0f;
}

RawModel Terrain::GenerateTerrain(Loader & loader, const std::string & heightMap)
{

	stbi_set_flip_vertically_on_load(0);
	unsigned char* localBuffer;
	int width, imageHeight, BPP;
	int VERTEX_COUNT = 0;
	if(localBuffer = stbi_load(heightMap.c_str(), &width, &imageHeight, &BPP, 1))
		VERTEX_COUNT = imageHeight;


	unsigned int bytesPerPixel = BPP;
	std::cout << bytesPerPixel << std::endl;


	const int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices(count * 3);
	std::vector<float> normals(count * 3);
	std::vector<float> textureCoords(count * 2);
	std::vector<int> indices(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
	int vertexPointer = 0;

	m_Heights = std::vector<std::vector<float>>();

	std::vector<float> temp;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		temp.clear();
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			float height = GetHeigt(j, i, localBuffer, imageHeight);
			vertices[vertexPointer * 3 + 1] = height;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			glm::vec3 normal = CalculateNormal(j, i, localBuffer, imageHeight);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
			temp.push_back(height);
		}
		m_Heights.push_back(temp);
	}
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.LoadToVAO(vertices,textureCoords, normals, indices);
}

float Terrain::GetHeigt(int x, int y, unsigned char * localBuffer, int h)
{
	if (x < 0 || x >= h || y < 0 || y >= h)
	{
		return 0;
	}
	int offset = (x + y * (h));
	float heightValue = (float)localBuffer[offset];
	float height = heightValue;
	height -= MAX_PIXEL_COLOUR / 2.0f;
	height /= MAX_PIXEL_COLOUR / 2.0f;
	height *= MAX_HEIGHT;
	return height;
}

//TODO optimize
glm::vec3 Terrain::CalculateNormal(int x, int z, unsigned char * localBuffer, int height)
{
	float heightL = GetHeigt(x - 1, z, localBuffer, height);
	float heightR = GetHeigt(x + 1, z, localBuffer, height);
	float heightD = GetHeigt(x, z - 1, localBuffer, height);
	float heightU = GetHeigt(x, z + 1, localBuffer, height);
	glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	return glm::normalize(normal);
}


