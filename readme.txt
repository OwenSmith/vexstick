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

VexEndPoint (vexendpoint.ino)
	I2C [type][data1][data2][data3]
	4x5 button matrix -> I2C  [00000000][bbbbbbbb][bbbbbbbb][----pppp] // stick grip, up-to-16-btns + POV
	8x3 button matrix -> I2C  [00000001][bbbbbbbb][bbbbbbbb][bbbbbbbb] // stick base, up-to-24-btns
	2x 8-bit axes -> I2C      [00000002][xxxxxxxx][yyyyxxxx][yyyyyyyy] // stick grip, x/y ministick

Libraries/VexJoystick
	HID Joystick Library for a 3x 12-bit axis, 16x button, 1x POV device

Libraries/VexDelta
	Delta kinematics Library, converts 3x 'angles' (0-4095) to 3x positions (0-4095)

Libraries/VexAxis
	Auto-calibration Library, takes 15-bit input, calibrates and outputs 12-bit

Libraries/VexMatrix
	Button Matrix Library, handles button inputs

VexStick:
	gimbal_cam.stl (x4)
	gimbal_core_bearing_carrier_non_pot_side.stl (x1)
	gimbal_core_bearing_carrier_pot_side.stl (x1)
	gimbal_core_non_pot_side.stl (x1)
		gimbal_core_pot_side.stl (x1 - needs mod for pot)
	gimbal_frame_cam_side.stl (x1)
	gimbal_frame_pot_side.stl (x1)
		gimbal_lever_arm.stl (x1 - needs mod for twist and pot)
		gimbal_twist_base.stl (x1 - needs making)
		housing_assembly.stl (x2 - needs rework into 2 frames)
		grip_left.stl (x1 - needs making)
		grip_right.stl (x1 - needs making)
		dpad.stl (x1 - needs making)
		castle_hat.stl (x2 - needs making)
		china_hat.stl (x1 - needs making)
		trigger.stl (x1 - needs making)
	
	6802zz bearing (x6 - gimbal/twist pivots)
	685zz bearing (x4 - cam arm pivot)
	MF105zz bearing (x8 - cam arm rests on these)
	
	M4x(long) Bolt+Nut (x4 - mount gimbal_frame* to housing_assembly)
	M4x40? Bolt+Nut (x4? - join gimbal_core* to gimbal_core_bearing*)
	M4x25? Bolt+Nut (x2? - mount MF105zz to gimbal_lever_arm/gimbal_core_non_pot_side)
	
	Torsion Spring (x1 - twist spring)
	25mm Spring (x2 - joins 2 cam_arms)
	
	Potentiometer (x3 - read axes)
	ADS1115 (x1 - 15-bit axes)
	Arduino Leonardo/ProMicro (x2 - base + grip)
	Tactile Switches (x? - switches)
	Diodes (x? - diodes for switch matrix)
		M3x? Bolt+Nut (x? - join grip* and gimbal_twist_base)

VexDelta:
		handle_top.stl (x1 - top of puck)
		handle_bottom.stl (x1 - bottom of puck)
		actuator.stl (x1 - join puck + traxxis rods)
		pivot_arm.stl (x6 - join traxxis rods to pivot_base/potentiometers/springs)
		pivot_base.stl (x6 - mount bearings and pivot_arms)
		delta_base.stl (x2 - hold pivot_base at 60 degrees to each other)
	
	6802zz bearing (x6)
	
	traxxis rod (x6)
	
	Torsion Spring (x6)
	
	M3x? Bolt+Nut (x?)
	M3 rod (x6)
	M3 locking-nut (x12)
	
	Potentiometer (x3)
	ADS1115 (x1 - 15-bit axes)
	Arduino Leonardo/ProMicro (x2 - base + grip)
	Tactile Switches (x? - switches)
	Diodes (x? - diodes for switch matrix)

