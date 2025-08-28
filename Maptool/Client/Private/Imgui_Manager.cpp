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
    m_pTerrain = dynamic_cast<CTerrain*>(m_pGameInstance->Get_GameObject(ENUM_CLASS(LEVEL::GAMEPLAY), TEXT("Layer_Terrain")));

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

	if (m_pGameInstance->Mouse_Down(MOUSEKEYSTATE::LBUTTON))
	{
        if (m_pTerrain)
        {
            if (m_eCurrentAddType == ADD_TYPE::END)
                return;

            _vector vPickedPoint = XMVectorZero();
            if (m_pTerrain->Pick_Terrain(&vPickedPoint))
            {
                // 좌표값을 출력하는 코드 (이전에 추가한 부분)
                wchar_t szCoord[256] = L"";
                swprintf_s(szCoord, L"Picked Point: X=%.2f, Y=%.2f, Z=%.2f\n", XMVectorGetX(vPickedPoint), XMVectorGetY(vPickedPoint), XMVectorGetZ(vPickedPoint));
                OutputDebugStringW(szCoord);

                // 몬스터 생성 코드
                CGameObject::GAMEOBJECT_DESC desc;
                ZeroMemory(&desc, sizeof(CGameObject::GAMEOBJECT_DESC));
                XMStoreFloat4(&desc.vPosition, vPickedPoint);

                if(m_eCurrentAddType == ADD_TYPE::MONSTER)
                {
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

                else if (m_eCurrentAddType == ADD_TYPE::YGGDRASIL)
                {
                    if (FAILED(m_pGameInstance->Add_GameObject_ToLayer(
                        ENUM_CLASS(LEVEL::GAMEPLAY),
                        TEXT("Prototype_GameObject_YggDrasil"),
                        ENUM_CLASS(LEVEL::GAMEPLAY),
                        TEXT("Layer_YggDrasil"),
                        &desc)))
                    {
                        OutputDebugStringW(L"Failed to add YggDrasil to layer!\n");
                    }
                }

                _float fHeightValue = m_fHeight;
                if (m_eCurrentAddType == ADD_TYPE::TERRAIN_DECREASE) {
                    if (fHeightValue > 0)
                        fHeightValue *= -1.0f;
                }

                else if (m_eCurrentAddType == ADD_TYPE::TERRAIN_INCREASE) {
                    if (fHeightValue < 0)
                        fHeightValue;
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

    // 1. 하이트맵 높이 조절 메뉴
    if (ImGui::Button("INCREASE"))
    {
        m_eCurrentAddType = ADD_TYPE::TERRAIN_INCREASE;
    }
    ImGui::SameLine();
    if (ImGui::Button("DECREASE"))
    {
        m_eCurrentAddType = ADD_TYPE::TERRAIN_DECREASE;
    }


    ImGui::InputFloat("Height", &m_fHeight, 0.1f, 100.f);

    ImGui::InputFloat("Radius", &m_fRadius, 0.01f, 10.f);

    ImGui::Text("Change Terrain Height.");

    ImGui::Spacing(); // 메뉴 사이의 간격
    ImGui::Separator(); // 구분선을 추가
    ImGui::Spacing();

    ImGui::Text("Registered Models");

    // 2. 모델 배치 / 삭제메뉴
    _int nSelectedModel = -1; 
    const _char* modelNames[] = { "None", "Player", "Monster", "YggDrasil", "Tree", "Rock"}; // 임시 모델 목록

	if (ImGui::ListBox("Models", &nSelectedModel, modelNames, IM_ARRAYSIZE(modelNames)))
	{
        if (nSelectedModel == 1)
        {
            m_eCurrentAddType = ADD_TYPE::PLAYER;
            m_CurrentLayerName = TEXT("Layer_Player");
        }
		else if (nSelectedModel == 2) // Monster
		{
            m_eCurrentAddType = ADD_TYPE::MONSTER;
            m_CurrentLayerName = TEXT("Layer_Monster");
		}
        else if (nSelectedModel == 3) // YggDrasil
        {
            m_eCurrentAddType = ADD_TYPE::YGGDRASIL;
            m_CurrentLayerName = TEXT("Layer_YggDrasil");
        }
		else if ( nSelectedModel == 0)
		{
            m_eCurrentAddType = ADD_TYPE::END;
		}
	}

    if (ImGui::Button("Delete All"))
    {
        if (m_eCurrentAddType == ADD_TYPE::END) return E_FAIL;

        m_pGameInstance->Delete_Object_All(ENUM_CLASS(LEVEL::GAMEPLAY), m_CurrentLayerName);
    }
    ImGui::SameLine();
    if (ImGui::Button("Delete Latest"))
    {
        if (m_eCurrentAddType == ADD_TYPE::END) return E_FAIL;

        m_pGameInstance->Delete_Object_Latest(ENUM_CLASS(LEVEL::GAMEPLAY), m_CurrentLayerName);
    }

    ImGui::Spacing(); // 메뉴 사이의 간격
    ImGui::Separator(); // 구분선을 추가
    ImGui::Spacing();

    // 3. 특정좌표로 텔레포트
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

    // 오브젝트 스케일링, 회전하기
    ImGui::Spacing(); // 메뉴 사이의 간격
    ImGui::Separator(); // 구분선을 추가
    ImGui::Spacing();

    ImGui::Text("Object Rotation");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100.f); // 슬라이더 너비 조절
    if (ImGui::SliderFloat("##RotX_Slider", &m_fRotX, -180.f, 180.f))
    {
        Update_Rotation();
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f); // 입력창 너비 조절
    if (ImGui::InputFloat("##RotX_Input", &m_fRotX))
    {
        Update_Rotation();
    }

    // Y축 회전
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::SliderFloat("##RotY_Slider", &m_fRotY, -180.f, 180.f))
    {
        Update_Rotation();
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    if (ImGui::InputFloat("##RotY_Input", &m_fRotY))
    {
        Update_Rotation();
    }

    // Z축 회전
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100.f);
    if (ImGui::SliderFloat("##RotZ_Slider", &m_fRotZ, -180.f, 180.f))
    {
        Update_Rotation();
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    if (ImGui::InputFloat("##RotZ_Input", &m_fRotZ))
    {
        Update_Rotation();
    }

    ImGui::Spacing(); // 메뉴 사이의 간격
    ImGui::Separator(); // 구분선을 추가
    ImGui::Spacing();

    ImGui::Text("Object Scale");
    ImGui::Text("X");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    ImGui::InputFloat("##ScaleX", &m_fScaleX);
    ImGui::SameLine();
    ImGui::Text("Y");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    ImGui::InputFloat("##ScaleY", &m_fScaleY);
    ImGui::SameLine();
    ImGui::Text("Z");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.f);
    ImGui::InputFloat("##ScaleZ", &m_fScaleZ);

    if (ImGui::Button("Scale"))
    {
        if (m_eCurrentAddType == ADD_TYPE::END) return E_FAIL;

        m_pObjects = m_pGameInstance->Get_GameObjectList(ENUM_CLASS(LEVEL::GAMEPLAY), m_CurrentLayerName);

        if (m_pObjects)
        {
            for (auto pObject : *m_pObjects)
            {
                CTransform* pTransform = dynamic_cast<CTransform*>(pObject->Find_Component(TEXT("Com_Transform")));
                if (pTransform)
                {
                    pTransform->Set_Scale(m_fScaleX, m_fScaleY, m_fScaleZ);
                }
            }
        }
    }

    

    ImGui::Spacing(); // 메뉴 사이의 간격
    ImGui::Separator(); // 구분선을 추가
    ImGui::Spacing();

    // 에디터 세이브/로드
    ImGui::Text("Save  /  Load");
    if (ImGui::Button("Save"))
    {
        MessageBoxW(g_hWnd, L"저장 성공.", L"알림", MB_OK);
    }
    ImGui::SameLine();
    if (ImGui::Button("Load"))
    {
        MessageBoxW(g_hWnd, L"불러오기 성공.", L"알림", MB_OK);
    }

	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
           
	return S_OK;
}

void CImgui_Manager::Update_Rotation()
{
    if (m_eCurrentAddType == ADD_TYPE ::END) return;

    m_pObjects = m_pGameInstance->Get_GameObjectList(ENUM_CLASS(LEVEL::GAMEPLAY), m_CurrentLayerName);

    if (m_pObjects)
    {
        for (auto pObject : *m_pObjects)
        {
            CTransform* pTransform = dynamic_cast<CTransform*>(pObject->Find_Component(TEXT("Com_Transform")));
            if (pTransform)
            {
                pTransform->Rotation(XMConvertToRadians(m_fRotX), XMConvertToRadians(m_fRotY), XMConvertToRadians(m_fRotZ));
            }
        }
    }
}

HRESULT CImgui_Manager::Save_Monsters()
{
    return S_OK;
}

HRESULT CImgui_Manager::Load_Monsters()
{
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
