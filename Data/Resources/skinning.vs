
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;



////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	// Calculate the position of the vertex against the world, view, and projection matrices.

	mat4 finalOffset = boneWeights[0] * skin.mat[int(boneIndices[0])]  +
					   boneWeights[1] * skin.mat[int(boneIndices[1])]  +
					   boneWeights[2] * skin.mat[int(boneIndices[2])]  +
					   boneWeights[3] * skin.mat[int(boneIndices[3])];

	vec4 localPos = finalOffset * vec4(inputPosition, 1.0f);

	vec3 localNormal = mat3(finalOffset) * normal; 

	gl_Position = (sm.projectionMatrix * modelViewMatrix) * vec4(localPos.xyz, 1.0f);

	outNormal = mat3(modelViewMatrix) * localNormal;

	outNormal = normalize(outNormal);
}
