
import wave
import pyaudio
import numpy
import pylab
import record
#打开WAV文档，文件路径根据需要做修改
#record.rec('testwav.wav')
wf = wave.open("D:\\SRTP project\\test2.wav", "rb")
#创建PyAudio对象
p = pyaudio.PyAudio()
stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
channels=wf.getnchannels(),
rate=wf.getframerate(),
output=True)
nframes = wf.getnframes()
framerate = wf.getframerate()
str_data = wf.readframes(nframes)
wf.close()
#将波形数据转换为数组

# A new 1-D array initialized from raw binary or text data in a string.
wave_data = numpy.fromstring(str_data, dtype=numpy.short)
wave_data=wave_data/(2.**15)
wave_data.shape = -1,2
wave_data = wave_data.T
'''

#
'''
N=44100
start=0
df = framerate/(N-1) # 分辨率
freq = [df*n for n in range(0,N)] #N个元素
wave_data2=wave_data[0][start:start+N]
c=numpy.fft.fft(wave_data2)*2/N
d=int(len(c)/2)
time = numpy.arange(0,nframes)*(1.0/framerate)
#绘制波形图
pylab.figure(figsize=(8,4))
pylab.subplot(211)
pylab.plot(time, wave_data[0])
pylab.xlabel("time (seconds)")
#仅显示频率在18000以下的频谱
while freq[d]>18000:
 d-=10
pylab.subplot(212)
pylab.plot(freq[:d-1],abs(c[:d-1]))
pylab.show()
'''
print(df)
print(c.__sizeof__())

'''
print(nframes)
