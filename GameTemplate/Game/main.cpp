#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

const int NUM_DIRECTIONAL_LIGHT = 4; // �f�B���N�V�������C�g�̐�

//�u���[��
/// <summary>
/// �f�B���N�V�������C�g
/// </summary>
struct DirectionalLight
{
	Vector3 direction;  // ���C�g�̕���
	float pad0;         // �p�f�B���O
	Vector4 color;      // ���C�g�̃J���[
};

/// <summary>
/// ���C�g�\����
/// </summary>
struct Light
{
	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT]; // �f�B���N�V�������C�g
	Vector3 eyePos;                 // �J�����̈ʒu
	float specPow;                  // �X�y�L�����̍i��
	Vector3 ambinetLight;           // ����
};

const int NUM_WEIGHTS = 8;
/// <summary>
/// �u���[�p�̃p�����[�^�[
/// </summary>
struct SBlurParam
{
	float weights[NUM_WEIGHTS];
};
//�u����

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, 250.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	//�u
	
     // step-1 ���C�������_�����O�^�[�Q�b�g���쐬����
    RenderTarget mainRenderTarget;
    mainRenderTarget.Create(
        1600,
        900,
        1,
        1,
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );
    // step-2 �������̃��C�g��p�ӂ���
    Light light;

    light.directionalLight[0].color.x = 5.8f;
    light.directionalLight[0].color.y = 5.8f;
    light.directionalLight[0].color.z = 5.8f;

    light.directionalLight[0].direction.x = 0.0f;
    light.directionalLight[0].direction.y = 0.0f;
    light.directionalLight[0].direction.z = -1.0f;
    light.directionalLight[0].direction.Normalize();

    light.ambinetLight.x = 0.5f;
    light.ambinetLight.y = 0.5f;
    light.ambinetLight.z = 0.5f;
    light.eyePos = g_camera3D->GetPosition();
    // ���f���̏���������ݒ肷��
    ModelInitData plModelInitData;

    // tkm�t�@�C�����w�肷��
    plModelInitData.m_tkmFilePath = "Assets/modelData/model/eggR.tkm";

    // �V�F�[�_�[�t�@�C�����w�肷��
    plModelInitData.m_fxFilePath = "Assets/shader/sample3D.fx";

    // ���[�U�[�g���̒萔�o�b�t�@�[�ɑ���f�[�^���w�肷��
    plModelInitData.m_expandConstantBuffer = &light;

    // ���[�U�[�g���̒萔�o�b�t�@�[�ɑ���f�[�^�̃T�C�Y���w�肷��
    plModelInitData.m_expandConstantBufferSize = sizeof(light);

    // �����_�����O����J���[�o�b�t�@�[�̃t�H�[�}�b�g���w�肷��
    plModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    // �ݒ肵���������������ƂɃ��f��������������
    Model plModel;
    plModel.Init(plModelInitData);

    // step-3 �P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬
    RenderTarget luminnceRenderTarget;
    //�𑜓x�A�~�b�v�}�b�v���x��
    luminnceRenderTarget.Create(
        1600,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
        900,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
        1,
        1,
        //�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���B
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );
    // step-4 �P�x���o�p�̃X�v���C�g��������
    SpriteInitData luminanceSpriteInitData;
    //�P�x���o�p�̃V�F�[�_�[�̃t�@�C���p�X���w�肷��B
    luminanceSpriteInitData.m_fxFilePath = "Assets/shader/samplePostEffect.fx";
    //���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
    luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
    //�s�N�Z���V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
    luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
    //�X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ����B
    luminanceSpriteInitData.m_width = 1600;
    luminanceSpriteInitData.m_height = 900;
    //�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�B
    luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    //�`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��B
    luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //�쐬�����������������ƂɃX�v���C�g������������B
    Sprite luminanceSprite;
    luminanceSprite.Init(luminanceSpriteInitData);
    // step-5 �K�E�V�A���u���[��������
    GaussianBlur gaussianBlur;
    gaussianBlur.Init(&luminnceRenderTarget.GetRenderTargetTexture());

    // step-6 �{�P�摜�����Z��������X�v���C�g��������
    SpriteInitData finalSpriteInitData;
    finalSpriteInitData.m_textures[0] = &gaussianBlur.GetBokeTexture();
    //�𑜓x��mainRenderTarget�̕��ƍ����B
    finalSpriteInitData.m_width = 1600;
    finalSpriteInitData.m_height = 900;
    //�ڂ������摜���A�ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷��̂ŁA
    //2D�p�̃V�F�[�_�[���g�p����B
    finalSpriteInitData.m_fxFilePath = "Assets/shader/sample2D.fx";
    //�������A���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���B
    finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
    //�J���[�o�b�t�@�̃t�H�[�}�b�g�͗�ɂ���āA32�r�b�g���������_�o�b�t�@�B
    finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //�������������ɉ��Z�����p�̃X�v���C�g������������B
    Sprite finalSprite;
    finalSprite.Init(finalSpriteInitData);

    // step-7 �e�N�X�`����\��t���邽�߂̃X�v���C�g������������
    SpriteInitData spriteInitData;
    //�e�N�X�`����mainRenderTarget�̃J���[�o�b�t�@�B
    spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    spriteInitData.m_width = 1600;
    spriteInitData.m_height = 900;
    //���m�N���p�̃V�F�[�_�[���w�肷��B
    spriteInitData.m_fxFilePath = "Assets/shader/sample2D.fx";
    //�������I�u�W�F�N�g���g���āA�X�v���C�g������������B
    Sprite copyToFrameBufferSprite;
    copyToFrameBufferSprite.Init(spriteInitData);
    //�u����

	//NewGO<Game>(0);

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();

        //�u
          // step-8 �����_�����O�^�[�Q�b�g��mainRenderTarget�ɕύX����
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //�����_�����O�^�[�Q�b�g��ݒ�B
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //�����_�����O�^�[�Q�b�g���N���A�B
        renderContext.ClearRenderTargetView(mainRenderTarget);
        // step-9 mainRenderTarget�Ɋe�탂�f����`�悷��
        plModel.Draw(renderContext);
        //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
        // step-10 �P�x���o
        renderContext.WaitUntilToPossibleSetRenderTarget(luminnceRenderTarget);
        //�����_�����O�^�[�Q�b�g��ݒ�B
        renderContext.SetRenderTargetAndViewport(luminnceRenderTarget);
        //�����_�����O�^�[�Q�b�g���N���A�B
        renderContext.ClearRenderTargetView(luminnceRenderTarget);
        //�P�x���o���s���B
        luminanceSprite.Draw(renderContext);
        //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
        renderContext.WaitUntilFinishDrawingToRenderTarget(luminnceRenderTarget);
        // step-11 �K�E�V�A���u���[�����s����
        gaussianBlur.ExecuteOnGPU(renderContext, 20);
        // step-12 �{�P�摜�����C�������_�����O�^�[�Q�b�g�ɉ��Z����
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //�����_�����O�^�[�Q�b�g��ݒ�B
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //�ŏI�����B
        finalSprite.Draw(renderContext);
        //�����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂��B
        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
        // step-13 ���C�������_�����O�^�[�Q�b�g�̊G���t���[���o�b�t�@�[�ɃR�s�[
        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        copyToFrameBufferSprite.Draw(renderContext);
        // ���C�g�̋�����ύX����
        light.directionalLight[0].color.x += g_pad[0]->GetLStickXF() * 0.5f;
        light.directionalLight[0].color.y += g_pad[0]->GetLStickXF() * 0.5f;
        light.directionalLight[0].color.z += g_pad[0]->GetLStickXF() * 0.5f;
        //�u����

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		// �X�v���C�g�����_�[�̕`�揈�����Ăяo���B
		//g_renderingEngine.SpriteRenderDraw(renderContext);

		// �t�H���g�����_�[�̕`�揈�����Ăяo���B
		//g_renderingEngine.FontRenderDraw(renderContext);

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();

		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();

	}

	delete g_k2EngineLow;

	return 0;
}