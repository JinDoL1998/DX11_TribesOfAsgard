#pragma once

#include "Client_Defines.h"
#include "GameObject.h"

NS_BEGIN(Engine)
NS_END

NS_BEGIN(Client)
class CImgui_Manager final : public CGameObject
{
private:
	CImgui_Manager(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	CImgui_Manager(const CImgui_Manager& Prototype);
	virtual ~CImgui_Manager() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg);
	virtual void Priority_Update(_float fTimeDelta) override;
	virtual void Update(_float fTimeDelta) override;
	virtual void Late_Update(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	static CImgui_Manager* Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

};

NS_END