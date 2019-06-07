#使用时import baidu_aip，调用其中的voice_recognize函数，将自动录音并识别，返回值为识别结果
from aip import AipSpeech
import wav2pcm,record,time
""" 你的 APPID AK SK """
APP_ID = '15455261'
API_KEY = 'piT7Qtn8InOVVwuIdfhLY4gI'
SECRET_KEY = 'obKt3CYfGOh7duezfqiBG2pFRZta255L'

client = AipSpeech(APP_ID, API_KEY, SECRET_KEY)
# 读取文件
def get_file_content(filePath):
    with open(filePath, 'rb') as fp:
        return fp.read()
def voice_recognize():


    record.rec('test1.wav')  #生成录音

    time_start = time.time()  #计时开始
    pcm_file = wav2pcm.wav_to_pcm('test1.wav')  #将wav转成pcm

    # 识别本地文件
    result=client.asr(get_file_content(pcm_file), 'pcm', 16000, {
        'dev_pid': 1536,
    })
    if(result.get("err_no")==0):
        time_end=time.time()  #计时结束
        res_str = '识别结果：%s,耗时%.2fs'%(result.get("result")[0],(time_end-time_start)) #截取结果
        wav2pcm.deletef(pcm_file)  #将此次识别的pcm文件删除

    else:
        res_str="识别失败"
        wav2pcm.deletef(pcm_file)  #将此次识别的pcm文件删除
    return result.get("result")[0]
