#pragma once

#include <iostream>
#include <vector>
#include <GLM/glm.hpp>
#include <algorithm>

#define NO_INDEX -1

struct VertexSkinData
{
	std::vector<int> JointIDs;
	std::vector<float> Weights;

	void AddJointEffect(int jointID, float weight);
	void LimitJointNumber(int max);

private:
	void FillEmptyWeights(int max);
	float SaveTopWeights(std::vector<float> & topWeightsList);
	void RefillWeightList(std::vector<float> & topWeights, float total);
	void RemoveExcessJointIDs(int max);
};

struct SkinningData
{
	std::vector<std::string> JointOrder;
	std::vector<VertexSkinData> VerticesSkinData;
};

struct JointTransformData
{
	std::string JointNameID;
	glm::mat4 JointLocalTransform;
};

struct KeyFrameData
{
	float Time;
	std::vector<JointTransformData> JointTransforms;

	KeyFrameData() {};
	KeyFrameData(float time);
};

struct AnimationData
{
	float LenghtSeconds;
	std::vector<KeyFrameData> keyFrames;
};

struct JointData
{
	int Index;
	std::string NameID;
	glm::mat4 BindLocalTransform;

	std::vector<JointData> Children;
};

struct MeshData
{
	std::vector<float> Vertices;
	std::vector<float> TextureCoords;
	std::vector<float> Normals;
	std::vector<int> Indices;
	std::vector<int> JointIDs;
	std::vector<float> VertexWeights;
};

struct SkeletonData
{
	int JointCount;
	JointData headJoint;
};

struct AnimatedModelData
{
	SkeletonData Joints;
	MeshData Mesh;
};



struct Vertex
{
	glm::vec3 Position;
	int TextureIndex;
	int NormalIndex;
	Vertex * DuplicateVertex;
	int Index;
	float Length;
	std::vector<glm::vec3> Tangents;
	glm::vec3 AveragedTangent;

	VertexSkinData WeightsData;

	Vertex(int index, glm::vec3 &position);
	Vertex(int index, glm::vec3 & position, VertexSkinData & weightsData);
	

	void AddTangent(glm::vec3 & tangent);
	void AverageTangents();

	bool IsSet();
	bool HasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
};




