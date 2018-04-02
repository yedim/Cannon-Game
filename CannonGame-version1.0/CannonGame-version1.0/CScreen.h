#pragma once
class CScreen
{
public:
	explicit CScreen(HWND hWnd);
	virtual ~CScreen();

	bool InitScreen(HWND hWnd);
	void ReleaseScreen();

	LPDIRECT3DDEVICE9 GetDevice() const { return m_pD3DDevice; }
	operator LPDIRECT3DDEVICE9() const { return m_pD3DDevice; }
	operator const LPDIRECT3DDEVICE9() { return m_pD3DDevice; }

	HRESULT BeginScene() { return m_pD3DDevice->BeginScene(); }
	HRESULT EndScene() { return m_pD3DDevice->EndScene(); }

	void BeginRender();
	void EndRender();
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

