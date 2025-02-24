# 🎯 VALOAI – AI-Powered Aim Assist for Valorant  

VALOAI is a **real-time AI-driven aim assist** that leverages **object detection** with CUDA acceleration on Nvidia GPUs. Designed for **smooth, precise targeting**, VALOAI helps users achieve **instant headshots** without modifying game files.  

> **Unlike other aim assists, which charge €5/month or €100 for lifetime access without offering any real advantages, VALOAI is completely FREE! <3**  

> ⚠️ **For educational purposes only. The developers are not responsible for any misuse.**

![capture](https://github.com/user-attachments/assets/a2f6f9f7-64ed-4b29-97c7-d3d3e02c27e4)

---

## 🔥 Why Use VALOAI?  

✔ **100% Free** – No subscriptions, no hidden fees  
✔ **Undetectable** – No game memory modifications 🛡️  
✔ **AI-Powered Accuracy** – YOLOv5-based real-time detection 🎯  
✔ **Hardware-Based Execution** – Uses **Arduino Leonardo + USB Host Shield 2.0** 🔌  
✔ **Optimized for Performance** – CUDA-accelerated for fast, efficient processing 🚀  

### 🖥️ System Requirements  
- **Minimum**: GTX 1650  
- **Recommended**: RTX 2060  

---

## ⚙️ Installation Guide  

### 🔹 1. Setting Up Arduino  
1. Install **Arduino Legacy IDE 1.8.19**  
2. Install **USB Host Shield 2.0** libraries  
3. Open `mouse/mouse.ino`  
4. Modify these values to match your **mouse X and Y ID** (values from 0-9):  

   ```cpp
   buttons = buf[0];
   xm = buf[1];
   ym = buf[2];
   scr = buf[3];
   ```

5. Upload the script to your **Arduino Leonardo** and test until everything matches your mouse input  

### 🔹 2. Installing Dependencies  
1. Install **Python 3.9** (recommended) or later  
2. Install **CUDA 12.1**  
3. Install **PyTorch** with CUDA 12.1 support:  

   ```bash
   pip install torch==2.3.1 torchvision==0.18.1 torchaudio==2.3.1 --index-url https://download.pytorch.org/whl/cu121
   ```  

4. Navigate to `v/scripts/yolov5-master`, open **Command Prompt**, and run:  

   ```bash
   pip install -r requirements.txt
   ```  

5. Install additional dependencies:  

   ```bash
   pip install pyserial  
   pip install pywin32  
   pip install keyboard  
   ```

---

## 🎮 How To Use  

1. Open the script and update the **serial COM port**:  

   ```python
   ard = serial.Serial("COM3", 9600, writeTimeout=0)
   ```  

   Replace `"COM3"` with your **Arduino's current COM port** (e.g., `"COM4"`, `"COM5"`).  

2. **Optimize your settings for best accuracy**:  
   - **Set Windows mouse sensitivity** to **default** (6/11)  
   - **Set in-game sensitivity** to **1.1** for **1:1 tracking**  
   - **Use Windowed Fullscreen mode** for optimal performance
   - **Change enemy highlight color to purple**  

3. Run the `.py` file  
4. Press **ALT** to trigger **instant aim assist**  

---

## ⚠️ Detection & Ban Risks  

🛡️ **VALOAI is currently undetected** as it does **not** modify game files or memory. However, there are still potential risks:  

- **Hardware-Based Detection** – The anti-cheat system could flag **Arduino Leonardo boards**, but this is unlikely since it acts like a standard mouse.  
- **Manual Reports** – If you receive too many reports, Riot may manually investigate and issue a ban. **Use responsibly!**  

---

## 🌍 Open Source & Contributions  

This project is **open-source**, and contributions are welcome! Feel free to **fork, improve, and submit pull requests**.

---

## 📜 License  

This project is released under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE) file for details.  

---

🔥 **VALOAI** 🔥  
