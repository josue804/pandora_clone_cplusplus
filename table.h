#include "songs.h"
using namespace std;

//Josue Valverde, Homework #3, CS202

//Manages a list of song nodes
class song_list: public song_node
{
	public:
		song_list(); //default constructor
		song_list(const song_list & to_copy); //copy constructor
		
		bool add_song(const char * title, const char * artist, const char * time); //adds a song to the list using the fed in arguments
		void display();	//displays list

	protected:
		song_node * list_head; //holds on the lit of song nodes

		void display_recursive(song_node * & head); //called by display function above
};


class genre; //genre declaration since it is used before it is declared

//manages an node that points to an adjacent genre
class adj_node
{
	public:
		adj_node(); //default constructor
		adj_node(const adj_node & to_copy); //copy constructor
		adj_node(genre & to_point_to); //constructor with a genre argument; this node will point to that genre

		bool update_genre(const char * new_genre); //updates the name of the genre
		adj_node*& get_next(adj_node *& head); //returns a pointer to the next adjacency node
		bool play_adjacent(song *& song_bucket); //plays a random song of the adjacent genre that it's pointing to
		void display(); //displays the name of the genre it's pointing to

	protected:
		adj_node * next; //pointer to another adj node
		genre * adj_genre; //pointer to an adjacent genre
		char * genre_name; //keeps track of what genre it's pointing to
		
};

//manages a list of adj_nodes
class adj_list: public adj_node
{
	public:
		adj_list(); //default constructor
		adj_list(const adj_list & to_copy); //copy constructor
		bool add_node(genre & to_point_to); //adds a node the list
		bool play_adjacent(int num_adj, song *& song_bucket); //calls a random adj_node's play_adjacent function
		void display(); //displays all the genres that the list is pointing to

	protected:
		adj_node * head; //keeps hold of the adjacency list
		
		bool add_node_recursive(genre & to_point_to, adj_node *& head); //called by add_node above
		void display_recursive(adj_node *& head); //called by display above

};

//manages a list of songs and a list of adjacency nodes
class genre: public song_list
{
	public:
		genre(); //default constructor
		genre(const genre & to_copy); //copy constructor

		bool new_name(const char * to_copy); //updates the name of te genre
		bool assign_name(char *& name_bucket); //copies a name of it's own genre into name_bucket
		bool update_num_songs(int number_of_songs); //updates the number of songs in the genre
		bool add_adj_node(genre & to_point_to); //adds a node to it's adjacency list
		
		bool play_song(song *& song_played); //plays a random song from it's song list
		bool play_adjacent(song *& song_played); //plays a random adjacent song from it's adjacency list
		bool remove(song & song_bucket); //removes a song that matches the song_buckets data
		void display_adj_list(); //displays the adjacency list
		void display_genre(); //displays what the current genre is

	protected:
		song_list songs; //list of song-nodes object
		adj_list * head; //keeps hold of the adjacency list

		char * genre_name; //keeps track of what genre it is
		int num_adj; //keeps hold of how many adjacent nodes it has
		int num_songs; //keeps track of how many songs it has in its list

};

//an adjacency table of genres
//table manages an array of genres
class table
{
	public:
		table();//default constructor
		table(const table & to_copy); //copy constructor

		bool build_genres(); //builds the table using an external data file
		bool play(int genre, song *& song_bucket); //plays a random song from the index specified by fed int genre integer; if liked, returned through bucket
		bool play_adjacent(int genre, song *& song_bucket); //plays a random song from the adjacency list of the index specified by fed in genre integer;
		//if liked, returned through song_bucket

		bool remove(song & song_bucket); ///wrapper function for genre's remove function
		void display(); //displays the entire adjacency table

		friend ostream& operator << (ostream&, table&); //displays the entire table's contents
		friend istream& operator >> (istream&, table&); //inserts a fed in song into the table
		table& operator -= (song&); //removes a song from the table that matches the user's input

	protected:
		genre * genre_array; //pointer to an array of genres
		int table_size;	//keeps track of the size of the table; this is modified by data in the external data file
};


