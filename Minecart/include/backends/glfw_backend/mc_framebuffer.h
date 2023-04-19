#ifndef MINECART_FRAMEBUFF_H
#define MINECART_FRAMEBUFF_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "minecart.h"
#include "mc_logging.h"

namespace minecart {
	namespace engine {
		class FrameBuffer {
			public:
			GLuint FramebufferName = 0;
			GLuint renderedTexture;
			GLuint depthrenderbuffer;
			GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
			int width;
			int height;
			glm::mat4 Projection;
			FrameBuffer(int width, int height) {
				minecart::logging::Logger* logger = minecart::engine::GetLogger();
				logger->AddLog(LOG_DEBUG, "FrameBuffer: Creating projection matrix");
				// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
				this->Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);

				logger->AddLog(LOG_DEBUG, "FrameBuffer: Creating framebuffer %i x %i", width, height);
				// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
				this->FramebufferName = 0;
				glGenFramebuffers(1, &this->FramebufferName);
				glBindFramebuffer(GL_FRAMEBUFFER, this->FramebufferName);
				// The texture we're going to render to
				glGenTextures(1, &this->renderedTexture);
				// "Bind" the newly created texture : all future texture functions will modify this texture
				glBindTexture(GL_TEXTURE_2D, this->renderedTexture);
				// Give an empty image to OpenGL ( the last "0" )
				glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
				// Poor filtering. Needed !
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				// The depth buffer
				glGenRenderbuffers(1, &this->depthrenderbuffer);
				glBindRenderbuffer(GL_RENDERBUFFER, this->depthrenderbuffer);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthrenderbuffer);
				// Set "renderedTexture" as our colour attachement #0
				// glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);  
				// Set the list of draw buffers.
				this->DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
				glDrawBuffers(1, this->DrawBuffers); // "1" is the size of DrawBuffers
				// Always check that our framebuffer is ok
				glBindTexture(GL_TEXTURE_2D, 0);
				this->width = width;
				this->height = height;
				if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
					logger->AddLog(LOG_FATAL, "FrameBuffer: Failed to initialize OpenGL framebuffer");
					return;
				}
			}
		};
	}
}

#endif // MINECART_FRAMEBUFF_H