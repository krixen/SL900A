# SL900A
SL900A RFID Chip, CODE

The Reason for this repository is that there is little to no sample/example code online for the SL900A RFID chip. The datasheet is a little tough to read, especially since someone pointed out it looks like it was translated from a different langugage. 

File 1: SL900A_SPI_VBAT
This file was my first attempt at getting information from the on-chip sensors, in this case the battery voltage. It uses SPI communication to retrieve this data. The comments explain in more detail how it works, it is not like tranditional SPI protocol with sensors as you will find when you look through. 

File 2: SL900A_SPI_Vbat_v2
This was a much cleaner updated version of retrieveing the battery voltage as in the file 1. 
