#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>

namespace godot
{
	class Argon2 : public Node
	{

		// Godot structure
	private:
		GODOT_CLASS(Argon2, Node)
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		Argon2();
		~Argon2();


		// Gameplay methods
	public:
		String RawHash(String str, String salt);

	private:




	};
}
