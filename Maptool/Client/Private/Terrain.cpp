#include "Terrain.h"
#include "GameInstance.h"

CTerrain::CTerrain(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CGameObject{ pDevice, pContext }
{
}

CTerrain::CTerrain(const CTerrain& Prototype)
	: CGameObject{ Prototype }
{
}

_bool CTerrain::Pick_Terrain(_vector* PickingPos)
{
	if (nullptr == m_pVIBufferCom)
		return false;

	// Terrain의 월드 행렬을 로컬 공간 픽킹 레이에 적용
	m_pGameInstance->Transform_MouseRay_ToLocalSpace(m_pTransformCom->Get_WorldMatrixInverse());

	// 지형의 정점 배열을 가져와 삼각형 단위로 픽킹 검사
	_float3* pVertexPositions = m_pVIBufferCom->Get_VertexPosition();	// 이 함수는 추가해야 합니다.
	_uint iNumVerticesX = m_pVIBufferCom->Get_NumVerticesX();			// 이 함수도 추가해야 합니다.
	_uint iNumVerticesZ = m_pVIBufferCom->Get_NumVerticesZ();			// 이 함수도 추가해야 합니다.

	for (_uint i = 0; i < iNumVerticesZ - 1; ++i)
	{
		for (_uint j = 0; j < iNumVerticesX - 1; ++j)
		{
			// 삼각형 정점 1 (삼각형 1)
			_vector vPointA = XMLoadFloat3(&pVertexPositions[i * iNumVerticesX + j]);
			_vector vPointB = XMLoadFloat3(&pVertexPositions[i * iNumVerticesX + j + 1]);
			_vector vPointC = XMLoadFloat3(&pVertexPositions[(i + 1) * iNumVerticesX + j + 1]);

			if (m_pGameInstance->isPicked_InLocalSpace(vPointA, vPointB, vPointC, PickingPos))
			{
				*PickingPos = XMVector3TransformCoord(*PickingPos, m_pTransformCom->Get_WorldMatrix());
				return true;
			}

			// 삼각형 정점 2 (삼각형 2)
			vPointA = XMLoadFloat3(&pVertexPositions[i * iNumVerticesX + j]);
			vPointB = XMLoadFloat3(&pVertexPositions[(i + 1) * iNumVerticesX + j + 1]);
			vPointC = XMLoadFloat3(&pVertexPositions[(i + 1) * iNumVerticesX + j]);

			if (m_pGameInstance->isPicked_InLocalSpace(vPointA, vPointB, vPointC, PickingPos))
			{
				*PickingPos = XMVector3TransformCoord(*PickingPos, m_pTransformCom->Get_WorldMatrix());
				return true;
			}
		}
	}

	return false;
}

HRESULT CTerrain::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CTerrain::Priority_Update(_float fTimeDelta)
{
	int a = 10;
}

void CTerrain::Update(_float fTimeDelta)
{

}

void CTerrain::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER::NONBLEND, this);
}

HRESULT CTerrain::Render()
{
	if (FAILED(Bind_ShaderResources()))
		return E_FAIL;

	if (FAILED(m_pShaderCom->Begin(0)))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Bind_Resources()))
		return E_FAIL;

	if (FAILED(m_pVIBufferCom->Render()))
		return E_FAIL;

	return S_OK;
}

void CTerrain::Change_Height(_vector vPickingPos, _float fHeight, _float fRadius)
{

	if (nullptr == m_pVIBufferCom)
		return;

	_vector vLocalPickedPos = XMVector3TransformCoord(vPickingPos, m_pTransformCom->Get_WorldMatrixInverse());
	m_pVIBufferCom->Change_Height(vLocalPickedPos, fHeight, fRadius);

}

HRESULT CTerrain::Ready_Components()
{
	/* Com_VIBuffer */
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Terrain"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/* Com_Texture */
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Terrain"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	/* Com_Shader */
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Shader_VtxNorTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CTerrain::Bind_ShaderResources()
{
	/*m_pShaderCom->Bind_Matrix("g_WorldMatrix", );*/
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", m_pGameInstance->Get_Transform_Float4x4(D3DTS::VIEW))))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", m_pGameInstance->Get_Transform_Float4x4(D3DTS::PROJ))))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;



	return S_OK;
}

CTerrain* CTerrain::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CTerrain* pInstance = new CTerrain(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : pGraphic_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CTerrain::Clone(void* pArg)
{
	CTerrain* pInstance = new CTerrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CTerrain");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTerrain::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
}
