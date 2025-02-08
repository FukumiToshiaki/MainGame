#pragma once
#include <SpriteRender.h>
const float PI = 3.14159f;

class Game;
class Butten_UI :public IGameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Butten_UI() {};
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Butten_UI() {};

	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// ���C�v�v�Z
	/// </summary>
	void WipeCalc();
	/// <summary>
	/// UI�J���[�v�Z
	/// </summary>
	void ColorCalc();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Render(RenderContext& rc);

	/// <summary>
	/// Y�{�^����bool�̕ύX
	/// </summary>
	void SetisYPush(bool YPush)
	{
		m_isYPush = YPush;
	}
private:
	/// <summary>
	/// �t�H���g�J���[�ύX�Ɏg�p����Bool
	/// </summary>
	bool m_isFontColor = false;
	/// <summary>
	/// Y�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenY_UI;
	/// <summary>
	/// X�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenX_UI;
	/// <summary>
	/// A�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenA_UI;
	/// <summary>
	/// B�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenB_UI;
	/// <summary>
	/// RT�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenRT_UI;
	/// <summary>
	/// RB�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenRB_UI;
	/// <summary>
	/// LB�{�^���̕\���X�v���C�g
	/// </summary>
	SpriteRender m_buttenLB_UI;
	/// <summary>
	/// �Q�[���̃C���X�^���X���i�[����|�C���^�ϐ�
	/// </summary>
	Game* m_game = nullptr;
	/// <summary>
	/// Y�{�^����������Ă��邩�ǂ���
	/// </summary>
	bool m_isYPush = false;

	DirectX::SpriteBatch* m_spriteBatch;  //SpriteBatch
	/// <summary>
	/// �p�x
	/// </summary>
	float m_degree = 360.0f;   
};

