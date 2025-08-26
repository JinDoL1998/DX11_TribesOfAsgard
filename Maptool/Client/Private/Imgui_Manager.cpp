#include "Imgui_Manager.h"
#include "GameInstance.h"

IMPLEMENT_SINGLETON(CImgui_Manager)

CImgui_Manager::CImgui_Manager()
{
}

HRESULT CImgui_Manager::Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;
	Safe_AddRef(m_pDevice);
	Safe_AddRef(m_pContext);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(g_hWnd);
	ImGui_ImplDX11_Init(m_pDevice, m_pContext);
	return S_OK;
}

void CImgui_Manager::Priority_Update(_float fTimeDelta)
{
}

void CImgui_Manager::Update(_float fTimeDelta)
{
}

void CImgui_Manager::Late_Update(_float fTimeDelta)
{
}

HRESULT CImgui_Manager::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	_bool bDemo = true;
	ImGui::ShowDemoWindow(&bDemo);

	ImGui::Begin("Map Editor");

    // 1. 하이트맵 높이 조절 메뉴
    static _float fHeightValue = 0.f; // 조절할 높이값
    ImGui::SliderFloat("Height", &fHeightValue, -5.f, 5.f);

    // ImGui::SliderFloat를 사용해 높이를 조절할 반경을 설정하는 슬라이더
    static _float fRadius = 1.f; // 높이 조절이 적용될 반경
    ImGui::SliderFloat("Radius", &fRadius, 0.1f, 10.f);

    ImGui::Text("Chage Terrain Height.");

    ImGui::Spacing(); // 메뉴 사이의 간격
    ImGui::Separator(); // 구분선을 추가
    ImGui::Spacing();

    // 2. 모델 배치 메뉴
    ImGui::Text("Registered Models");

    // 등록된 프로토타입 모델 목록을 보여줄 예정입니다.
    _int nSelectedModel = -1; 
    const _char* modelNames[] = { "Player", "Monster", "Tree", "Rock" }; // 임시 모델 목록

    // 목록 상자(List Box)를 만들어 모델들을 나열합니다.
    // ImGui::ListBox를 사용하면 여러 항목 중 하나를 선택하는 메뉴를 쉽게 만들 수 있습니다.
    ImGui::ListBox("Models", &nSelectedModel, modelNames, IM_ARRAYSIZE(modelNames));

    // 선택된 모델이 있을 때만 버튼을 활성화합니다.
    if (nSelectedModel != -1)
    {
        if (ImGui::Button("Place Model"))
        {
            OutputDebugStringW(L"Place Model Button Clicked\n");
        }
    }
    else
    {
        ImGui::Button("Place Model", ImVec2(0, 0)); // 비활성화
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
}
