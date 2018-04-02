#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "CSprite.h"
#include "CEffect.h"


CEffect::CEffect(LPDIRECT3DDEVICE9 pD3Device, LPDIRECT3DTEXTURE9 texture
	, float cx, float cy)
	:m_bAlive(false)
	,m_frame(0)
{
	for (int i = 0; i < SPR_MAX; ++i)
		m_spr[i] = new CSprite(pD3Device, texture, cx, cy);
}


CEffect::~CEffect()
{
	for (int i = 0; i < SPR_MAX; i++)
		m_spr[i]->ReleaseSprite();
}

void CEffect::SetTexture(int id, LPDIRECT3DTEXTURE9 texture)
{
	m_spr[id]->SetTexture(texture);
}
void CEffect::SetPosition(D3DXVECTOR3& pos)
{
	for (int i = 0; i < SPR_MAX; ++i)
		m_spr[i]->SetPosition(pos);
}
void CEffect::SetAwake(D3DXVECTOR3& pos)
{
	m_bAlive = true;
	m_frame = 0;
	m_dwPrevTime = GetTickCount();
	SetPosition(pos);
}

void CEffect::Update()
{
	if (m_bAlive == true)
	{
		DWORD time = GetTickCount() - m_dwPrevTime;

		if (time > 100)
		{
			m_frame++;
			m_dwPrevTime = GetTickCount();//!!!갱신

			if (m_frame == SPR_MAX)
				m_bAlive = false;//!!! 다 했으면 끝
		}
	}
}
void CEffect::Draw()
{
	if (m_bAlive == true)
	{
		m_spr[m_frame]->Draw();
	}
}