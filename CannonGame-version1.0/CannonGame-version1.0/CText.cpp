#include "stdafx.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "CText.h"

CText::CText(LPDIRECT3DDEVICE9 pD3DDeivce, int width, int height)
{
	D3DXFONT_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.CharSet = HANGUL_CHARSET;
	desc.Quality = DEFAULT_QUALITY;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.Weight = FW_BOLD;
	_tcscpy_s(desc.FaceName, _T("µ¸¿ò"));
	D3DXCreateFontIndirect(pD3DDeivce, &desc, &m_pFont);
}
CText::~CText()
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

void CText::Draw(int x, int y, int width, int height, const TCHAR* lpszText)
{
	RECT rc;
	SetRect(&rc, x, y, x + width, y + height);
	
	m_pFont->DrawTextW(NULL, lpszText, -1, &rc, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
}