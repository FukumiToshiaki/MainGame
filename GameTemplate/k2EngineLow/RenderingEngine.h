#pragma once
#include "Bloom.h"
/// <summary>
/// �����_�����O�G���W���B
/// </summary>
/// <remark>
/// K2Engine�̂P�t���[���̃����_�����O�̗���͎��̂悤�ɂȂ��Ă��܂��B
/// �P.ComputeAnimatedVertex
///     ���[���h��Ԃɕϊ��ς݂̒��_���v�Z����B   
///     �ȍ~�̃��f���`��p�X�ł́A���̃p�X�Ōv�Z���ꂽ���_���g���񂷁B
/// �@�@���̃p�X�ŃC���X�^���V���O�`����s�����f���̒��_�o�b�t�@�͂P�̑傫�ȃo�b�t�@�ɂ܂Ƃ߂���B
///     �Ⴆ�΁A���郂�f�����C���X�^���V���O�`���100���_�̃��f����100�̕`�悷��ݒ�ɂȂ��Ă���ꍇ�A
///     100���_ �~ 100��1�����_���L���ł��钸�_�o�b�t�@�������B
///     ���_�o�b�t�@���܂Ƃ߂闝�R��DXR�̍������̂��߁B
///     DXR�ł̓��C�g�����[���h�ɓo�^����I�u�W�F�N�g�̐��������Ȃ�ƁA�����I��BVH���\�z�ł��Ȃ��Ȃ�A
///     �傫�����x���ቺ����B���̃I�u�W�F�N�g���P�̒��_�o�b�t�@�ɓZ�߂邱�Ƃő啝�ȍ��������\�ƂȂ�B
/// 
/// 2. �V���h�E�}�b�v�̍쐬
///     �J�X�P�[�h�V���h�E���𗘗p���ĂS�̃��C�g����̃V���h�E�}�b�v���쐬����B
///     ���̂��߁A�S�̃��C�g�@�~�@�R���̃V���h�E�}�b�v(�ߋ����p�A�������p�A�������p)�̍��v12���̃V���h�E�}�b�v���쐬�����B
/// 
/// 3. ZPrepass
///     ���C�g�J�����O�̂��߂�ZPrepass�B
///     ���ʂȃs�N�Z���`�������邽�߂ł͂Ȃ��A�[�x�e�N�X�`�����쐬���邽�߂ɑ��݂��Ă���p�X�B
///     ��q����G-Buffer�̐[�x�e�N�X�`�����g���΂����悤�Ɋ����邪�A
///     �f�B�t�@�[�h�ƃt�H���[�h�̗����̐[�x�l���������܂ꂽ�e�N�X�`�����K�v���������ߒǉ��B
/// 
/// 4. ���C�g�J�����O
///     �^�C�����Ƃ̃|�C���g���C�g�ƃX�|�b�g���C�g�̔ԍ����X�g���쐬�B
/// 
/// 5. G-Buffer�ւ̃����_�����O
///     G-Buffer�̓A���x�h&�[�x�l�A�@���A���^���b�N&�V���h�E&Smooth�̂R���B
/// 
/// 6. ���C�g���[�V���O�ŉf�荞�݉摜���쐬����B
///     NVIDIA��RTX�V���[�Y��GPU������Ă���ꍇ�A���C�g����p���Ċe�I�u�W�F�N�g�ւ̉f�荞�݉摜�𐶐�����B
///     ���̃p�X��NVIDIA��RTX�V���[�Y�ł����ʏ�͎g���Ȃ��B
///     �������Ak2EngineLow\k2EngineLowPreCompile.h��ENABLE_DXR_ON_RTX_ONLY�̃}�N���𖳌��ɂ��邱�Ƃ�
///     DXR�����p�ł���ꕔ��RTX�ȊO��GPU�iNVIDIA GTX1060�Ȃǁj�ł����C�g�����s����B
///     �������AGTX�V���[�Y�ł̓p�t�H�[�}���X���傫�����Ȃ��邽�߁A�����܂ł��J���p�B
/// 
/// 7. �f�B�t�@�[�h���C�e�B���O
///     �f�B�Y�j�[�x�[�X��PBR���C�e�B���O���s����B
/// 
/// 8. �t�H���[�h�����_�����O
///     �������I�u�W�F�N�g�����ȃV�F�[�f�B���O�̕`��p�X�B
/// 
/// 9. �|�X�g�G�t�F�N�g
///     ���L�̃|�X�g�G�t�F�N�g�����s�����B
///     9.1 �X�N���[���X�y�[�X���t���N�V����(���C�g�����s���Ă���ꍇ�͏�������Ȃ��B)
///     9.2 �V�[���̋P�x�v�Z(��q��HDR�����_�����O�̃u���[����g�[���}�b�v�Ŏg�p�����B)
///     9.3 �u���[��
///     9.4 �g�[���}�b�v
///     9.5 Effekseer�̃G�t�F�N�g�`��
///     9.6 DOF
///     9.7 FXAA + �K���}�␳
/// 
/// 10. 2D�`��
/// 11. �ŏI�摜���t���[���o�b�t�@�ɃR�s�[�B
/// </reramk>

namespace nsK2EngineLow {
	class RenderingEngine : public Noncopyable
	{
	public:

		RenderingEngine();
		~RenderingEngine();

		void Init();

		//�`��I�u�W�F�N�g��ǉ�
		void AddRenderObject(IRender* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		//3D���f���̕`��
		void Render3DModel(RenderContext& rc);

		//2D�`��
		void Render2D(RenderContext& rc);

		//���O2D�`��
		void PreRender2D(RenderContext& rc);

		//�V���h�E�}�b�v�`�揈��
		void RenderShadowMap(RenderContext& rc);

		//�t�H���g�`��
		void FontRender(RenderContext& rc);

		//���s
		void Execute(RenderContext& rc);


		RenderTarget* GetShadowMapRenderTarget()
		{
			return &m_shadowMap;
		}

	private:
		std::vector< IRender* > m_renderObjects;	// �`��I�u�W�F�N�g�̃��X�g�B

		RenderTarget m_shadowMap;
		RenderTarget mainRenderTarget;
		Bloom m_bloom;

		Sprite m_result;	//�|�X�g�G�t�F�N�g�Ȃǂ̏������I�����ŏI�I�ȉ摜
	};
}


