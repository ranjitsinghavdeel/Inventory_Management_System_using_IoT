# Inventory_Management_System_using_IoT
The project is a combination of hardware and software integrating IoT based sensor for real-time inventory status with features of tracking inventory levels, alert for low inventory, inventory tracking for every in's and out's from the system. 
# Abstract
— Inventory management is an important function for organizations that provide services with physical goods, their domains include manufacturing, retail and distribution. The goal of inventory management system is to ensure availability of product, minimize stock outs and improve efficiency.  This project includes deployment of this system for real world scenario using integration of Internet of Things (IoT) technologies with cloud computing and user-friendly interface to provide real-time, automated tracking.
# Features
The project is divided in two modules, with one made to track inventory levels and the other to track each and every stock entering and exiting the system. 
1) The main feature provided by first module is alerts based on low inventory levels to user with pre-defined threshold levels.
2) The second module's main feature is to prevent stock loss in the system as the observing user can keep in check for every stock/ product entering and exiting the system in real-time.
3) Improves efficiency of stock management and time management.
4) Stock refilling is optimized as threshold is set to give alert before stock levels are at zero.
5) Compact setup helps it to be intergrated with already existing inventory management systems.
6) Low power consumtion.
7) User-friendly interface as ThingSpeak IoT platform is used.
# Tech Stack
Hardware:
1) ESP32 Wi-Fi module
2) ESP8266 Wi-Fi module
3) Ultrasonic sensor
4) RFID tags
5) RFID reader

Software:
1) Arduino IDE
2) embedded C
3) ThingSpeak IoT platform
4) Telegram chatbot
# Working 
- The system operates based on the input from both the modules. Alert function of the system is set such that if Ultrasonic sensor reads a distance greater than thresold (indicating stock level is moving further away from sensor that is approaching low levels), it is programmed to give the user/ operator alert through telegram chatbot. 
- The second module is based on pair of RFID readers and RFID tags attached to stock/ inventory/ products. In a real-life conveyor belt these two RFID readers will be attached to end points that is entery and exit respectively. Therefore any stock entering and exiting the system will be scanned twice one for entry and one for exit by respective readers. 
