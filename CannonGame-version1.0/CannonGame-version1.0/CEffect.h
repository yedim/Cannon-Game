#pragma once
#define SPR_MAX 5
class CSprite;
class CEffect
{
private:
	CSprite * m_spr[SPR_MAX];
	DWORD m_dwPrevTime;
	int m_frame;

public:
	bool m_bAlive;

	explicit CEffect(LPDIRECT3DDEVICE9 pD3Device, LPDIRECT3DTEXTURE9 texture
	,float cx,float cy);
	virtual ~CEffect();

	void SetTexture(int id, LPDIRECT3DTEXTURE9 texture);
	void SetPosition(D3DXVECTOR3& pos);
	void SetAwake(D3DXVECTOR3& pos);

	void Update();
	void Draw();

};

