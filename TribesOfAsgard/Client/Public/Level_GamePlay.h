#pragma once

#include "Client_Defines.h"
#include "Level.h"

NS_BEGIN(Client)

class CLevel_GamePlay final : public CLevel
{
private:
	CLevel_GamePlay(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID);
	virtual ~CLevel_GamePlay() = default;

public:
	virtual HRESULT Initialize() override;
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	HRESULT Ready_Lights();
	HRESULT Ready_Layer_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Camera(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Player(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Monster(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Effect(const _wstring& strLayerTag);

	HRESULT Ready_HUD_PowerScore_BackGround(const _wstring& strLayerTag);		// ÀüÅõ·Â
	HRESULT Ready_HUD_YggDrasilPoint_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Day_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Roll_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_HUD_SkillCounter_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_HUD_SkillCount(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Key_RButton(const _wstring& strLayerTag);
	HRESULT Ready_HUD_PlayerInfo_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Weapon_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Player_CurrentWeapon(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Key_LButton(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Player_Roll(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Key_Space(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Sundial_Border(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Sundial_Runes(const _wstring& strLayerTag);
	HRESULT Ready_HUD_Sundial_Light(const _wstring& strLayerTag);


public:
	static CLevel_GamePlay* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID);
	virtual void Free() override;
};

NS_END