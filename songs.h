#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include "time.h"

//Josue Valverde, Homework #3, CS202

const int HASH_TABLE_SIZE = 101;	//constant hash table size, no collisions

class song_node; //declaring song node since song has some data that needs it

//song class just manages song name, artist, and time
class song
{
	//functions are described in more detail in cpp file
	public:
		song(); //default constructor
		song(const song & to_copy); //copy constructor
		song(const char * new_name, const char * new_artist, const char * new_time); //constructor with arguments
		~song(); //destructor

		bool copy_song(song & song_data, song & to_copy); //copies to_copy's info int song_data's info
		bool copy_artist_name(char *& artist_name); //copies the fed in artist name into song's own artist
		bool compare(song & to_compare); //returns true if the fed in song and the current song have matching data
		int hash(); //returns an integer based on the hashed value of the artist name
		void display(); //displays the song's contents

	protected:
		char * name; //song's name
		char * artist; //song's artist name
		char * time; //length of song
};

//manages a song node
class song_node: public song
{
	//functions are described in more detail in cpp file
	public:
		song_node(); //constructor
		song_node(song_node & to_copy); //copy constructor
		song_node(song & to_copy); //constructor with song argument
		song_node(const char * title, const char * artist, const char * time); //constructor with raw data arguments
		~song_node(); //destructor

		bool retrieve_song(song *& song_bucket); //returns it's song_data through the song_bucket
		bool compare(song & song_bucket); //calls the song's compare function
		song_node*& get_next(song_node *& head); //returns a pointer to the next song node in the list
		void display_song(); //displays node data

	protected:
		song song_data; //contains the raw song data
		song_node * next; //pointer to another song node
};


