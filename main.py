import baidu_aip
from pyparrot.Minidrone import Mambo
import time
mamboAddr = "e0:14:d0:63:3d:d0"

# make my mambo object
# remember to set True/False for the wifi depending on if you are using the wifi or the BLE to connect
mambo = Mambo(mamboAddr, use_wifi=True)

print("trying to connect")
#success = mambo.connect(num_retries=3)
#print("connected: %s" % success)
#mambo.smart_sleep(2)
#mambo.ask_for_state_update()

if (1):
    # get the state information

    while (1):
     print("\n\n==================================================")
     print("Please tell me the command(limit within 2 seconds):")
     result=baidu_aip.voice_recognize();
     print(result)

     if result=="起飞" or result=="许飞" or result=="息飞" or result=="李飞"or result=="喜欢" or result=="飞":
      print("taking off")
      mambo.connect(num_retries=3)
      mambo.ask_for_state_update()
      mambo.safe_takeoff(5)
      #mambo.smart_sleep(5)
      print("Control End...")

     if result=="前进":
      print("flip front")
      mambo.connect(num_retries=3)
      mambo.ask_for_state_update()
      success = mambo.flip(direction="front")
      print("mambo flip result %s" % success)
      mambo.smart_sleep(5)

     if result=="降落":
       print("landing")
       #mambo.connect(num_retries=3)
       #mambo.ask_for_state_update()
       mambo.safe_land(5)
       print("Control End...")
        #mambo.smart_sleep(5)
     time.sleep(3)


