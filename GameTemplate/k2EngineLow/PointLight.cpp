#include "k2EngineLowPreCompile.h"
#include "PointLight.h"

namespace nsK2EngineLow {
	//���̏ꏊ�ł��ǂݍ��߂�悤�ɃO���[�o���ɂ���B
	PointLight g_pointLig;
	PointLight::PointLight()
	{

		//step-2 �|�C���g���C�g�̏������W��ݒ肷��B
		m_pointLig.ptPosition.x = 0.0f;
		m_pointLig.ptPosition.y = 50.0f;
		m_pointLig.ptPosition.z = 50.0f;

		// step-3 �|�C���g���C�g�̏����J���[��ݒ肷��
		m_pointLig.ptColor.x = 10.0f;
		m_pointLig.ptColor.y = 0.0f;
		m_pointLig.ptColor.z = 0.0f;

		// step-4 �|�C���g���C�g�̉e���͈͂�ݒ肷��
		m_pointLig.ptRange = 100.0f;

	}
	PointLight::~PointLight()
	{

	}
}