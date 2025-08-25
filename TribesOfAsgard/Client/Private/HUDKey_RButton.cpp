#include "HUDKey_RButton.h"
#include "GameInstance.h"

CHUDKey_RButton::CHUDKey_RButton(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: CUIObject { pDevice, pContext }
{
}

CHUDKey_RButton::CHUDKey_RButton(const CHUDKey_RButton& Prototype)
	: CUIObject { Prototype }
{
}

HRESULT CHUDKey_RButton::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CHUDKey_RButton::Initialize(void* pArg)
{
	CUIObject::UIOBJECT_DESC	Desc{};

	Desc.fX = 240.f;
	Desc.fY = 655.f;
	Desc.fSizeX = 30.f;
	Desc.fSizeY = 30.f;

	if (FAILED(__super::Initialize(&Desc)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;

	return S_OK;
}

void CHUDKey_RButton::Priority_Update(_float fTimeDelta)
{
}

void CHUDKey_RButton::Update(_float fTimeDelta)
{
}

void CHUDKey_RButton::Late_Update(_float fTimeDelta)
{
	m_pGameInstance->Add_RenderGroup(RENDER::HUD, this);
}

HRESULT CHUDKey_RButton::Render()
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

HRESULT CHUDKey_RButton::Ready_Components()
{
	/* Com_VIBuffer */
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
		TEXT("Com_VIBuffer"), reinterpret_cast<CComponent**>(&m_pVIBufferCom))))
		return E_FAIL;

	/* Com_Texture */
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_HUDKey_RButton"),
		TEXT("Com_Texture"), reinterpret_cast<CComponent**>(&m_pTextureCom))))
		return E_FAIL;

	/* Com_Shader */
	if (FAILED(__super::Add_Component(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Shader_VtxPosTex"),
		TEXT("Com_Shader"), reinterpret_cast<CComponent**>(&m_pShaderCom))))
		return E_FAIL;

	return S_OK;
}

HRESULT CHUDKey_RButton::Bind_ShaderResources()
{
	if (FAILED(m_pTransformCom->Bind_ShaderResource(m_pShaderCom, "g_WorldMatrix")))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ViewMatrix", &m_ViewMatrix)))
		return E_FAIL;
	if (FAILED(m_pShaderCom->Bind_Matrix("g_ProjMatrix", &m_ProjMatrix)))
		return E_FAIL;
	if (FAILED(m_pTextureCom->Bind_ShaderResource(m_pShaderCom, "g_Texture", 0)))
		return E_FAIL;

	return S_OK;
}

CHUDKey_RButton* CHUDKey_RButton::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CHUDKey_RButton* pInstance = new CHUDKey_RButton(pDevice, pContext);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Failed to Created : pGraphic_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject* CHUDKey_RButton::Clone(void* pArg)
{
	CHUDKey_RButton* pInstance = new CHUDKey_RButton(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Failed to Cloned : CHUDKey_RButton");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CHUDKey_RButton::Free()
{
	__super::Free();

	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTextureCom);
	Safe_Release(m_pShaderCom);
}
