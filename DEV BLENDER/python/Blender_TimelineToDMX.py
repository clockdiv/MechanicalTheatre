import bpy
from DMXEnttecPro import Controller 

# Python DMX:
# https://pypi.org/project/DMXEnttecPro/

dmx = Controller('/dev/cu.usbserial-EN159904')
motorPosOld = 0

def frame_handler(scene): 
    global motorPosOld
    print("")
    print("")
    currentFrame = scene.frame_current
    # get data from Custom Properties:
    motorObject = bpy.data.objects["Cube"]

    motorPos = motorObject["motor"]
    
    # Print data to console:
    print("frame:", currentFrame) 
    print("motor pos: ", motorPos)
    print("motor pos old: ", motorPosOld)

    posDiff = abs(motorPos - motorPosOld)
    motorPosOld = motorPos    
    print("posDiff: ", posDiff)
    
    fps = 50
    stepsPerSecond = 6000   #sixteenth microstep on dmx4all controller
    maxStepsPerFrame = stepsPerSecond / fps
    
    if posDiff > maxStepsPerFrame:
        print("TOO FAST")
        speed = 255
    else:    
        speed = round(posDiff / maxStepsPerFrame * 255)
        
    print("Speed: ", speed);
    
    motorPosLow = round(motorPos) & 0xff
    motorPosHigh = (round(motorPos) >> 8) & 0xff
    
    # Send DMX-Data:
    dmx.set_channel(1, motorPosHigh)    # HIGH BYTE "Grobeinstellung"
    dmx.set_channel(2, motorPosLow)    # LOW BYTE   "Feineinstellung"
    dmx.set_channel(3, speed)
    dmx.submit() 
    
    # Animate Blender-Objects (optional):
    # bpy.data.objects["Cu be"].location.x = motor1
    # bpy.data.lights["Light"].energy = licht1*100
     


if __name__ == "__main__":
    bpy.app.handlers.frame_change_post.clear()      # clear the previous handlers if any
    bpy.app.handlers.frame_change_pre.clear()      # clear the previous handlers if any
    print("script started")
    bpy.app.handlers.frame_change_post.append(frame_handler) # on every frame change
    
