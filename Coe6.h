#include <fstream>
#include <iostream>
/*************************************************************
***  Constants used within the program 
***  
***
**************************************************************/
const int MAX_INVENTORY = 20000;

/*************************************************************
***  structures used in this program are defined 
***  here
***
**************************************************************/
typedef struct struct_VideoInfo
{
	char lpstrVideoTitle[50];
	char lpstrVideoActors[50];
	char lpstrVideoType[15];
	char lpstrVideoRating[5];
	int nVideoLength;
	int nVideoNumber;
} t_VideoInfo;

/*************************************************************
***  Classes used in this program are defined 
***  here
***
**************************************************************/

/*************************************************************
***  This class defines a video kept in the video store
***  
***
**************************************************************/

class cl_Video
{
private:
	char lpstrVideoTitle[50];
	char lpstrVideoActors[50];
	char lpstrVideoType[15];
	char lpstrVideoRating[5];
	int nVideoLength;
	int nVideoNumber;
	
public:
	// *******************************************
	// The following member functions get the values of private member variables
	//
	char *getVideoTitle();
	char *getVideoActors();
	char *getVideoType();
	char *getVideoRating();
	int getVideoLength();
	int getVideoNumber();
	
	// *******************************************
	// The following member functions set the values of private member variables
	//
	void setVideoTitle();
	void setVideoActors();
	void setVideoType();
	void setVideoRating();
	void setVideoLength();
	void setVideoNumber();
	
	//
	//
	//
	//

};

/*************************************************************
***  This class defines the video store
***  
***
**************************************************************/

class cl_VideoStore
{
private:
	cl_Video m_Video;
	t_VideoInfo m_VideoInfo;
	int n_recsWritten, n_recsRead, nCurrentRecord;
	bool b_matchFound;	
	char lpstrSearchTitle[50];
	FILE *pVideoDatabase;
	
public:
	cl_VideoStore();
	~cl_VideoStore();
	
	//
	// Method declarations for the Video Store object
	//
	void addVideo();
	void deleteVideo();
	void searchVideo();
	void listVideos();
	void searchHelper(char *);
	void writeVideo2DB();
};



