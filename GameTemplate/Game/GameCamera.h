#pragma once

class Player1;
class Player2;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	/// <summary>
	/// 2p���̃J�����ʒu�̂��߂̉��u��
	/// </summary>
	void karioki();

public:
	/// <summary>
	/// �����_�̃x�N�g�����擾����
	/// </summary>
	const Vector3& GetForwardVector() const
	{
		return m_toCameraPos;
	}

private:
	Player1* m_player;	//�v���C���[�B
	Player2* m_player2;	//�v���C���[�B
	Vector3 m_toCameraPos;	//�����_���王�_�Ɍ������x�N�g���B
	int m_CameraState = 0;
};