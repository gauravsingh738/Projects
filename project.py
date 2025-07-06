import tkinter as tk
import requests
import time
from tkinter import messagebox

# Function to fetch weather details
def getWeather(event=None):
    city = textField.get().strip()
    if not city:
        messagebox.showwarning("Input Error", "Please enter a city name.")
        return

    api = f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid=06c921750b9a82d8f5d1294e1586276f"

    try:
        json_data = requests.get(api).json()
        if json_data['cod'] != 200:
            raise ValueError(json_data.get('message', 'Error fetching data'))

        # Extract weather data
        condition = json_data['weather'][0]['main']
        temp = int(json_data['main']['temp'] - 273.15)
        min_temp = int(json_data['main']['temp_min'] - 273.15)
        max_temp = int(json_data['main']['temp_max'] - 273.15)
        pressure = json_data['main']['pressure']
        humidity = json_data['main']['humidity']
        wind = json_data['wind']['speed']
        timezone_offset = json_data['timezone']
        sunrise = time.strftime('%I:%M:%S %p', time.gmtime(json_data['sys']['sunrise'] + timezone_offset))
        sunset = time.strftime('%I:%M:%S %p', time.gmtime(json_data['sys']['sunset'] + timezone_offset))

        # Weather condition icons
        weather_icons = {
            "Clear": "☀️", "Clouds": "☁️", "Rain": "🌧️",
            "Drizzle": "🌦️", "Thunderstorm": "⛈️",
            "Snow": "❄️", "Mist": "🌫️"
        }
        icon = weather_icons.get(condition, "🌈")

        # Format display
        final_info = f"{icon} {condition}\n{temp}°C"
        final_data = (
            f"🌡️ Min Temp: {min_temp}°C\n"
            f"🌡️ Max Temp: {max_temp}°C\n"
            f"💧 Humidity: {humidity}%\n"
            f"🧭 Pressure: {pressure} hPa\n"
            f"🌬 Wind Speed: {wind} m/s\n"
            f"🌅 Sunrise: {sunrise}\n"
            f"🌇 Sunset: {sunset}"
        )

        label1.config(text=final_info)
        label2.config(text=final_data)

    except Exception as e:
        label1.config(text="")
        label2.config(text="")
        messagebox.showerror("Error", f"Could not retrieve weather data.\n\n{e}")

# Setup main window
canvas = tk.Tk()
canvas.geometry("650x600")
canvas.title("🌤️ Weather App")
canvas.configure(bg="#d4f1f4")  # Soft sky background

# Fonts
font_header = ("Poppins", 28, "bold")
font_prompt = ("Poppins", 16, "bold")
font_input = ("Poppins", 22)
font_weather_main = ("Poppins", 30, "bold")
font_weather_details = ("Poppins", 14)
font_footer = ("Poppins", 10, "italic")

# Header
header = tk.Label(canvas, text="🌤️ Weather App", font=font_header, bg="#d4f1f4", fg="#003e5c")
header.pack(pady=(20, 5))

# Instruction Label
prompt_label = tk.Label(canvas, text="Enter the City Name", font=font_prompt, bg="#d4f1f4", fg="#003e5c")
prompt_label.pack()

# Entry Field
textField = tk.Entry(canvas, justify='center', width=22, font=font_input, bg="#ffffff", fg="#003e5c", relief="solid", bd=2)
textField.pack(pady=10)
textField.focus()
textField.bind('<Return>', getWeather)

# Output Frame
output_frame = tk.Frame(canvas, bg="#ffffff", bd=2, relief="groove", padx=30, pady=20)
output_frame.pack(pady=30)

label1 = tk.Label(output_frame, font=font_weather_main, bg="#ffffff", fg="#2e7d32")
label1.pack(pady=(0, 12))

label2 = tk.Label(output_frame, font=font_weather_details, bg="#ffffff", fg="#333333", justify="left")
label2.pack()

# Footer
footer = tk.Label(canvas, text="⚡ Powered by OpenWeatherMap", font=font_footer, bg="#d4f1f4", fg="#555")
footer.pack(side="bottom", pady=10)

# Run App
canvas.mainloop()
