from datetime import datetime
import time

time1 = "1970-1-2 "
time2 = "00:00:01"
time3 = "17:00:00"


#a = time.strptime("00:00:01","%H:%M:%S")
#b = time.strptime("17:00:00","%H:%M:%S")
#print(time.strptime("00:00:01","%H:%M:%S"),time.strptime("17:00:00","%H:%M:%S"))
a = time.strptime(time1+time2,"%Y-%m-%d %H:%M:%S")
b = time.strptime(time1+time3,"%Y-%m-%d %H:%M:%S")
#a = time.mktime(time.strptime("1970-1-2 00:00:01","%Y-%m-%d %H:%M:%S"))
#b = time.mktime(time.strptime("1970-1-2 17:00:00","%Y-%m-%d %H:%M:%S"))
aa = time.mktime(a)
bb = time.mktime(b)
print(a,b,bb-aa)
