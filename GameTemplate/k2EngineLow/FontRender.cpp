#include "k2EngineLowPreCompile.h"
#include "FontRender.h"

namespace nsK2EngineLow {
	void FontRender::Draw(RenderContext& rc)
	{
		if (m_text == nullptr)
		{
			return;
		}
		/*
			for (auto& renderObj : m_Fontrenders) {
				Font font;
				font.Begin(rc);
				font.Draw(
					m_text,
					Vector2(m_position.x, m_position.y),
					m_color,
					m_rotation,
					m_scale,
					m_pivot
				);
				font.End(rc);
			}
			//�o�^����Ă�`��I�u�W�F�N�g���N���A
			m_Fontrenders.clear();
			*/
		g_renderingEngine.AddRenderObject(this);
	}
}