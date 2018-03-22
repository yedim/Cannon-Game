#pragma once
class CSprite
{
public:
	explicit CSprite(LPDIRECT3DDEVICE9 pD3DDevice, LPDIRECT3DTEXTURE9 texture,
		float cx=1.0f, float cy=1.0f);
	virtual ~CSprite();

	bool InitSprite(LPDIRECT3DDEVICE9 pD3DDevice);
	void Release();

	virtual void Update(DWORD dwCurTime){}
	virtual void Draw();

	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_Pos = pos;
	}
	void SetPosition(float x, float y)
	{
		m_Pos = D3DXVECTOR3(x, y, 0);
	}
	const D3DXVECTOR3& GetPosition() const 
	{
		return m_Pos;
	}

	void SetTexture(LPDIRECT3DTEXTURE9 texture)
	{
		m_pTexutre = texture;
	}

protected:
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DTEXTURE9 m_pTexutre;
	LPD3DXSPRITE m_pSpr;

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Center;
};

