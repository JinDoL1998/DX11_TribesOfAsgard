#include "Imgui_Manager.h"
#include "GameInstance.h"
#include "Monster.h"
#include "Terrain.h"

#include <fstream>

IMPLEMENT_SINGLETON(CImgui_Manager)

CImgui_Manager::CImgui_Manager()
{
}

HRESULT CImgui_Manager::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;
	m_pGameInstance = CGameInstance::GetInstance();
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);
	Safe_AddRef(m_pGameInstance);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(m_pDevice, m_pContext);

    m_pCameraTransform = reinterpret_cast<CTransform*>(m_pGameInstance->Get_Component(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Layer_Camera"), TEXT("Com_Transform")));

	return S_OK;
}

void CImgui_Manager::Priority_Update(_float fTimeDelta)
{
}

void CImgui_Manager::Update(_float fTimeDelta)
{
	
	if (ImGui::GetIO().WantCaptureMouse)
	{
		return;
	}

    if (m_pGameInstance->Key_Down(DIK_BACK))
    {
        m_isCancel = true;
    }

	if (m_isPlacingMonster && m_pGameInstance->Mouse_Down(MOUSEKEYSTATE::LBUTTON))
	{
        m_pTerrain = dynamic_cast<CTerrain*>(m_pGameInstance->Get_GameObject(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Layer_Terrain")));
        if (m_pTerrain)
        {
            _vector vPickedPoint = XMVectorZero();
            if (m_pTerrain->Pick_Terrain(&vPickedPoint))
            {
                // ��ǥ���� ����ϴ� �ڵ� (������ �߰��� �κ�)
                wchar_t szCoord[256] = L"";
                swprintf_s(szCoord, L"Picked Point: X=%.2f, Y=%.2f, Z=%.2f\n", XMVectorGetX(vPickedPoint), XMVectorGetY(vPickedPoint), XMVectorGetZ(vPickedPoint));
                OutputDebugStringW(szCoord);

                // ���� ���� �ڵ�
                CGameObject::GAMEOBJECT_DESC desc;
                ZeroMemory(&desc, sizeof(CGameObject::GAMEOBJECT_DESC));
                XMStoreFloat4(&desc.vPosition, vPickedPoint);

                if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(
                    ENUM_CLASS(LEVEL::GAMEPLAY),
                    TEXT("Prototype_GameObject_Monster"),
                    ENUM_CLASS(LEVEL::GAMEPLAY),
                    TEXT("Layer_Monster"),
                    &desc)))
                {
                    OutputDebugStringW(L"Failed to add Monster to layer!\n");
                }
            }
        }
	}
    else if (m_isEditingTerrainHeight && m_pGameInstance->Mouse_KeyPressing(MOUSEKEYSTATE::LBUTTON))
    {
        m_pTerrain = dynamic_cast<CTerrain*>(m_pGameInstance->Get_GameObject(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Layer_Terrain")));
        if (m_pTerrain)
        {
            _vector vPickedPoint = XMVectorZero();
            if (m_pTerrain->Pick_Terrain(&vPickedPoint))
            {
                // Terrain�� ���̸� �����ϴ� �Լ� ȣ��
                _float fHeightValue = m_fHeight;
                if (m_isDecreaseHeight) {
                    fHeightValue *= -1.0f; // ���� ���� ����� ��
                }
                m_pTerrain->Change_Height(vPickedPoint, fHeightValue, m_fRadius);
            }
        }
    }

}

void CImgui_Manager::Late_Update(_float fTimeDelta)
{
}

HRESULT CImgui_Manager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
    ImGui::SetNextWindowSize(ImVec2(300.f, 0.f), ImGuiCond_Once);

	_bool bDemo = true;
	ImGui::ShowDemoWindow(&bDemo);

	ImGui::Begin("Map Editor");

    // 1. ����Ʈ�� ���� ���� �޴�
    if (ImGui::Button("INCREASE"))
    {
        m_isEditingTerrainHeight = true;
        m_isIncreaseHeight = true;
        m_isDecreaseHeight = false;
        OutputDebugStringW(L"Terrain Height Increase selected.\n");
    }
    ImGui::SameLine();
    if (ImGui::Button("DECREASE"))
    {
        m_isEditingTerrainHeight = true;
        m_isDecreaseHeight = true;
        m_isIncreaseHeight = false;
        OutputDebugStringW(L"Terrain Height Decrease selected.\n");
    }


    ImGui::InputFloat("Height", &m_fHeight, 0.1f, 100.f);

    // ImGui::SliderFloat�� ����� ���̸� ������ �ݰ��� �����ϴ� �����̴�
    ImGui::InputFloat("Radius", &m_fRadius, 0.01f, 10.f);

    ImGui::Text("Change Terrain Height.");

    ImGui::Spacing(); // �޴� ������ ����
    ImGui::Separator(); // ���м��� �߰�
    ImGui::Spacing();

    ImGui::Text("Registered Models");

    // 2. �� ��ġ �޴�
    _int nSelectedModel = -1; 
    const _char* modelNames[] = { "None", "Player", "Monster", "Tree", "Rock"}; // �ӽ� �� ���

	if (ImGui::ListBox("Models", &nSelectedModel, modelNames, IM_ARRAYSIZE(modelNames)))
	{
        if (nSelectedModel == 1)
        {
            OutputDebugStringW(L"Player selected.\n");
        }
		else if (nSelectedModel == 2) // Monster �ε���
		{
			m_isPlacingMonster = true;
			OutputDebugStringW(L"Monster selected.\n");
		}
		else if ( nSelectedModel == 0)
		{
			m_isPlacingMonster = false; // �ٸ� ���� �����ϸ� ��ġ ��� ����
            m_isIncreaseHeight = false;
            m_isDecreaseHeight = false;
            m_isEditingTerrainHeight = false;
		}
	}

    ImGui::Spacing(); // �޴� ������ ����
    ImGui::Separator(); // ���м��� �߰�
    ImGui::Spacing();

    // 3. Ư����ǥ�� �ڷ���Ʈ
        
    ImGui::SetNextItemWidth(50.f);
    ImGui::InputFloat("X", &m_fX);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    ImGui::InputFloat("Y", &m_fY);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    ImGui::InputFloat("Z", &m_fZ);
    ImGui::SameLine(); 

    if(ImGui::Button("Teleport"))
    {
        m_pCameraTransform->Set_State(STATE::POSITION, XMVectorSet(m_fX, m_fY, m_fZ, 1));
    }


    ImGui::Spacing(); // �޴� ������ ����
    ImGui::Separator(); // ���м��� �߰�
    ImGui::Spacing();

    // 4. ������ ���̺�/�ε�
    ImGui::Text("Save  /  Load");
    if (ImGui::Button("Save"))
    {
        MessageBoxW(g_hWnd, L"���� ����.", L"�˸�", MB_OK);
    }
    ImGui::SameLine();
    if (ImGui::Button("Load"))
    {
        MessageBoxW(g_hWnd, L"�ҷ����� ����.", L"�˸�", MB_OK);
    }

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
           
	return S_OK;
}

void CImgui_Manager::Free()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	Safe_Release(m_pDevice);
	Safe_Release(m_pContext);
	Safe_Release(m_pGameInstance);

}
