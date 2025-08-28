#pragma once

#include "Client_Defines.h"
#include "Base.h"

NS_BEGIN(Engine)
class CGameInstance;
class CTransform;
class CGameObject;
NS_END

NS_BEGIN(Client)
class CImgui_Manager final : public CBase
{
	DECLARE_SINGLETON(CImgui_Manager)

private:
	CImgui_Manager();
	virtual ~CImgui_Manager() = default;

public:
	HRESULT Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	void Priority_Update(_float fTimeDelta);
	void Update(_float fTimeDelta);
	void Late_Update(_float fTimeDelta);
	HRESULT Render();

	void Update_Rotation();
	HRESULT Save_Monsters();
	HRESULT Load_Monsters();

private:
	ID3D11Device* m_pDevice = { nullptr };
	ID3D11DeviceContext* m_pContext = { nullptr };

	class CTerrain* m_pTerrain = { nullptr };
	class CGameInstance* m_pGameInstance = { nullptr };
	class CTransform* m_pCameraTransform = { nullptr };
	class CTransform* m_pTransform = { nullptr };

	ADD_TYPE m_eCurrentAddType = { ADD_TYPE::END };
	
	// ���� ����, �ݰ�
	_float m_fHeight = { 0.f };
	_float m_fRadius = { 0.f };

	// ī�޶� �̵��� ��ǥ
	_float m_fX = { 0.f };
	_float m_fY = { 0.f };
	_float m_fZ = { 0.f };

	// ������Ʈ ȸ����
	_float m_fRotX = { 0.f };
	_float m_fRotY = { 0.f };
	_float m_fRotZ = { 0.f };

	// ������Ʈ �����Ͽ�
	_float m_fScaleX = { 0.f };
	_float m_fScaleY = { 0.f };
	_float m_fScaleZ = { 0.f };

	// ������Ʈ Ŭ������

	vector<class CMonster*> m_Monsters; 
	list<class CGameObject*>* m_pObjects;
	_bool m_isCancel = { false }; 

	const _tchar* m_CurrentLayerName = {};

public:
	virtual void Free() override;

};

NS_END