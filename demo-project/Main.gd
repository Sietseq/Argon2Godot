extends Node2D

var Argon2 = load("res://Argon2.gdns").new()

onready var TextEdit = $TextEdit
onready var Label = $Label
onready var Button = $Button

var rng = RandomNumberGenerator.new()

func _on_Button_pressed():
	Button.disabled = true
	
	var result : String
	var salt : String = ""
	for _i in range(16):
		var b = str(rng.randi_range(0,9))
		salt += b
	result = Argon2.RawHash(TextEdit.text, salt)
	
	Label.text = result
	Button.disabled = false
	TextEdit.text = ""
