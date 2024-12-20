#include "k2EngineLowPreCompile.h"
#include "k2EngineLow.h"
#include "Light.h"

namespace nsK2EngineLow {

    Light::Light()
    {

    }

    void Light::Init()
    {

        //lightCamera.SetAspectOneFlag(true);

        m_lightCamera.SetViewAngle(Math::DegToRad(90.0f));
        
        // �J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu
        // Y�̐��l���グ��Ɖe�̉f��͈͂��L����
        m_lightCamera.SetPosition(0.0f, 3000.0f, 100.0f);

        // �J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ
        m_lightCamera.SetTarget(0, 0, 0);

        // �������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���
        //lightCamera.SetUp(1, 0, 0);

        // ���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���
        m_lightCamera.Update();

        //���C�g�r���[�v���W�F�N�V����
        m_light.mPVL = m_lightCamera.GetViewProjectionMatrix();

        // ���z��
        m_light.directionalLight[0].color.x = 1.0f;
        m_light.directionalLight[0].color.y = 1.0f;
        m_light.directionalLight[0].color.z = 1.0f;

        m_light.directionalLight[0].direction.x = 1.0f;
        m_light.directionalLight[0].direction.y = -1.0f;
        m_light.directionalLight[0].direction.z = -1.0f;

        m_light.directionalLight[0].direction.Normalize();
        m_light.directionalLight[0].castShadow = true;


        m_light.ambientLight.x = 0.4f;
        m_light.ambientLight.y = 0.4f;
        m_light.ambientLight.z = 0.4f;
        m_light.eyePos = g_camera3D->GetPosition();

        //�S�Ẵ|�C���g���C�g�𖢎g�p�ɂ���
        for (auto& pt : m_light.pointLights) {
            pt.UnUse();
            pt.SetAffectPowParam(1.0f);
        }
        m_light.numPointLight = 0;

        // �S�ẴX�|�b�g���C�g�𖢎g�p�ɂ���B
        for (auto& sp : m_light.spotLights) {
            sp.UnUse();
        }
        m_light.numSpotLight = 0;
    }

    void Light::Update()
    {
        

        ////���C�g�̋�����ύX����
        //if (g_pad[0]->IsPress(enButtonX))
        //    //�������Q�[���p�b�h�̉E�{�^���������ꂽ��B
        //{
        //    //�L�[�{�[�h��6�L�[�B
        //    m_light.directionalLight[0].color.x += 1.0f;
        //    m_light.directionalLight[0].color.y += 1.0f;
        //    m_light.directionalLight[0].color.z += 1.0f;
        //}

        //if (g_pad[0]->IsPress(enButtonB))
        //    //�������Q�[���p�b�h�̍��{�^���������ꂽ��B
        //{
        //    //�L�[�{�[�h��4�L�[�B
        //    m_light.directionalLight[0].color.x -= 1.0f;
        //    m_light.directionalLight[0].color.y -= 1.0f;
        //    m_light.directionalLight[0].color.z -= 1.0f;
        //}

        m_light.numPointLight = 0;
        for (int i = 0; i < MAX_POINT_LIGHT; i++)
        {
            if (m_light.pointLights[i].GetUse())
            {
                m_light.numPointLight++;
            }
        }

        m_light.numSpotLight = 0;
        for (int i = 0; i < MAX_SPOT_LIGHT; i++)
        {
            if (m_light.spotLights[i].GetUse())
            {
                m_light.numSpotLight++;
            }
        }
    }


    SPointLight* Light::NewPointLight()
    {
        if (m_light.numPointLight >= MAX_POINT_LIGHT)
        {
            return nullptr;
        }

        for (int i = 0; i < MAX_POINT_LIGHT; i++)
        {
            if (m_light.pointLights[i].GetUse() != true)
            {
                m_light.pointLights[i].Use();
                return &m_light.pointLights[i];
            }
        }
    }

    void Light::DeletePointLight(SPointLight* m_pointlight)
    {
        //�|�C���^�ɃA�h���X�������ĂȂ������牽�������Ԃ�
        if (m_pointlight == nullptr)
        {
            return;
        }
        //������V�[�����C�g���Ǘ����Ă��Ȃ��|�C���g���C�g�ɑ΂��č폜���������s����ƊǗ����o�O��(���Ɏg�p���̃��C�g�̐�)�̂�
        //�{���ɍ폜���������Ă������m�F����
        // 
        //�����Ă����|�C���^�ɓ����Ă���A�h���X�ƁA�z��̊e�v�f�̃A�h���X���Ƃ炵���킹�āA
        //�A�h���X���������̂���������A�폜���������s����
        for (int i = 0; i < MAX_POINT_LIGHT; i++)
        {

            if (m_pointlight == &m_light.pointLights[i])
            {
                m_pointlight->UnUse();
                m_pointlight->SetColor(0.0f, 0.0f, 0.0f);
                m_pointlight->SetPosition(0.0f, 0.0f, 0.0f);
                m_pointlight->SetRange(0.0f);
                m_pointlight->SetAffectPowParam(1.0f);
            }
        }
    }


    SSpotLight* Light::NewSpotLight()
    {
        if (m_light.numSpotLight >= MAX_SPOT_LIGHT)
        {
            return nullptr;
        }

        for (int i = 0; i < MAX_SPOT_LIGHT; i++)
        {
            if (m_light.spotLights[i].GetUse() != true)
            {
                m_light.spotLights[i].Use();
                return &m_light.spotLights[i];
            }
        }
    }

    void Light::DeleteSpotLight(SSpotLight* m_spotlight)
    {
        if (m_spotlight == nullptr)
        {
            return;
        }

        for (int i = 0; i < MAX_SPOT_LIGHT; i++)
        {

            if (m_spotlight == &m_light.spotLights[i])
            {
                m_spotlight->UnUse();
                m_spotlight->SetColor(0.0f, 0.0f, 0.0f);
                m_spotlight->SetPosition(0.0f, 0.0f, 0.0f);
                m_spotlight->SetRange(0.0f);
                m_spotlight->SetRangeAffectPowParam(1.0f);
                m_spotlight->SetAngleAffectPowParam(1.0f);
            }
        }
    }
}