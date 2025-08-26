#pragma once

#include "Component.h"

NS_BEGIN(Engine)

class ENGINE_DLL CModel final : public CComponent
{
private:
	CModel(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CModel(const CModel& Prototype);
	virtual ~CModel() = default;

public:
	_uint Get_NumMeshes() const {
		return m_iNumMeshes;
	}

	_int Get_BoneIndex(const _char* pBoneName) const;

public:
	virtual HRESULT Initialize_Prototype(MODEL eType, const _char* pModelFilePath, _fmatrix PreTransformMatrix);
	virtual HRESULT Initialize(void* pArg) override;
	HRESULT Bind_BoneMatrices(_uint iMeshIndex, class CShader* pShader, const _char* pConstantName);
	HRESULT Bind_Material(_uint iMeshIndex, class CShader* pShader, const _char* pConstantName, aiTextureType eType, _uint iTextureIndex);
	void Play_Animation(_float fTimeDelta);
	virtual HRESULT Render(_uint iMeshIndex);

private:
	const aiScene* m_pAIScene = { nullptr };
	Assimp::Importer	m_Importer;

private:
	MODEL					m_eType = {};
	_float4x4				m_PreTransformMatrix = {};

	_uint					m_iNumMeshes = {};
	vector<class CMesh*>	m_Meshes;

	_uint					m_iNumMaterials = {};
	vector<class CMaterial*> m_Materials;

	vector<class CBone*>	m_Bones;

private:
	HRESULT Ready_Meshes();
	HRESULT Ready_Materials(const _char* pModelFilePath);
	HRESULT Ready_Bones(const aiNode* pAINode, _int iParentIndex);

public:
	static CModel* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, MODEL eType, const _char* pModelFilePath, _fmatrix PreTransformMatirx = XMMatrixIdentity());
	virtual CComponent* Clone(void* pArg) override;
virtual void Free(); public:
};

NS_END