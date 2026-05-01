Sketch name: Project_2_combined_V3

Necessary libraries: (install these libraries to the Arduino IDE with the IDE's built-in library manager for program to compile)
	#include <SD.h> //SD card library
	#include <LiquidCrystal_I2C.h> //LCD I2C library
	#include <TinyGPSPlus.h> //GPS library


To open:
	Open the Project_2_combined_V3.ino file inside the Project_2_combined_V3
	folder using the Arduino IDE. Alternatively, from the Windows File Explorer,
	right click on the same file and select "open with > Arduino IDE".


Notes:
	The datafiles on the microSD card have to be manually formatted to be cleared
	of any past writes done to them. Otherwise, the program will continue to write
	on top of previous data. 

	**********************************************************************
	*Make sure to keep the first line of the datafiles when clearing them*
	*These are the names of the columns and are not restored when the    *
	*Arduino begins writing to the files again.                          *
	*Please do not actually format them using the Windows format function*
	*Open each file in notepad or excel and delete the data yourself     *
	**********************************************************************

	The GPS module works best in places with a clear, unobstructed space above the vehicle
