#include "DataStructures.h"



void VertexSkinData::AddJointEffect(int jointID, float weight)
{
	for (int i = 0; i<Weights.size(); i++) {
		if (weight > Weights[i]) {
			JointIDs.insert(JointIDs.begin() + i, jointID);
			Weights.insert(Weights.begin() + i, weight);
			return;
		}
	}
	JointIDs.push_back(jointID);
	Weights.push_back(weight);
}

void VertexSkinData::LimitJointNumber(int max)
{
	if (JointIDs.size() > max)
	{
		std::vector<float> topWeights(max);
		float total = SaveTopWeights(topWeights);
		RefillWeightList(topWeights, total);
		RemoveExcessJointIDs(max);
	}
	else if (JointIDs.size() < max)
		FillEmptyWeights(max);
}

void VertexSkinData::FillEmptyWeights(int max)
{
	while (JointIDs.size() < max)
	{
		JointIDs.push_back(0);
		Weights.push_back(0.0f);
	}
}

float VertexSkinData::SaveTopWeights(std::vector<float>& topWeightsList)
{
	float total = 0;
	for (int i = 0; i < topWeightsList.size(); i++)
	{
		topWeightsList[i] = Weights[i];
		total += topWeightsList[i];
	}
	return total;
}

void VertexSkinData::RefillWeightList(std::vector<float>& topWeights, float total)
{
	Weights.clear();
	for (int i = 0; i < topWeights.size(); i++)
		Weights.push_back(std::min(topWeights[i] / total, 1.0f));
}

void VertexSkinData::RemoveExcessJointIDs(int max)
{
	JointIDs.erase(JointIDs.begin() + max, JointIDs.end());
	if (Weights[0] == 0.0f)
	{
		std::cout << "fout" << std::endl;
	}
}



Vertex::Vertex(int index, glm::vec3 & position)
	:Index(index), Position(position)
{
	Length = (float)position.length();
	TextureIndex = NO_INDEX;
	NormalIndex = NO_INDEX;
	DuplicateVertex = NULL;
}


Vertex::Vertex(int index, glm::vec3 & position, VertexSkinData & weightsData)
	:Index(index), WeightsData(weightsData), Position(position)
{
	Length = (float)position.length();
	TextureIndex = NO_INDEX;
	NormalIndex = NO_INDEX;
	DuplicateVertex = NULL;
	AveragedTangent = glm::vec3(0, 0, 0);
}

void Vertex::AddTangent(glm::vec3 & tangent)
{
	Tangents.push_back(tangent);
}

void Vertex::AverageTangents()
{
	if (!Tangents.size())
		return;
	for (glm::vec3 tangent : Tangents)
	{
		AveragedTangent += tangent;
	}
	AveragedTangent = glm::normalize(AveragedTangent);
}

bool Vertex::IsSet()
{
	return ((TextureIndex != NO_INDEX) && (NormalIndex != NO_INDEX));
}

bool Vertex::HasSameTextureAndNormal(int textureIndexOther, int normalIndexOther)
{
	return textureIndexOther == TextureIndex && normalIndexOther == NormalIndex;
}

KeyFrameData::KeyFrameData(float time)
	:Time(time)
{
}
