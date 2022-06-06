#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	void RenderingEngine::SpriteRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Spriterenders) {
			renderObj->OnRender2D(rc);
		}
		//�o�^����Ă�`��I�u�W�F�N�g���N���A
		m_Spriterenders.clear();
	}
	
	void RenderingEngine::FontRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Fontrenders) {
			renderObj->OnRender2D(rc);
		}
		//�o�^����Ă�`��I�u�W�F�N�g���N���A
		m_Fontrenders.clear();
	}
	
}