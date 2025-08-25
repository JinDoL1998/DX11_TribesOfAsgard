#include "Level_GamePlay.h"
#include "GameInstance.h"
#include "UIObject.h"
#include "Camera_Free.h"

CLevel_GamePlay::CLevel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID)
	: CLevel { pDevice, pContext, ENUM_CLASS(eLevelID)}
	
{

}

HRESULT CLevel_GamePlay::Initialize()
{
	/*if (FAILED(Ready_Lights()))
		return E_FAIL;
		*/
	if (FAILED(Ready_Layer_Camera(TEXT("Layer_Camera"))))
		return E_FAIL;

	if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
		return E_FAIL;
	//if (FAILED(Ready_Layer_Player(TEXT("Layer_Player"))))
	//	return E_FAIL;

	if (FAILED(Ready_Layer_Monster(TEXT("Layer_Monster"))))
		return E_FAIL;

	//if (FAILED(Ready_Layer_Effect(TEXT("Layer_Effect"))))
	//	return E_FAIL;

	if (FAILED(Ready_HUD_PowerScore_BackGround(TEXT("Layer_HUD_PowerScore_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_YggDrasilPoint_BackGround(TEXT("Layer_HUD_YggDrasilPoint_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Day_BackGround(TEXT("Layer_HUD_Day_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Roll_BackGround(TEXT("Layer_HUD_Roll_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_SkillCounter_BackGround(TEXT("Layer_HUD_SkillCounter_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_SkillCount(TEXT("Layer_HUD_SkillCount"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Key_RButton(TEXT("Layer_HUD_Key_RButton"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_PlayerInfo_BackGround(TEXT("Layer_HUD_PlayerInfo_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Weapon_BackGround(TEXT("Layer_HUD_Weapon_BackGround"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Player_CurrentWeapon(TEXT("Layer_HUD_Weapon"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Key_LButton(TEXT("Layer_HUD_Key_LButton"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Player_Roll(TEXT("Layer_HUD_Roll"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Key_Space(TEXT("Layer_HUD_Key_Space"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Sundial_Border(TEXT("Layer_HUD_Sundial_Border"))))
		return E_FAIL;

	if (FAILED(Ready_HUD_Sundial_Runes(TEXT("Layer_HUD_Sundial_Runes"))))
		return E_FAIL;
	
	if (FAILED(Ready_HUD_Sundial_Light(TEXT("Layer_HUD_Sundial_Light"))))
		return E_FAIL;

	return S_OK;
}

void CLevel_GamePlay::Update(_float fTimeDelta)
{
}

HRESULT CLevel_GamePlay::Render()
{
	SetWindowText(g_hWnd, TEXT("게임플레이레벨이빈다"));
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Lights()
{

	
	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_BackGround(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Terrain"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Camera(const _wstring& strLayerTag)
{
	CCamera_Free::CAMERA_FREE_DESC			CameraDesc{};
	CameraDesc.fFovy = XMConvertToRadians(60.0f);
	CameraDesc.fNear = 0.1f;
	CameraDesc.fFar = 500.f;
	CameraDesc.vEye = _float3(0.f, 10.f, -10.f);
	CameraDesc.vAt = _float3(0.f, 0.f, 0.f);
	CameraDesc.fSpeedPerSec = 20.f;
	CameraDesc.fRotationPerSec = XMConvertToRadians(90.0f);
	CameraDesc.fMouseSensor = 0.2f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Camera_Free"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &CameraDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Player(const _wstring& strLayerTag)
{
	/*for (size_t i = 0; i < 1; i++)
	{
		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Player"),
			ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
			return E_FAIL;
	}*/
	

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Monster(const _wstring& strLayerTag)
{
	for (size_t i = 0; i < 1; i++)
	{
		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Monster"),
			ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
			return E_FAIL;
	}


	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_Layer_Effect(const _wstring& strLayerTag)
{
	/*for (size_t i = 0; i < 50; i++)
	{
		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Effect"),
			ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
			return E_FAIL;
	}*/

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_PowerScore_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 250.f;
	UIDesc.fY = 80.f;
	UIDesc.fSizeX = 200.f;
	UIDesc.fSizeY = 80.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_YggDrasilPoint_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 930.f;
	UIDesc.fY = 160.f;
	UIDesc.fSizeX = 250.f;
	UIDesc.fSizeY = 50.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Day_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 930.f;
	UIDesc.fY = 90.f;
	UIDesc.fSizeX = 250.f;
	UIDesc.fSizeY = 80.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Roll_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 300.f;
	UIDesc.fY = 630.f;
	UIDesc.fSizeX = 60.f;
	UIDesc.fSizeY = 60.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_SkillCounter_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 180.f;
	UIDesc.fY = 630.f;
	UIDesc.fSizeX = 150.f;
	UIDesc.fSizeY = 60.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_SkillCount(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	for (size_t i = 0; i < 3; i++)
	{
		UIDesc.fX = 135.f + (i * 46.f);
		UIDesc.fY = 630.f;
		UIDesc.fSizeX = 50.f;
		UIDesc.fSizeY = 50.f;

		if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_SkillCount"),
			ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
			return E_FAIL;
	}

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Key_RButton(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Key_RButton"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Weapon_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 60.f;
	UIDesc.fY = 630.f;
	UIDesc.fSizeX = 60.f;
	UIDesc.fSizeY = 60.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_PlayerInfo_BackGround(const _wstring& strLayerTag)
{
	CUIObject::UIOBJECT_DESC			UIDesc{};

	UIDesc.fX = 680.f;
	UIDesc.fY = 630.f;
	UIDesc.fSizeX = 500.f;
	UIDesc.fSizeY = 60.f;

	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Weapon_BackGround"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag, &UIDesc)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Player_CurrentWeapon(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_CurrentWeapon"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Key_LButton(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Key_LButton"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Player_Roll(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Roll"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Key_Space(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Key_Space"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Sundial_Border(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Sundial_Border"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Sundial_Runes(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Sundial_Runes"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLevel_GamePlay::Ready_HUD_Sundial_Light(const _wstring& strLayerTag)
{
	if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_HUD_Sundial_Light"),
		ENUM_CLASS(LEVEL::GAMEPLAY), strLayerTag)))
		return E_FAIL;

	return S_OK;
}


CLevel_GamePlay* CLevel_GamePlay::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID)
{
	CLevel_GamePlay* pInstance = new CLevel_GamePlay(pDevice, pContext, eLevelID);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CLevel_GamePlay");
		Safe_Release(pInstance);
	}

	return pInstance;
}





void CLevel_GamePlay::Free()
{
	__super::Free();


}
