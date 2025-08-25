#include "Level_Loading.h"

#include "Loader.h"
#include "GameInstance.h"

#include "Level_Logo.h"
#include "Level_GamePlay.h"

CLevel_Loading::CLevel_Loading(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID)
	: CLevel { pDevice, pContext, ENUM_CLASS(eLevelID)}
{

}

HRESULT CLevel_Loading::Initialize(LEVEL eNextLevelID)
{
	m_eNextLevelID = eNextLevelID;

	/* ���� ������ ���� �ڿ��� �ε��Ͽ� �غ��صд�. */
	m_pLoader = CLoader::Create(m_pDevice, m_pContext, eNextLevelID);
	if (nullptr == m_pLoader)
		return E_FAIL;

	/* �� ������ �����ϱ����� ��ü�� �����. */
	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_Loading_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Circle(TEXT("Layer_Loading_Circle"))))
		return E_FAIL;
		
	if (FAILED(Ready_Layer_Loading_Bar_BackGround(TEXT("Layer_Loading_Bar_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_Loading_Bar(TEXT("Layer_Loading_Loading_Bar"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_Loading::Update(_float fTimeDelta)
{
	if (true == m_pLoader->isFinished())
	{
		CLevel* pNewLevel = { nullptr };

		switch (m_eNextLevelID)
		{
		case LEVEL::LOGO:
			pNewLevel = CLevel_Logo::Create(m_pDevice, m_pContext, m_eNextLevelID);
			break;
		case LEVEL::GAMEPLAY:
			pNewLevel = CLevel_GamePlay::Create(m_pDevice, m_pContext, m_eNextLevelID);
			break;
		}

		if (FAILED(m_pGameInstance->Change_Level(pNewLevel)))
			return;		
	}	
}

HRESULT CLevel_Loading::Render()
{
	m_pLoader->Output();

	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_BackGround(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_BackGround"),
		ENUM_CLASS(LEVEL::LOADING), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_Circle(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_Circle"),
		ENUM_CLASS(LEVEL::LOADING), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_Loading_Bar_BackGround(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_Bar_BackGround"),
		ENUM_CLASS(LEVEL::LOADING), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_Loading_Bar(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_Bar"),
		ENUM_CLASS(LEVEL::LOADING), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

CLevel_Loading* CLevel_Loading::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID, LEVEL eNextLevelID)
{
	CLevel_Loading* pInstance = new CLevel_Loading(pDevice, pContext, eLevelID);

	if (FAILED(pInstance->Initialize(eNextLevelID)))
	{
		MSG_BOX("Failed to Created : CLevel_Loading");
		Safe_Release(pInstance);
	}

	return pInstance;
}



void CLevel_Loading::Free()
{
	__super::Free();

	Safe_Release(m_pLoader);


}
