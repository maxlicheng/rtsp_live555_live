/**********************************************************************************************************
** 文件名		:encoder_define.hh
** 作者			:maxlicheng<licheng.chn@outlook.com>
** 作者github		:https://github.com/maxlicheng
** 作者博客		:https://www.maxlicheng.com/	
** 生成日期		:2019-07-01
** 描述			:x264编码头文件
************************************************************************************************************/
#ifndef _ENCODER_DEFINE_HH
#define _ENCODER_DEFINE_HH


extern "C" {
#include <stdint.h>
#include <x264.h>

	typedef struct 
	{
		x264_param_t *param;
		x264_t *handle;
		x264_picture_t *picture; 
		x264_nal_t *nal;
	} Encoder;

	typedef struct
	{
	    char *start; 
	    int length;
	}BUFTYPE;

}

#endif


