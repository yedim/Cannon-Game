#pragma once

class CText
{
public:
	LPD3DXFONT m_pFont;

	explicit CText(LPDIRECT3DDEVICE9 pD3DDeivce, int width,int height);//너비와 높이만
	virtual ~CText();

	void Draw(int x, int y, int width, int height,const TCHAR* lpszText);

};