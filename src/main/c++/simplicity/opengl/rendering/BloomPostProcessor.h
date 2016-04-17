/*      _                 _ _      _ _
 *     (_)               | (_)    (_) |
 *  ___ _ _ __ ___  _ __ | |_  ___ _| |_ _   _
 * / __| | '_ ` _ \| '_ \| | |/ __| | __| | | |
 * \__ \ | | | | | | |_) | | | (__| | |_| |_| |
 * |___/_|_| |_| |_| .__/|_|_|\___|_|\__|\__, |
 *                 | |                    __/ |
 *                 |_|                   |___/
 *
 * This file is part of simplicity. See the LICENSE file for the full license governing this code.
 */
#ifndef BLOOMPOSTPROCESSOR_H
#define BLOOMPOSTPROCESSOR_H

#include <simplicity/model/Model.h>
#include <simplicity/rendering/PostProcessor.h>

#include "OpenGLRenderingEngine.h"

namespace simplicity
{
	namespace opengl
	{
		class BloomPostProcessor :public PostProcessor
		{
			public:
				BloomPostProcessor();

				void process(RenderingEngine& engine) override;

			private:
				std::unique_ptr<FrameBuffer> pingFrameBuffer;

				std::unique_ptr<FrameBuffer> pongFrameBuffer;

				std::unique_ptr<Model> quad;

				OpenGLRenderingEngine::RenderList renderList;
		};
	}
}

#endif /* BLOOMPOSTPROCESSOR_H */
