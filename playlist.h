#include "hash_table.h"
using namespace std;

//Josue Valverde, Homework #3, CS202

//playlist that manages all the songs a user has liked
class playlist: public song_node
{
	//public functions are described in more detail in cpp file
	public:
		playlist(); //default constructor
		playlist(const playlist & to_copy); //copy constructor

		bool add_song(song *& song_bucket); //adds the song in the song_bucket to the list
		bool play_song(); //plays a random song in the list and removes it if the user doesn't like it
		void display(); //displays all the songs in the list

 		friend ostream& operator << (ostream&, playlist&); //displays songs
		friend istream& operator >> (istream&, playlist&); //inserts a new song
		playlist& operator -= (song&);	//removes a song that matches what the user feeds in

	private:
		bool add_recursive(song *& song_bucket, song_node *& rear); //alled by display function above
	
		song_node * playlist_rear; //keeps hold of the rear of the playlist
		int num_songs; //keeps track of how many songs there are in the playlist
};
