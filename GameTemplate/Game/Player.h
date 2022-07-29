#pragma once
class Player : public IGameObject
{
public:
	/// <summary>
	/// �J�n�̏���
    /// </summary>
    /// <returns></returns>
	bool Start() override;
	/// <summary>
    /// �X�V����
    /// </summary>
	void Update() override;
	/// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="rc"></param>
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// �v���C���[�̍��W���擾����B
	/// </summary>
	/// <returns>�v���C���[�̍��W�B</returns>
	const Vector3& GetPlayerPosition() const
	{
		return m_position;
	}



private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimationClip_Idle,				//�ҋ@�A�j���[�V�����B	
		//enAnimationClip_Walk,				//�����A�j���[�V�����B
		//enAnimationClip_Run,				//����A�j���[�V�����B
		//enAnimationClip_Attack1,			//�U���A�j���[�V�����B
		//enAnimationClip_Attack2,			//�U���A�j���[�V�����B
		//enAnimationClip_Attack3,			//�U���A�j���[�V�����B
		//enAnimationClip_MagicAttack,		//���@�U���A�j���[�V�����B
		//enAnimationClip_HitDamage1,			//��_���[�W�A�j���[�V�����B
		//enAnimationClip_HitDamage2,			//��_���[�W�A�j���[�V�����B
		//enAnimationClip_Down1,				//HP��0�B
		//enAnimationClip_Down2,				//HP��0�B
		//enAnimationClip_Down3,				//HP��0�B
		//enAnimationClip_PushLever,			//���o�[�������A�j���[�V�����B
		//enAnimationClip_Winner,				//�����A�j���[�V�����B
		enAnimationClip_Num,				//�A�j���[�V�����̐��B
	};


	Model m_model;
	ModelRender m_player;                               //�v���C���[
	Animation m_animation;								// �A�j���[�V����
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;       //�L�����N�^�[�R���g���[���[�B
	Vector3 m_position= Vector3::Zero;				   // ���W
	Quaternion m_rotation = Quaternion::Identity;;     // ��]
	Vector3 m_scale=Vector3::One;	                   // �g�嗦
	CollisionObject* m_collisionObject;

	int m_playerState;
	float m_timer = 0.0f;
};