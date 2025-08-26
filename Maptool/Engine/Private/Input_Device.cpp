
#include "Input_Device.h"

Engine::CInput_Device::CInput_Device(void)
{
	ZeroMemory(m_byKeyState, sizeof(m_byKeyState));
}

_bool CInput_Device::Key_Down(_ubyte eKeyID)
{
	if (m_preKeyState[eKeyID] != m_byKeyState[eKeyID])
	{
		if (m_byKeyState[eKeyID] & 0x80)
			return true;
	}

	return false;
}

_bool CInput_Device::Key_Up(_ubyte eKeyID)
{
	if (m_preKeyState[eKeyID] != m_byKeyState[eKeyID])
	{
		if (m_preKeyState[eKeyID] & 0x80)
			return true;
	}

	return false;
}

_bool CInput_Device::Key_Pressing(_ubyte eKeyID)
{
	if (m_preKeyState[eKeyID] == m_byKeyState[eKeyID])
	{
		if (m_preKeyState[eKeyID] & 0x80)
			return true;
	}

	return false;
}

_bool CInput_Device::Mouse_Down(MOUSEKEYSTATE eMouseKeyID)
{
	if (m_preMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)] != m_tMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)])
	{
		if (m_tMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)] & 0x80)
		{
			return true;
		}
	}

	return false;
}

_bool CInput_Device::Mouse_Up(MOUSEKEYSTATE eMouseKeyID)
{
	if (m_preMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)] != m_tMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)])
	{
		if (m_preMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)] & 0x80)
		{
			return true;
		}
	}

	return false;
}

_bool CInput_Device::Mouse_Pressing(MOUSEKEYSTATE eMouseKeyID)
{
	if (m_preMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)] == m_tMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)])
	{
		if (m_tMouseState.rgbButtons[ENUM_CLASS(eMouseKeyID)] & 0x80)
			return true;
	}

	return false;
}

HRESULT Engine::CInput_Device::Initialize(HINSTANCE hInst, HWND hWnd)
{

	// DInput �İ�ü�� �����ϴ� �Լ�
	if (FAILED(DirectInput8Create(hInst,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pInputSDK,
		NULL)))
		return E_FAIL;

	// Ű���� ��ü ����
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysKeyboard, &m_pKeyBoard, nullptr)))
		return E_FAIL;

	// ������ Ű���� ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	// ��ġ�� ���� �������� �������ִ� �Լ�, (Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�)
	m_pKeyBoard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pKeyBoard->Acquire();


	// ���콺 ��ü ����
	if (FAILED(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
		return E_FAIL;

	// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	m_pMouse->SetDataFormat(&c_dfDIMouse);

	// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	m_pMouse->Acquire();

	//// ���̽�ƽ ��ü ����
	//if (FAILED(m_pInputSDK->CreateDevice(GUID_SysMouse, &m_pMouse, nullptr)))
	//	return E_FAIL;

	//// ������ ���콺 ��ü�� ���� ������ �� ��ü���� �����ϴ� �Լ�
	//m_pMouse->SetDataFormat(&c_dfDIMouse);

	//// ��ġ�� ���� �������� �������ִ� �Լ�, Ŭ���̾�Ʈ�� ���ִ� ���¿��� Ű �Է��� ������ ������ �����ϴ� �Լ�
	//m_pMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	//// ��ġ�� ���� access ������ �޾ƿ��� �Լ�
	//m_pMouse->Acquire();


	return S_OK;
}

void Engine::CInput_Device::Update(void)
{
	memcpy(&m_preKeyState, &m_byKeyState, sizeof(_char) * 256);
	m_pKeyBoard->GetDeviceState(256, m_byKeyState);
	memcpy(&m_preMouseState, &m_tMouseState, sizeof(DIMOUSESTATE));
	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_tMouseState);
}

CInput_Device* CInput_Device::Create(HINSTANCE hInstance, HWND hWnd)
{
	CInput_Device* pInstance = new CInput_Device();

	if (FAILED(pInstance->Initialize(hInstance, hWnd)))
	{
		MSG_BOX("Failed to Created : CInput_Device");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void Engine::CInput_Device::Free(void)
{
	Safe_Release(m_pKeyBoard);
	Safe_Release(m_pMouse);
	Safe_Release(m_pInputSDK);
}

