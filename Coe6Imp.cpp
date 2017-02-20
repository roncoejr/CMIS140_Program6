#define TRUE 1
#define FALSE 0


#include <iostream>
#include "Coe6.h";




using namespace std;

void caseConverter(char *);
/*
* Method implementations for the Video class begin below this comment area.
*
*
*
*
*/

// *****************************************************
// This method gets the video title
//
//
char *cl_Video::getVideoTitle()
{

	return lpstrVideoTitle;
}

// *****************************************************
// This method gets the video actors
//
//
char *cl_Video::getVideoActors()
{

	return lpstrVideoActors;
}


// *****************************************************
// This method gets the video type
//
//
char *cl_Video::getVideoType()
{

	return lpstrVideoType;
}


// *****************************************************
// This method gets the video rating
//
//
char *cl_Video::getVideoRating()
{

	return lpstrVideoRating;
}


// *****************************************************
// This method gets the video length
//
//
int cl_Video::getVideoLength()
{

	return nVideoLength;
}


// *****************************************************
// This method gets the video number
//
//
int cl_Video::getVideoNumber()
{

	return nVideoNumber;
}

// *****************************************************
// This method sets the video title
//
//
void cl_Video::setVideoTitle()
{
	cout << "Please enter the Video Name: ";
	gets(lpstrVideoTitle);
}

// *****************************************************
// This method handles setting the actors for the video
//
//
void cl_Video::setVideoActors()
{
	cout << "Please enter the Video Actors: ";
	gets(lpstrVideoActors);
}

// *****************************************************
// This method handles setting the video type
//
//
void cl_Video::setVideoType()
{
	cout << "Please enter the Video Type: ";
	gets(lpstrVideoType);
}

// *****************************************************
// This method handles setting the video rating
//
//
void cl_Video::setVideoRating()
{
	cout << "Please enter the Video Rating: ";
	gets(lpstrVideoRating);
}

// *****************************************************
// This method handles setting the video length
//
//
void cl_Video::setVideoLength()
{
	cout << "Please enter the Video Length: ";
	cin >> nVideoLength;
}

// *****************************************************
// This method handles setting the video number
//
//
void cl_Video::setVideoNumber()
{
	cout << "Please enter the Video Number: ";
	cin >> nVideoNumber;
}


/*
* Method implementations for the VideoStore class begin below this comment area.
*
*
*
*
*/


// *****************************************************
// The constructor for the Video Store object gets things setup so that the database can be used
//
//
cl_VideoStore::cl_VideoStore()
{
	if((pVideoDatabase = fopen("dbFile.DAT", "rb")) == NULL)  // If the database cannot be opened for reading we will create a new one
	{
		cout << "Cannot open the video database file" << endl << endl;
		cout << "Attempting to create the Video Database" << endl << endl;
		if((pVideoDatabase = fopen("dbFile.DAT", "wb")) != NULL)
			cout << "Video Database Created Successfully" << endl << endl;
		else
			cout << "Fatal error.  The Video Database could not be created." << endl << endl;
	}
	else
	{
			cout << "Video Database Opened Successfully." << endl << endl;  // We found the database and opened it successfully.
	}
}

// *****************************************************
// The destructor for the Video Store class makes sure things are clean before the program completely shuts down.
//
//
cl_VideoStore::~cl_VideoStore()
{
	fflush(pVideoDatabase);
	if(pVideoDatabase != NULL)
		fclose(pVideoDatabase);
}

// *****************************************************
// This method is used to add a video to the database
//
//
void cl_VideoStore::addVideo()
{
	m_Video.setVideoTitle();
	m_Video.setVideoActors();
	m_Video.setVideoType();
	m_Video.setVideoRating();
	m_Video.setVideoLength();
	writeVideo2DB();
}

// *****************************************************
// This method is used to delete a video from the database
//
//
void cl_VideoStore::deleteVideo()
{

	t_VideoInfo temp_VideoDB[200];
	int i = -1, j = -1;
	bool b_foundDeletion = FALSE;
		
	cout << "What Video Title would you like to delete: ";
	gets(lpstrSearchTitle);
	
	searchHelper(lpstrSearchTitle);
	
	if(b_matchFound)  // If we found a match it makes sense to continue with the logic that performs the delete operation
	{
		i++;
		while(!feof(pVideoDatabase))  // If we haven't reached the end of the file keeep reading records into the array
		{
			if(i != nCurrentRecord)  // If this isn't the deleted record then add the record to the array that will supply the new database
			{
				n_recsRead = fread(&temp_VideoDB[i], sizeof(temp_VideoDB[i]), 1, pVideoDatabase);
				i++;
			}
			else
			{
				n_recsRead = fread(&m_VideoInfo, sizeof(m_VideoInfo), 1, pVideoDatabase);
				b_foundDeletion = TRUE;
				nCurrentRecord = 25;
			}
				
		}
		
		fclose(pVideoDatabase);
		pVideoDatabase = fopen("dbFile.DAT", "wb");  // Create a new database file in preparation for the array to be written, minus the deleted record
		
		for(j=0; j<i-1; j++)
			n_recsWritten = fwrite(&temp_VideoDB[j], sizeof(temp_VideoDB[j]), 1, pVideoDatabase);
			
		fclose(pVideoDatabase);
		cout << j << " records written to the database." << endl << endl;
		
		pVideoDatabase = fopen("dbFile.DAT", "rb");
	}
	
}

