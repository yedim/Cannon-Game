#pragma once
class CScreen
{
public:
	static float g_fScreenTop;
	static float g_fScreenBottom;
	static float g_fScreenRight;
	static float g_fScreenLeft;

	explicit CScreen(HWND hWnd);
	virtual ~CScreen();

	LPDIRECT3DDEVICE9 GetDeivce() const { return m_pD3DDevice; }
	operator LPDIRECT3DDEVICE9() const { return m_pD3DDevice; }
	operator const LPDIRECT3DDEVICE9() { return m_pD3DDevice; }

	HRESULT BeginScene() { return m_pD3DDevice->BeginScene(); }
	HRESULT EndScene() { return m_pD3DDevice->EndScene(); }
	
	bool InitScreen(HWND hWnd);
	void ShutdownScreen();

	void BeginRender();
	void EndRender();
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

