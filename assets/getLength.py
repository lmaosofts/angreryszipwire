import wave

def main(file_path):
	with wave.open(file_path,"rb") as wav:return wav.getnframes()/float(wav.getframerate())

length = main("logoFart.wav")
print(f"Length of WAV file: {length:.100f} seconds")