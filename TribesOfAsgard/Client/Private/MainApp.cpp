#include "MainApp.h"

#include "GameInstance.h"
#include "Level_Loading.h"
#include "Camera_Free.h"
#include "Loading_BackGround.h"
#include "Loading_Circle.h"
#include "Loading_Bar_BackGround.h"
#include "Loading_Bar.h"


Client::CMainApp::CMainApp()	
	: m_pGameInstance { CGameInstance::GetInstance() }
{
	

	Safe_AddRef(m_pGameInstance);
}

HRESULT Client::CMainApp::Initialize()
{
	ENGINE_DESC				EngineDesc{};
	EngineDesc.hInstance = g_hInstance;
	EngineDesc.hWnd = g_hWnd;
	EngineDesc.eWindowMode = WINMODE::WIN;
	EngineDesc.iWinSizeX = g_iWinSizeX;
	EngineDesc.iWinSizeY = g_iWinSizeY;
	EngineDesc.iNumLevels = ENUM_CLASS(LEVEL::END);

	if (FAILED(m_pGameInstance->Initialize_Engine(EngineDesc, &m_pDevice, &m_pContext)))
		return E_FAIL;

	if (FAILED(Ready_Default_Setting()))
		return E_FAIL;

	if (FAILED(Ready_Prototypes()))
		return E_FAIL;

	if (FAILED(Start_Level(LEVEL::LOGO)))
		return E_FAIL;	

	return S_OK;
}

void Client::CMainApp::Update(_float fTimeDelta)
{
	m_pGameInstance->Update_Engine(fTimeDelta);
}

HRESULT Client::CMainApp::Render()
{
	_float4			vClearColor = _float4(0.f, 0.f, 1.f, 1.f);

	m_pGameInstance->Render_Begin(&vClearColor);

	m_pGameInstance->Draw();

	m_pGameInstance->Render_End();

	return S_OK;
}

HRESULT CMainApp::Ready_Default_Setting()
{
	

	return S_OK;
}

HRESULT CMainApp::Start_Level(LEVEL eLevelID)
{
	if (FAILED(m_pGameInstance->Change_Level(CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL::LOADING, eLevelID))))
		return E_FAIL;
	
	return S_OK;
}

HRESULT CMainApp::Ready_Prototypes()
{
	///* For.Prototype_Component_Transform*/
	//if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Transform"),
	//	CTransform::Create(m_pGraphic_Device))))
	//	return E_FAIL;

	/* For.Prototype_Component_VIBuffer_Rect */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Shader_VtxPosTex */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Shader_VtxPosTex"),
		CShader::Create(m_pDevice, m_pContext, TEXT("../Bin/ShaderFiles/Shader_VtxPosTex.hlsl"), VTXPOSTEX::Elements, VTXPOSTEX::iNumElements))))
		return E_FAIL;

	/* For.Prototype_GameObject_Camera_Free */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Camera_Free"),
		CCamera_Free::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Loading_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Texture_Loading_BackGround"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/UI/Loading/UI_LoadingScreen_Bg.png"), 1))))
		return E_FAIL;

	/* For.Prototype_GameObject_Loading_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_BackGround"),
		CLoading_BackGround::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Loading_Circle */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Texture_Loading_Circle"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/UI/Loading/UI_LoadingScreenCircle_0.png"), 1))))
		return E_FAIL;

	/* For.Prototype_GameObject_Loading_Circle */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_Circle"),
		CLoading_Circle::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Loading_Bar_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Texture_Loading_Bar_BackGround"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/UI/Loading/UI_LoadingBarBg_001.png"), 1))))
		return E_FAIL;

	/* For.Prototype_GameObject_Loading_Bar_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_Bar_BackGround"),
		CLoading_Bar_BackGround::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	/* For.Prototype_Component_Texture_Loading_Bar_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_Component_Texture_Loading_Bar"),
		CTexture::Create(m_pDevice, m_pContext, TEXT("../Bin/Resources/UI/Loading/UI_LoadingBar_001.png"), 1))))
		return E_FAIL;

	/* For.Prototype_GameObject_Loading_Bar_BackGround */
	if (FAILED(m_pGameInstance->Add_Prototype(ENUM_CLASS(LEVEL::STATIC), TEXT("Prototype_GameObject_Loading_Bar"),
		CLoading_Bar::Create(m_pDevice, m_pContext))))
		return E_FAIL;

	return S_OK;
}

CMainApp* Client::CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp();

	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void Client::CMainApp::Free()
{
	__super::Free();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);

	m_pGameInstance->Release_Engine();

	Safe_Release(m_pGameInstance);	
}
