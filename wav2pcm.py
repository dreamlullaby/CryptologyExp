# wav2pcm.py 文件内容
# wav to pcm
import os

def wav_to_pcm(wav_file):
    # 假设 wav_file = "音频文件.wav"
    # wav_file.split(".") 得到["音频文件","wav"] 拿出第一个结果"音频文件"  与 ".pcm" 拼接 等到结果 "音频文件.pcm"
    pcm_file = "%s.pcm" %(wav_file.split(".")[0])
    cmd2=r"D:\FFmpeg\bin\ffmpeg -i %s -f s16le -ac 1 -ar 16000 -acodec pcm_s16le %s"%(wav_file,pcm_file)
    # 就是此前我们在cmd窗口中输入命令,这里面就是在让Python帮我们在cmd中执行命令
    os.system(cmd2)



    return pcm_file

def deletef(pcm_file):
    os.system("del %s"%pcm_file)
