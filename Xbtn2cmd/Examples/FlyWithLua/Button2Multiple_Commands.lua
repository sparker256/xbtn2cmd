-- Button 2 Multiple Commands
-- William Good
-- 12-07-18
-- Allows using more than one command for a button of Xbtn2cmd.


DataRef( "Page_Number", "bgood/xbtn2cmd/page_number_value", "readonly" )
DataRef( "Button_Number", "bgood/xbtn2cmd/button_number_value", "readonly" )

Page_Number = 0
Button_Number = 0

function many_commands()
	if (Page_Number == 1) and (Button_Number == 2) then
		command_once("sim/lights/nav_lights_on")
		command_once("sim/lights/taxi_lights_on")
	end

	if (Page_Number == 1) and (Button_Number == 5) then
		command_once("sim/lights/nav_lights_off")
		command_once("sim/lights/taxi_lights_off")
	end
end

do_every_frame("many_commands()")
