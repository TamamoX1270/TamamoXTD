#pragma once
namespace nsK2EngineLow {

	class PointLight
	{
	public:
		// �|�C���g���C�g�p�̍\���̂��`����B
		struct PointLightST
		{
			// step-1 ���C�g�\���̂Ƀ|�C���g���C�g�p�̃����o�ϐ���ǉ�����
			Vector3 ptPosition;		//�ʒu�B
			float pad2;					//�p�f�B���O�B
			Vector3 ptColor;			//�J���[�B
			float ptRange;				//�e���͈́B
		};
	public:
		PointLight();
		~PointLight();
		/// <summary>
		/// �|�C���g���C�g�̈ʒu��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetPointPos(const Vector3& pos)
		{
			m_pointLig.ptPosition = pos;
		}
		/// <summary>
		/// �|�C���g���C�g�̐F��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetPointColor(const Vector3& col)
		{
			m_pointLig.ptColor = col;
		}
		PointLightST& GetPointLight()
		{
			return m_pointLig;
		}
	private:
		PointLightST                m_pointLig;                 //�|�C���g���C�g�̃f�[�^���쐬����B
	};

	//���̏ꏊ�ł��ǂݍ��߂�悤�ɃO���[�o���ɂ���B
	extern PointLight g_pointLig;
}