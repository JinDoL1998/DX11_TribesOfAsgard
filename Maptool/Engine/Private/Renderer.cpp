#include "Renderer.h"

#include "GameObject.h"


CRenderer::CRenderer(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
{
    Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
}

HRESULT CRenderer::Initialize()
{
    return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDER eRenderGroup, CGameObject* pRenderObject)
{
	if (nullptr == pRenderObject)
		return E_FAIL;

	m_RenderObjects[ENUM_CLASS(eRenderGroup)].push_back(pRenderObject);

	Safe_AddRef(pRenderObject);

	return S_OK;
}

void CRenderer::Render()
{
	Render_Priority();
	Render_NonBlend();
	Render_Blend();
	Render_HUD_Back();
	Render_HUD_Mid();
	Render_HUD();
	Render_UI();
}

void CRenderer::Render_Priority()
{
	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::PRIORITY)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::PRIORITY)].clear();
}

void CRenderer::Render_NonBlend()
{
	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::NONBLEND)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::NONBLEND)].clear();
}




void CRenderer::Render_Blend()
{


	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::BLEND)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::BLEND)].clear();
}

void CRenderer::Render_HUD_Back()
{
	// ±íÀÌ ½ºÅÙ½Ç »óÅÂ¸¦ Off·Î ¼³Á¤
	ID3D11DepthStencilState* pOldState = nullptr;
	UINT                    iOldStencilRef = 0;

	m_pContext->OMGetDepthStencilState(&pOldState, &iOldStencilRef);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = FALSE;  // ±íÀÌ Å×½ºÆ® ²û
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.StencilEnable = FALSE;

	ID3D11DepthStencilState* pDepthState = nullptr;
	m_pDevice->CreateDepthStencilState(&dsDesc, &pDepthState);

	m_pContext->OMSetDepthStencilState(pDepthState, 0);

	// ½ÇÁ¦ ·»´õ¸µ
	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::HUD_BACK)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::HUD_BACK)].clear();

	m_pContext->OMSetDepthStencilState(pOldState, iOldStencilRef);

	Safe_Release(pDepthState);
	Safe_Release(pOldState);
}

void CRenderer::Render_HUD_Mid()
{// ±íÀÌ ½ºÅÙ½Ç »óÅÂ¸¦ Off·Î ¼³Á¤
	ID3D11DepthStencilState* pOldState = nullptr;
	UINT                    iOldStencilRef = 0;

	m_pContext->OMGetDepthStencilState(&pOldState, &iOldStencilRef);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = FALSE;  // ±íÀÌ Å×½ºÆ® ²û
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.StencilEnable = FALSE;

	ID3D11DepthStencilState* pDepthState = nullptr;
	m_pDevice->CreateDepthStencilState(&dsDesc, &pDepthState);

	m_pContext->OMSetDepthStencilState(pDepthState, 0);

	// ½ÇÁ¦ ·»´õ¸µ
	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::HUD_MID)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::HUD_MID)].clear();

	m_pContext->OMSetDepthStencilState(pOldState, iOldStencilRef);

	Safe_Release(pDepthState);
	Safe_Release(pOldState);
}

void CRenderer::Render_HUD()
{
	// ±íÀÌ ½ºÅÙ½Ç »óÅÂ¸¦ Off·Î ¼³Á¤
	ID3D11DepthStencilState* pOldState = nullptr;
	UINT                    iOldStencilRef = 0;

	m_pContext->OMGetDepthStencilState(&pOldState, &iOldStencilRef);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = FALSE;  // ±íÀÌ Å×½ºÆ® ²û
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.StencilEnable = FALSE;

	ID3D11DepthStencilState* pDepthState = nullptr;
	m_pDevice->CreateDepthStencilState(&dsDesc, &pDepthState);

	m_pContext->OMSetDepthStencilState(pDepthState, 0);

	// ½ÇÁ¦ ·»´õ¸µ
	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::HUD)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::HUD)].clear();

	m_pContext->OMSetDepthStencilState(pOldState, iOldStencilRef);

	Safe_Release(pDepthState);
	Safe_Release(pOldState);
}

void CRenderer::Render_UI()
{
	// ±íÀÌ ½ºÅÙ½Ç »óÅÂ¸¦ Off·Î ¼³Á¤
	ID3D11DepthStencilState* pOldState = nullptr;
	UINT                    iOldStencilRef = 0;

	m_pContext->OMGetDepthStencilState(&pOldState, &iOldStencilRef);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = FALSE;  // ±íÀÌ Å×½ºÆ® ²û
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.StencilEnable = FALSE;

	ID3D11DepthStencilState* pDepthState = nullptr;
	m_pDevice->CreateDepthStencilState(&dsDesc, &pDepthState);

	m_pContext->OMSetDepthStencilState(pDepthState, 0);

	// ½ÇÁ¦ ·»´õ¸µ
	for (auto& pRenderObject : m_RenderObjects[ENUM_CLASS(RENDER::UI)])
	{
		if (nullptr != pRenderObject)
			pRenderObject->Render();

		Safe_Release(pRenderObject);
	}

	m_RenderObjects[ENUM_CLASS(RENDER::UI)].clear();

	m_pContext->OMSetDepthStencilState(pOldState, iOldStencilRef);

	Safe_Release(pDepthState);
	Safe_Release(pOldState);
}

CRenderer* CRenderer::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	CRenderer* pInstance = new CRenderer(pDevice, pContext);

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CRenderer");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRenderer::Free()
{
    __super::Free();

	for (auto& RenderObjects : m_RenderObjects)
	{
		for (auto& pRenderObject : RenderObjects)
			Safe_Release(pRenderObject);
		RenderObjects.clear();
	}

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);


}
