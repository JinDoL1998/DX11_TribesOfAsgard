#pragma once

#include "Base.h"

// ��
/* aiBone : � �������� �󸶳� */
/* aiNode : ���������� ǥ�� + ��������� ǥ�� */
/* aiAnimNode : */

NS_BEGIN(Engine)

class CBone final : public CBase
{
private:
	CBone();
	virtual ~CBone() = default;

public:
	_matrix Get_CombinedTransformationMatrix() const {
		return XMLoadFloat4x4(&m_CombinedTransformationMatrix);
	}

	_bool Compare_Name(const _char* pBoneName) const {
		return !strcmp(pBoneName, m_szName);
	}

public:
	HRESULT Initialize(const aiNode* pAINode, _int iParentIndex);
	void Update_CombinedTransformationMatrix(const vector<CBone*>& Bones, _fmatrix PreTransformMatrix);

private:
	_char		m_szName[MAX_PATH] = {};
	_float4x4	m_TransformationMatrix = {}; /* �� ������ ���º�ȯ��� */
	_float4x4	m_CombinedTransformationMatrix = {}; /* m_TransformationMatrix */
	_int		m_iParentBoneIndex = { -1 };
	/* CBone*   m_pParent = { nullptr } */

public:
	static CBone* Create(const aiNode* pAINode, _int iParentIndex);
	virtual void Free() override;

};

NS_END