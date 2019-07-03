/**********************************************************************************************************
** 文件名		:H264VideoStreamer.cpp
** 作者			:maxlicheng<licheng.chn@outlook.com>
** 作者github		:https://github.com/maxlicheng
** 作者博客		:https://www.maxlicheng.com/	
** 生成日期		:2019-07-01
** 描述			:live直播程序/单播
************************************************************************************************************/
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include <H264FramedLiveSource.hh>
#include <sys/types.h>  
#include <sys/stat.h> 

UsageEnvironment* env;
char const* inputFileName = "/tmp/fifo";
char *ptr;
class Device Camera; 

// To make the second and subsequent client for each stream reuse the same
// input stream as the first client (rather than playing the file from the
// start for each client), change the following "False" to "True":
Boolean reuseFirstSource = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName); // fwd

int main(int argc, char** argv) {
	// Begin by setting up our usage environment:
	TaskScheduler* scheduler = BasicTaskScheduler::createNew();
	env = BasicUsageEnvironment::createNew(*scheduler);

	UserAuthenticationDatabase* authDB = NULL;
#ifdef ACCESS_CONTROL
	// To implement client access control to the RTSP server, do the following:
	authDB = new UserAuthenticationDatabase;
	authDB->addUserRecord("username1", "password1"); // replace these with real strings
	// Repeat the above with each <username>, <password> that you wish to allow
	// access to the server.
#endif
	
	//打开摄像头
	Camera.Init();
	mkfifo(inputFileName, 0777);
	if(0 == fork())
	{
		Camera.pipe_fd = fopen(inputFileName, "w");
		if(NULL == Camera.pipe_fd)
		{
			printf("===============child process open pipe err =======\n ");
		}
		while(1)
		{
			usleep(15000);
			Camera.getnextframe();
		}

	}

	// Create the RTSP server:
	RTSPServer* rtspServer = RTSPServer::createNew(*env, 8554, authDB);
	if (rtspServer == NULL) {
		*env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
		exit(1);
	}

	char const* descriptionString
	= "Session streamed by \"testOnDemandRTSPServer\"";

	// A H.264 video elementary stream:
	char const* streamName = "live";
	ServerMediaSession* sms
		= ServerMediaSession::createNew(*env, streamName, streamName,
					  descriptionString);
	sms->addSubsession(H264VideoFileServerMediaSubsession
			   ::createNew(*env, inputFileName, reuseFirstSource));
	rtspServer->addServerMediaSession(sms);

	announceStream(rtspServer, sms, streamName, FILE_VIDEO);

/*  
	if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080)) {
    		*env << "\n(We use port " << rtspServer->httpServerPortNum() << " for optional RTSP-over-HTTP tunneling.)\n";
  	} else {
    		*env << "\n(RTSP-over-HTTP tunneling is not available.)\n";
  	}
*/

  	env->taskScheduler().doEventLoop(); // does not return
  
  	Camera.Destory();

  	return 0; // only to prevent compiler warning
}

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName) {
	char* url = rtspServer->rtspURL(sms);
	UsageEnvironment& env = rtspServer->envir();
	env << "\n\"" << streamName << "\" stream, from the file \""
	  << inputFileName << "\"\n";
	env << "Play this stream using the URL \"" << url << "\"\n";
	delete[] url;
}



