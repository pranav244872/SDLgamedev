-- This a Lua table that contain values for the initialization of our game engine
config = {
	title = "My Game Engine",
	fullscreen = false,
	resolution = {
		width = 800,
		height = 600
	}
}

-- This is a Lua function that calculates the factorial of a given number
function factorial(n)
	if (n == 0) or (n == 1) then
		return 1
	end
	return factorial(n-1)*n
end
