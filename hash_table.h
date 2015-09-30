#include "table.h"
using namespace std;

//Josue Valverde, Homework #3, CS202

//hash index manages individual indices in the hash table and is derived from song_node
//for quick access to song lists
class hash_index: public song_node
{
	//public functions are described in detail in the cpp file
	public:
		hash_index(); //constructor
		hash_index(const hash_index & to_copy); //copy constructor

		bool add_song(song & to_add); //adds a song to the list
		bool connect_artist(hash_index & to_connect_to); //builds an adjacency between artists
		bool compare_artists(char * artist); //returns true if the indice's artist and the fed in artist match
		bool play_song(song *& song_bucket); //plays a random song in the index
		bool play_adjacent(song *& song_bucket); //plays an adjacent song to the fed in artist's index
		bool jump_artists(char *& artist); //changes the value of artists to be able to jump to the next adjacent artist
		void display();	//displays the songs in the index
		void display_artist(); //displays the artist of the index

	protected:
		void display_recursive(song_node *& head); //called by display() function above
		
		song_node * index_head;	//keeps hold of the head of the list of song nodes
		hash_index * related_artist; //points to an adjacent artist
		char * artist_name; //keeps track of the indice's artist
		int num_songs; //keeps track of how many songs there are in the list, for random-song-choosing purposes
};

//hash table manages the entire data structure
class hash_table
{
	//public functions are described in further detail in cpp file
	public:
		hash_table(); //constructor
		hash_table(const hash_table & to_copy); //copy constructor

		bool load_songs(); //builds the hash table
		bool hash_and_add(song & to_add); //hashes the artist's name in to_add and stores in appropriate index
		bool search_artist(char *& artist, song *& song_bucket); //searches for an artist by name, and returns one of their songs through song_bucket
		bool play_adjacent(char *& artist, song *& song_bucket); //plays a song of an adjacent artist's
		void display(); //displays the whole table
		void display_artists(); //displays all the artists

		friend ostream& operator << (ostream&, hash_table&); //displays all the table
		friend istream& operator >> (istream&, hash_table&); //inserts a song into the table based on artist name value
		bool operator == (char *); //checks to see if the artist has a song in the table

	protected:
		hash_index * table_array; //manages an array of hash indices
};
