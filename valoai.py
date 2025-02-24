from termcolor import colored
import numpy as np
import win32gui, win32ui, win32con
import torch
import serial
import time
import keyboard
import pathlib
from pathlib import Path
pathlib.PosixPath = pathlib.WindowsPath
print(colored('''     _    _     _
    | |  / /_ _| |   ___   __ _ _
    | | / / _` | |  / _ \ / _` | |
    | |/ / (_| | |_| (_) | (_| | |
    |___/ \__,_|____\___/ \__,_|_|''', "magenta",attrs=['bold']))
fov = 320
mid = fov / 2
model = torch.hub.load('v/scripts/yolov5-master', 'custom', path='v/scripts/best640.pt', source='local', force_reload=True).cuda()
if torch.cuda.is_available():
    print(colored("CUDA ACCELERATION [ENABLED]", "green"))
ard = serial.Serial("COM3", 9600, writeTimeout=0)
def calculatedistance(x, y):
    code = f"{x:.2f},{y:.2f}*"
    ard.write(str.encode(code))
    time.sleep(0.03)
def windowcapture():
    hwnd = None
    wDC = win32gui.GetWindowDC(hwnd)
    dcObj = win32ui.CreateDCFromHandle(wDC)
    cDC = dcObj.CreateCompatibleDC()
    dataBitMap = win32ui.CreateBitmap()
    dataBitMap.CreateCompatibleBitmap(dcObj, fov, fov)
    cDC.SelectObject(dataBitMap)
    cDC.BitBlt((0, 0), (fov, fov), dcObj, (800, 380), win32con.SRCCOPY)
    signedIntsArray = dataBitMap.GetBitmapBits(True)
    img = np.frombuffer(signedIntsArray, dtype='uint8').reshape((fov, fov, 4))
    dcObj.DeleteDC()
    cDC.DeleteDC()
    win32gui.ReleaseDC(hwnd, wDC)
    win32gui.DeleteObject(dataBitMap.GetHandle())
    return img
print('Running!')
while True:
    sct_img = windowcapture()
    results = model(sct_img, size=320)
    df = results.pandas().xyxy[0]
    if not df.empty:
        xmin, ymin, xmax, ymax = df.iloc[0, :4]
        cX = (xmin + xmax) / 2
        cY = (ymin + ymax) / 2
        x = cX - mid if cX > mid else -(mid - cX)
        y = cY - mid if cY > mid else -(mid - cY)
        if keyboard.is_pressed('Alt'):
            calculatedistance(x, y)
