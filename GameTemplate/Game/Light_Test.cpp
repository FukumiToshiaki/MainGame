#include "stdafx.h"
#include "Light_Test.h"

bool Light_Test::Start()
{

	m_pointLightList.Init();
	Vector3 pointLightPosition = { 0.0f, 2000.0f, 10.0f };
	//�|�C���g���C�g�̍��W��ݒ肷��B
	m_pointLightList.SetPosition(pointLightPosition);
		//�|�C���g���C�g�̃p�����[�^��ݒ肷��B
	//�|�C���g���C�g�̐F�B
	m_pointLightList.SetColor(Vector3(1.0f, 9.0f, 1.0f));
	//�|�C���g���C�g�̉e���͈́B
	m_pointLightList.SetRange(3000.0f);
	//�|�C���g���C�g�̌������B
	m_pointLightList.SetAffectPowParam(1.5f);
	////true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ȃ��B
	return true;

}
void Light_Test::Update()
{

}

void Light_Test::Render(RenderContext& rc)
{
}
