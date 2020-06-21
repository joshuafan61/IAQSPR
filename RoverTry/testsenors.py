import MySQLdb
import serial
import time
ser = serial.Serial('/dev/ttyUSB0', 9600)
db = MySQLdb.connect("localhost", "root", "104403011","sensorData")
cursor = db.cursor()
while 1:
    print("waiting for data...")
    print("")
    mq2 = ser.readline()
    mq7 = ser.readline()
    mq131 = ser.readline()
    mq135 = ser.readline()
    mq136 = ser.readline()
    time.sleep(1)
    pm1 = ser.readline()
    pm25 = ser.readline()
    pm10 = ser.readline()
    time.sleep(0.1)
    mq2 = int(mq2)
    mq7 = int(mq7)
    mq131 = int(mq131)
    mq135 = int(mq135)
    mq136 = int(mq136)
    pm1 = int(pm1)
    pm25 = int(pm25)
    pm10 = int(pm10)
    print("inserting to database..")
    print("")
    sql = "INSERT INTO systemdata(mq2,mq7,mq131,mq135,mq136,pm1,pm25,pm10) VALUES (%d, %d, %d, %d, %d, %d, %d, %d)" %(mq2,mq7,mq131,mq135,mq136,pm1,pm25,pm10)
    cursor.execute(sql)
    db.commit()
