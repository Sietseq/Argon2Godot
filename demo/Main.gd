extends Node2D

onready var TextEdit = $TextEdit
onready var Label = $Label
onready var Button = $Button

var rng = RandomNumberGenerator.new()

func _on_Button_pressed():
	Button.disabled = true
	
	var result : String
	var salt = rng.randi_range(1000000000000000, 9999999999999999)
	result = $Argon2.RawHash(TextEdit.text, salt)
	
	Label.text = result
	Button.disabled = false
	TextEdit.text = ""
