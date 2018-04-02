#include "stdafx.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"


CSprite::CSprite(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 texture
	, float cx, float cy)
	: m_pSpr(NULL)
	, m_Center(cx,cy,0.f)
	,m_Pos(0.f,0.f,0.f)
	,m_pD3DDevice(pD3DDevice)
	,m_pTexture(texture)
{
	InitSprite(pD3DDevice);
}

CSprite::~CSprite()
{
	ReleaseSprite();
}
bool CSprite::InitSprite(LPDIRECT3DDEVICE9 pD3DDevice)
{
	auto hr = D3DXCreateSprite(pD3DDevice, &m_pSpr);
	if (FAILED(hr))
		return false;

	return true;
}

void CSprite::Draw()
{
	m_pSpr->Begin(D3DXSPRITE_ALPHABLEND);
	m_pSpr->Draw(m_pTexture, NULL, &m_Center, &m_Pos, D3DCOLOR_XRGB(255, 255, 255));
	m_pSpr->End();
}
void CSprite::ReleaseSprite()
{
	if (m_pSpr != NULL)
	{
		m_pSpr->Release();
		m_pSpr = NULL;
	}
}
