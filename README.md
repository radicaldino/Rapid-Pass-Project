Title: Rapid Pass


--This is a project focused on traffic management for emergency vehicles, the motivation was to lend ambulances the upper hand in a traffic light situation, so I decided to have an IOT device on the signal which would be used to connect to an application on the ambulance drivers phone--
the phone would have an application sending real-time data like the location , emergency info etc to the device . which the device then would take and calculate the proximity of the ambulance and change the signal.
To be honest this was just an idea and a quick project so everything hasn't been thought through but what you have here is a baseline for something that can quite possibly save lives, so you can take this and build something better.

--so i have used two boards(I didnt think this throught and thought of having one board for signal/data fetching, ang the other to process the data/ You can definetly just use a NodeMCU and process the data.) Arduino Uno , and a NodeMCU esp8266 and I have also used the Arduino IOT cloud and the IOT connect app to complete this project.
esp8266 is soley responsible for connecting to the wifi and also to the device(smartphone), and the Uno is responsible for processing the data.

-- Here you'll find two files one is a mcutouno.ino file which contains the code to fetch and connect to the device through the Arduino IOT cloud, and send that data to the Uno(set the baud rate to 9200) check if the data recieved makes sense or just keep changing the baud rate until it does.
and the other file is unotomcu.ino , this file just contains the code for processing the recieved data from mcu , you can refer the code to know what kind of data im sending the uno in this code.

--I'm using the haversine formula to calculate the proximity b/w the IOT device and the application(phone) , which resulted to be insufficient half the time because it just take the position b/w the two and just calculates a straight line distance , I would suggest using some other proximity formula.

--Finally i used the Arduino IOT cloud to create a device key and you also need to provide ssid and password for the wifi that your connecting to using the mcu .

--what I found easy at the time was to create a dashboard on my smartphones arduino application that consisted of all the data that was required to be sent , and then i created an instance (device) in the application which i sent all the dashboard data to.

--This is a pretty simple project but the , "hard part" is connecting the mcu to the uno ( which can also be solved if you just use a single device).
