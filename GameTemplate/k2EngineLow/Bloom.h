#pragma once
namespace nsK2EngineLow {

    const int NUM_WEIGHTS = 8;

    class Bloom
    {
    public:
        /// <summary>
        /// �u���[�p�̃p�����[�^�[
        /// </summary>
        struct SBlurParam
        {
            float weights[NUM_WEIGHTS];
        };
    };
    RenderTarget mainRenderTarget;
}