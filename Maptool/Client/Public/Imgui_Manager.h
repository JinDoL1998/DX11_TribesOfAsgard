#pragma once

#include "Client_Defines.h"
#include "Base.h"

NS_BEGIN(Engine)
class CGameInstance;
class CTransform;
NS_END

NS_BEGIN(Client)
class CImgui_Manager final : public CBase
{
	DECLARE_SINGLETON(CImgui_Manager)

private:
	CImgui_Manager();
	virtual ~CImgui_Manager() = default;

public:
	_bool IsPlacingMonster() { return m_isPlacingMonster; }

public:
	HRESULT Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	void Priority_Update(_float fTimeDelta);
	void Update(_float fTimeDelta);
	void Late_Update(_float fTimeDelta);
	HRESULT Render();

private:
	ID3D11Device* m_pDevice = { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };

	class CTerrain* m_pTerrain = { nullptr };
	class CGameInstance* m_pGameInstance = { nullptr };
	class CTransform* m_pCameraTransform = { nullptr };

	_float m_fHeight = { 0.f };
	_float m_fRadius = { 0.f };

	_float m_fX = { 0.f };
	_float m_fY = { 0.f };
	_float m_fZ = { 0.f };

	_bool m_isPlacingMonster = { false };
	_bool m_isEditingTerrainHeight = { false };
	_bool m_isIncreaseHeight = { false };
	_bool m_isDecreaseHeight = { false };

	vector<class CMonster*> m_Monsters; 
	_bool m_isCancel = { false }; 

public:
	virtual void Free() override;

};

NS_END