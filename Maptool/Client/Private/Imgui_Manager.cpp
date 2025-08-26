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

    // 1. ����Ʈ�� ���� ���� �޴�
    static _float fHeightValue = 0.f; // ������ ���̰�
    ImGui::SliderFloat("Height", &fHeightValue, -5.f, 5.f);

    // ImGui::SliderFloat�� ����� ���̸� ������ �ݰ��� �����ϴ� �����̴�
    static _float fRadius = 1.f; // ���� ������ ����� �ݰ�
    ImGui::SliderFloat("Radius", &fRadius, 0.1f, 10.f);

    ImGui::Text("Chage Terrain Height.");

    ImGui::Spacing(); // �޴� ������ ����
    ImGui::Separator(); // ���м��� �߰�
    ImGui::Spacing();

    // 2. �� ��ġ �޴�
    ImGui::Text("Registered Models");

    // ��ϵ� ������Ÿ�� �� ����� ������ �����Դϴ�.
    _int nSelectedModel = -1; 
    const _char* modelNames[] = { "Player", "Monster", "Tree", "Rock" }; // �ӽ� �� ���

    // ��� ����(List Box)�� ����� �𵨵��� �����մϴ�.
    // ImGui::ListBox�� ����ϸ� ���� �׸� �� �ϳ��� �����ϴ� �޴��� ���� ���� �� �ֽ��ϴ�.
    ImGui::ListBox("Models", &nSelectedModel, modelNames, IM_ARRAYSIZE(modelNames));

    // ���õ� ���� ���� ���� ��ư�� Ȱ��ȭ�մϴ�.
    if (nSelectedModel != -1)
    {
        if (ImGui::Button("Place Model"))
        {
            OutputDebugStringW(L"Place Model Button Clicked\n");
        }
    }
    else
    {
        ImGui::Button("Place Model", ImVec2(0, 0)); // ��Ȱ��ȭ
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
