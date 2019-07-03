/**********************************************************************************************************
** 文件名		:H264FrameLiveSource.hh
** 作者			:maxlicheng<licheng.chn@outlook.com>
** 作者github		:https://github.com/maxlicheng
** 作者博客		:https://www.maxlicheng.com/	
** 生成日期		:2019-07-01
** 描述			:uvc设备操作及x264编码参数设置头文件
************************************************************************************************************/
#ifndef _H264FRAMEDLIVESOURCE_HH
#define _H264FRAMEDLIVESOURCE_HH
#include <FramedSource.hh>
#include <UsageEnvironment.hh>
#include "encoder_define.hh"

#define WIDTH                   640
#define HEIGHT                  480
#define widthStep              960
#define FILE_VIDEO      	"/dev/video4"		//设备名

class Device
{
public:
    void init_mmap(void);
    void init_camera(void);
    void init_encoder(void);
    void open_camera(void);
    
    void close_camera(void);
    void read_one_frame(void);
	void getnextframe(void);
    void start_capture(void);
    void stop_capture(void);
    void close_encoder(); 
    int  camera_able_read(void);
    void compress_begin(Encoder *en, int width, int height);
    int  compress_frame(Encoder *en, int type, char *in, int len, char *out);
    void compress_end(Encoder *en);
    void Init();
	void intoloop();
    void GetNextFrame();
    void Destory();
public:
    int fd;
	FILE *save_fd;
    int n_nal;
    int frame_len;
	char *h264_buf;
	unsigned int n_buffer;
	Encoder en;
	FILE *h264_fp;
    BUFTYPE *usr_buf;
	FILE *pipe_fd;
};
#endif