// *****************************************************
// This function allows the user to search for a video by title
//
//
void cl_VideoStore::searchVideo()
{
	
	b_matchFound = FALSE;
	
	cout << "What Video Title would you like to search for: ";
	gets(lpstrSearchTitle);
	
	searchHelper(lpstrSearchTitle);
	
	
}

// *****************************************************
// This method provides a list of all videos in the database
//
//
void cl_VideoStore::listVideos()
{

	n_recsRead = fread(&m_VideoInfo, sizeof(m_VideoInfo), 1, pVideoDatabase);

	//
	// Output the video information header line.
	//
	cout << "Video Title" << "\t" << "Video Actors" << "\t" << "Video Type" << "\t" << "Video Rating";
	cout << "\t" << "Video Length" << endl << endl;
	
	while(!feof(pVideoDatabase))  // If we haven't reached the end of the file keep on listing videos
	{
		cout << m_VideoInfo.lpstrVideoTitle << "\t" << m_VideoInfo.lpstrVideoActors << "\t" << m_VideoInfo.lpstrVideoType << "\t" << m_VideoInfo.lpstrVideoRating;
		cout << "\t" << m_VideoInfo.nVideoLength << endl;
		n_recsRead = fread(&m_VideoInfo, sizeof(m_VideoInfo), 1, pVideoDatabase);
	}
	
	if(!fseek(pVideoDatabase, 0, SEEK_SET))
		cout << endl << "File marker returned to the beginning of the database." << endl << endl;
	
	
}

// *****************************************************
// This method is used to write changes to the database
//
//
void cl_VideoStore::writeVideo2DB()
{
	//
	// This code copies strings from a temporary structure into the appropriate instance of the Video class
	//
	//
	strcpy(m_VideoInfo.lpstrVideoTitle, m_Video.getVideoTitle());
	strcpy(m_VideoInfo.lpstrVideoActors, m_Video.getVideoActors());
	strcpy(m_VideoInfo.lpstrVideoType, m_Video.getVideoType());
	strcpy(m_VideoInfo.lpstrVideoRating, m_Video.getVideoRating());
	m_VideoInfo.nVideoLength = m_Video.getVideoLength();
	
	if(pVideoDatabase != NULL)  // Ensure that we have a valid file pointer before trying to write to the database
	{
		fclose(pVideoDatabase);
		if((pVideoDatabase = fopen("dbFile.DAT", "a+")) != NULL)
		{
			n_recsWritten = fwrite(&m_VideoInfo, sizeof(m_VideoInfo), 1, pVideoDatabase);
			fclose(pVideoDatabase);
			pVideoDatabase = fopen("dbFile.DAT", "rb");
		}
		else
			cout << "Failed to open the file for writing." << endl << endl;
	}
		
	cout << "Wrote " << n_recsWritten << " records to the database." << endl << endl;
	
}

// *****************************************************
// This function provides the search functionality for programs that use the Video Store object type
//
//
void cl_VideoStore::searchHelper(char *searchClause)
{
	
	b_matchFound = FALSE;
	caseConverter(searchClause);
	
	n_recsRead = fread(&m_VideoInfo, sizeof(m_VideoInfo), 1, pVideoDatabase);
	
	if(n_recsRead >= 1)  // If we have read at least one record then it makes sense to proceed with the matching logic
	{
		nCurrentRecord = -1;
		do
		{
			nCurrentRecord++;
			caseConverter(m_VideoInfo.lpstrVideoTitle);
			if(!strcmp(searchClause, m_VideoInfo.lpstrVideoTitle))
			{
				b_matchFound = TRUE;
			}
			else
			{
				n_recsRead = fread(&m_VideoInfo, sizeof(m_VideoInfo), 1, pVideoDatabase);
			}
				
		} while(!feof(pVideoDatabase) && !b_matchFound);
		
	}
	
	if(b_matchFound)  // When a search match is found, output all of the pertinent information
	{
		cout << endl << endl;
		cout << m_VideoInfo.lpstrVideoTitle << "\t" << m_VideoInfo.lpstrVideoActors << "\t" << m_VideoInfo.lpstrVideoType << "\t" << m_VideoInfo.lpstrVideoRating;
		cout << "\t" << m_VideoInfo.nVideoLength << endl << endl;	
	}
	else
		cout << endl << "No matching records were found." << endl << endl;
	
	fseek(pVideoDatabase, 0, SEEK_SET);
	
}


// **************************
//
// Utility Functions are defined here

// **********************************************
// This function will handle string case conversion for the program
//
void caseConverter(char *text2Convert)
{
	int i = 0;
	
	while(text2Convert[i] != '\0')
	{
		text2Convert[i] = toupper(text2Convert[i]);  // Replace each character in the string with its upper case equivalent.
		i++;
	}
	
}