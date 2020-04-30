Github Project: domino_effect_gui_ver_2

Class: CSCE 462

Team: Domino Effect

Team Members: Aaron Kutch, Samuel Sells

This is the final version of the GUI for our team project. The first version, which can be found
at https://github.com/merlinsam123/domino_effect_gui_ver_1, is not really a GUI at all, since it used
the command line interface for the user to input data. Really, version 1 was more of an early prototype
that was used both to figure out the logic that would be used in the final version and provide
avenues to test the hardware side of the project before the final GUI was completed.

This GUI was intended to be used with a robot designed to set up a sequence of dominoes which would fall
in sequence after the first or last domino is knocked over. The robot has three wheels, the front two of
which are driven by motors. To communicate with the robot, the GUI would output the file
domino_effect_gui_output.txt once the user told the program they were done setting up the path they wanted
the robot to set up the dominoes in. The .txt file will contain letters corresponding to actions taken by the robot.

F - Drop Domino
W - Move Both Wheels Forward One Step
D - Move Only Left Wheel Forward
A - Move Only Right Wheel Forward

To execute the project above, download a version of Microsoft Visual Studio (the project was Visual Studio 2017) and
execute the project in x86. When run, the user will be presented with a GUI that will allow them to create a path for
the robot to follow. The .txt file will be created once the user tells the GUI to "finalize path".
