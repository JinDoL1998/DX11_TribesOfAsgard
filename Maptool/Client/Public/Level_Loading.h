#pragma once

#include "Client_Defines.h"
#include "Level.h"


/* 2. �ڿ��� �ε��ϴ� ����, ȭ�鿡 �ε� ���¸� ǥ�����ش�. */

NS_BEGIN(Client)

class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID);
	virtual ~CLevel_Loading() = default;

public:
	virtual HRESULT Initialize(LEVEL eNextLevelID);
	virtual void Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	LEVEL				m_eNextLevelID = { LEVEL::END };
	class CLoader*		m_pLoader = { nullptr };

private:
	HRESULT Ready_Layer_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Circle(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Loading_Bar_BackGround(const _wstring& strLayerTag);
	HRESULT Ready_Layer_Loading_Bar(const _wstring& strLayerTag);


public:
	static CLevel_Loading* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, LEVEL eLevelID, LEVEL eNextLevelID);
	virtual void Free() override;
};

NS_END