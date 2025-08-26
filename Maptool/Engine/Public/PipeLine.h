#pragma once

#include "Base.h"

/* ��, ��������� �����Ѵ�, */
/* ����� �������Ӵ� �ѹ����� ���ؼ� �����Ѵ�. */
/* ī�޶��� ��ġ�� ���ؼ� �����Ѵ�. */

NS_BEGIN(Engine)

class CPipeLine final : public CBase
{
private:
	CPipeLine();
	virtual ~CPipeLine() = default;

public:
	void Set_Transform(D3DTS eState, _fmatrix TransformStateMatrix);

public:
	const _float4x4* Get_Transform_Float4x4(D3DTS eState);
	_matrix Get_Transform_Matrix(D3DTS eState);

	_float4x4 Get_Transform_Inverse_Float4x4(D3DTS eState) const {
		return m_TransformStateMatrixInverse[static_cast<_uint>(eState)];
	}

	_matrix Get_Transform_Inverse_Matrix(D3DTS eState) const {
		return XMLoadFloat4x4(&m_TransformStateMatrixInverse[static_cast<_uint>(eState)]);
	}

	const _float4* Get_CamPosition();

public:
	void Update();

private:
	_float4x4				m_TransformStateMatrices[ENUM_CLASS(D3DTS::END)] = {};
	_float4x4				m_TransformStateMatrixInverse[ENUM_CLASS(D3DTS::END)] = {};
	_float4					m_vCamPosition = {};


public:
	static CPipeLine* Create();
	virtual void Free() override;

};

NS_END