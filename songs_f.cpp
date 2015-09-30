#include "songs.h"
using namespace std;

//Josue Valverde, Homework #3, CS202
/****************************************SONG CLASS*******************************/

//Default Contructor
song::song()
{
	name = NULL;
	artist = NULL;
	time = NULL;
}

//Copy Constructor
song::song(const song & to_copy)
{

	name = new char[strlen(to_copy.name) + 1];
	strcpy(name, to_copy.name);

	artist = new char[strlen(to_copy.artist) + 1];
	strcpy(artist, to_copy.artist);

	time = new char[strlen(to_copy.time) + 1];
	strcpy(time, to_copy.time);

}

//Constructor with arguments, creates a new object with the data fed in (name, artist, and length of the song)
song::song(const char * new_name, const char * new_artist, const char * new_time)
{
	if(new_name)
	{
		name = new char[strlen(new_name) + 1];
		strcpy(name, new_name);
	}

	if(new_artist)
	{
		artist = new char[strlen(new_artist) + 1];
		strcpy(artist, new_artist);
	}

	if(new_time)
	{
		time = new char[strlen(new_time) + 1];
		strcpy(time, new_time);
	}
}

//copies to_copy's information into song_data's information; this is needed when a song needs to be copied into another object that is not being pointed to
bool song::copy_song(song & song_data, song & to_copy)
{
	song_data.name = new char[strlen(to_copy.name) + 1];
	strcpy(song_data.name, to_copy.name);

	song_data.artist = new char[strlen(to_copy.artist) + 1];
	strcpy(song_data.artist, to_copy.artist);

	song_data.time = new char[strlen(to_copy.time) + 1];
	strcpy(song_data.time, to_copy.time);
}

//copies the fed in name into the current object's artist name
bool song::copy_artist_name(char *& artist_name)
{
	if(artist_name)
		return false;

	artist_name = new char[strlen(artist) + 1];
	strcpy(artist_name, artist);
}

//compares current song object to fed in object and returns true if they hold the same information
bool song::compare(song & to_compare)
{
	if(strcmp(name, to_compare.name) == 0)
		return true;

	return false;
}

//song destructor
song::~song()
{
	if(name)
		delete [] name;

	if(artist)
		delete [] artist;

	if(time)
		delete [] time;
}

//returns an integer based on the hash value of the current object's artist name (this is used for adding to the hash table)
int song::hash()
{
	int key = 0;

	if(!artist)
		return key;
	
	for(int i = 0; i < strlen(artist); ++i)
		key += (artist[i] * 33) ^ 19;

	return key;	
}

//displays the song's information
void song::display()
{
	cout << "Song: " << name << endl;
	cout << "Artist: " << artist << endl;
	cout << "Time: " << time << endl << endl;
}

/******************************SONG NODE CLASS****************************/
//Default constructor
song_node::song_node()
{
	next = NULL;
}

//copy constructor
song_node::song_node(song_node & to_copy)
{
	song_data.copy_song(song_data, to_copy.song_data);
}

//Constructor with arguments
//Copies a song into it's song data
song_node::song_node(song & to_copy)
{
	copy_song(song_data, to_copy);	
	next = NULL;
}

//Initialization list for song
song_node::song_node(const char * title, const char * artist, const char * time): song_data(title,artist,time)
{

}

//Destructor
song_node::~song_node()
{
	next = NULL;
}

//Displays the song node's song data
void song_node::display_song()
{
	song_data.display();	
}

//returns the song data in the song node through the song_bucket argument
bool song_node::retrieve_song(song *& song_bucket)
{
	if(song_bucket)
		delete song_bucket;

	song_bucket = new song(song_data);
	return true;
}

//calls song's compare fucntion to see if song_bucket has the same data as it's own
bool song_node::compare(song & song_bucket)
{
	return song_data.compare(song_bucket);
}

//returns a pointer to the next song node
song_node*& song_node::get_next(song_node * & head)
{
	if(!head)
		return head;

	else
		return head -> next;
}
