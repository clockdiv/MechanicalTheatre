bl_info = {
    "name": "Dump Timeline To Serial",
    "author": "Julian",
    "version": (1, 0),
    "blender": (2, 92, 0),
    "category": "Hardware",
    "location": "",
    "description": "sends timeline data to a serial device (e.g. arduino)",
    "warning" : "",
    "doc_url": "",
    "tracker_url": ""
}

import bpy
import serial
import serial.tools.list_ports
import time

# Operator: the functions where stuff actually happens:
class HARDWARE_OT_DumpTimeline(bpy.types.Operator):
    """Send Timeline To Serial"""
    bl_idname = "hardware.dump_timeline"
    bl_label = "dump_timeline Timeline To Serial"

    
    def execute(self, context):
        serialport = "/dev/" + context.scene.dumpTimeline_props.serialports
        self.serial_device = serial.Serial(port=serialport, baudrate=115200, timeout=.1)
        time.sleep(1)
        print("\n\n\ndumping timeline...")
        print("Object: ", end ='')
        print(context.active_object)    
        print("frames per second: ", end = '')
        print(context.scene.render.fps)
        print()

        # get the names of the curves that will be dumped:
        curvenames = context.scene.dumpTimeline_props.custom_properties_list.split(sep=',')
        curvenames = [s.strip() for s in curvenames]

        # create a Dictionary with the curves and all the keyframes for each curve::
        all_curves_w_keyframes = {}
        for K in context.active_object.keys():
            key_values = []
            if K in curvenames:
                for f in range(context.scene.frame_start, context.scene.frame_end + 1):
                    context.scene.frame_set(f)
                    key_values.append((context.active_object[K]))
                all_curves_w_keyframes[K] = key_values
        # now we have all the data! Hahahahaaaaa!

        # Set the Serial Device into Upload Mode:
        print("Set Serial Device into Upload-Mode")
        self.serial_device.write(bytes('u', 'utf-8'))
        time.sleep(0.25)
        
        # Send information on how many frames we will send:
        framecount = context.scene.frame_end - context.scene.frame_start + 1
        print("number of frames: ", end="");
        print(framecount)
        self.send_uint16_to_serial(val=framecount)
        time.sleep(0.25)

        # Send information on how many curves/timelines we will send:
        curvecount = len(all_curves_w_keyframes)
        print("number of curves: ", end="")
        print(curvecount)
        self.send_uint16_to_serial(val=curvecount)
        time.sleep(0.25)

        # Send the timeline data in packs of 100, wait a bit and continue:
        for curve in all_curves_w_keyframes:
            print(curve)
            valuessent = 0
            for i in all_curves_w_keyframes.get(curve):
                self.send_uint16_to_serial(val=i)
                valuessent += 1
                if valuessent % 100 == 0:
                    print("...");
                    time.sleep(0.75)
            print(valuessent, end="")
            print(" frames sent in total")
            time.sleep(0.75)
        print("done");
        return {"FINISHED"}

    # splits a 16-bit value into lower and higher bytes and 
    # sends it to Serial Device
    def send_uint16_to_serial(self, val):
        byte_low = round(val) & 0xff
        byte_high = (round(val) >> 8) & 0xff

        self.serial_device.write(bytes([byte_low]))
        self.serial_device.write(bytes([byte_high]))

    # sends the current framenumber to Serial Device
    def send_current_frame_to_serial(self, scene):
        v = currentScene.frame_current
        self.send_uint16_to_serial(v)
 


# Properties:
class PROPERTIES_DumpTimeline(bpy.types.PropertyGroup):
    def seriallist_callback(self, context):
        ports = serial.tools.list_ports.comports()
        enum_list = []
        for port in ports:
            p = (port.name, port.name, "")      # doesn't seem elegant to use the
                                                # port name as the identifier, but
                                                # i don't know how to access the
                                                # name otherwise
            enum_list.append(p)
        return enum_list

    serialports : bpy.props.EnumProperty(
        name="Serial Port",
        description="Please select Serial Device",
        items=seriallist_callback
    )

    custom_properties_list : bpy.props.StringProperty(name = "Props to send")



# Panel: the GUI that sits on the right side of the Graph Editor
class GRAPH_EDITOR_PT_DumpTimeline(bpy.types.Panel):
    bl_space_type = "GRAPH_EDITOR"  # editor type
    bl_region_type = "UI"           # region type
    bl_category = "Dump Timeline"   # name of tab group
    bl_label = "Settings"           # name of 

    def draw(self, context):
        # All UI Elements:
        # https://docs.blender.org/api/current/bpy.types.UILayout.html
        props = context.scene.dumpTimeline_props
        
        self.layout.prop(props, "serialports")      # Enum with SerialPort List

        self.layout.separator()                     # Separator

        if context.active_object is None:
            self.layout.label(text="please select an object")
        else:
            col = self.layout.column(align=True)
            col.label(text="Object: " + context.active_object.name)

            col.separator()
            col.label(text="Custom Properties to dump,")
            col.label(text="use Comma (,) as separator:")
            col.prop(props, "custom_properties_list")

            self.layout.operator("hardware.dump_timeline",
                text="Copy To Hardware")


def register():
    bpy.utils.register_class(PROPERTIES_DumpTimeline)
    bpy.utils.register_class(HARDWARE_OT_DumpTimeline)
    bpy.utils.register_class(GRAPH_EDITOR_PT_DumpTimeline)
    bpy.types.Scene.dumpTimeline_props = bpy.props.PointerProperty(type=PROPERTIES_DumpTimeline)


def unregister():
    bpy.utils.unregister_class(PROPERTIES_DumpTimeline)
    bpy.utils.unregister_class(HARDWARE_OT_DumpTimeline)
    bpy.utils.unregister_class(GRAPH_EDITOR_PT_DumpTimeline)
    del bpy.types.Scene.dumpTimeline_props



