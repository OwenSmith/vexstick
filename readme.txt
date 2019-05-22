Readme.txt
	this file

VexStick (vexstick.ino)
	3x 12-bit axes (roll, pitch, yaw)
	16x buttons (up-to, matrix)
	1x POV hat (matrix)

	X: Roll
	Y: Pitch
	Z: Yaw
	B0: Trigger
	B1: Pinkie
	B2: Pickle (right side of stick head)
	B3: Trigger2
	B4..7: D-Pad (center-low)
	B8..11: HAT2 (left)
	B12..15: HAT3 (right)
	POV: POV (center-high)

VexDelta (vexdelta.ino)
	3x 12-bit axes (sway, heave, surge)
	16x buttons (up-to, matrix)
	1x POV hat (matrix)

	X: Sway
	Y: Heave
	Z: Surge
	B0..15: undefined
	POV: undefined

Libraries/VexJoystick
	HID Joystick Library for a 3x 12-bit axis, 16x button, 1x POV device

Libraries/VexDelta
	Delta kinematics Library, converts 3x 'angles' (0-4095) to 3x positions (0-4095)

Libraries/VexAxis
	Auto-calibration Library, takes 15-bit input, calibrates and outputs 12-bit

Libraries/VexMatrix
	Button Matrix Library, handles button inputs

stl/VexStick/*.stl
	STL files for VexStick mechanicals
	(+ 6x bearings, 4x bearings, 4x bearings, 4x M4-long bolts, 6x M4?-bolts, 10x M4?-nuts, ??x M3-bolts, ??x M3-nuts)
	(+ 3x potentiometers, 1x arduino/clone, ??x tactile switches, 1x ADS1115 module)

stl/VexDelta/*.stl
	STL files for VexDelta mechanicals
		Cam-Arm		(x6)
		Cam-Mount	(x6)
		Base		(x1-2)
		Grip-Base	(x1)
		Grip-Bottom (x1)
		Grip Top 	(x1)
	(+ 6x traxxis rods, 6x M3-rods, 12x M3-nuts, 6x springs, 6x bearings)
	(+ 3x potentiometer, 1x arduino/clone, ??x tactile switches, 1x ADS1115 module)
