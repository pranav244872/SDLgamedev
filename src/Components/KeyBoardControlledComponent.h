#ifndef KEYBOARDCONTROLLEDCOMPONENT_H
#define KEYBOARDCONTROLLEDCOMPONENT_H

#include <glm/glm.hpp>

struct KeyBoardControlledComponent
{
	glm::vec2 upVelocity;
	glm::vec2 rightVelocity;
	glm::vec2 downVelocity;
	glm::vec2 leftVelocity;

	KeyBoardControlledComponent
	(
		glm::vec2 upVelocity = glm::vec2(0,0),
		glm::vec2 rightVelocity = glm::vec2(0,0),
		glm::vec2 downVelocity = glm::vec2(0,0),
		glm::vec2 leftVelocity = glm::vec2(0,0)
	)
	: 
	upVelocity(upVelocity), rightVelocity(rightVelocity),
	downVelocity(downVelocity), leftVelocity(leftVelocity) {}
};

#endif 
