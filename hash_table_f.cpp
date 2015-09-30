#include "hash_table.h"
using namespace std;

//Josue Valverde, Homework #3, CS202

/************************************HASH INDEX CLASS********************************/
//Default constructor
hash_index::hash_index()
{
	index_head = NULL;
	related_artist = NULL;
	artist_name = NULL;
	num_songs = 0;
}

//copy constructor
hash_index::hash_index(const hash_index & to_copy)
{
	//copy traverses through the list and current copies it at is goes
	song_node * copy = to_copy.index_head;
	song_node * current = NULL;

	current = new song_node(*copy);
	index_head = current;
	current = current -> get_next(current);
	copy = copy -> get_next(copy);	

	while(copy)
	{
		current = new song_node(*copy);
		current = current -> get_next(current);
		copy = copy -> get_next(copy);	
	}
}

//adds a song to the index using the fed in song object
bool hash_index::add_song(song & to_add)
{
	//if it's the first item
	if(!index_head)
	{
		to_add.copy_artist_name(artist_name);
		index_head = new song_node(to_add);
		++num_songs;
		return true;
	}

	//otherwise add at the head and connect
	song_node * temp = new song_node(to_add);
	temp -> get_next(temp) = index_head;
	index_head = temp;
	++num_songs;
	return true;
}

//connects hash index to the one specified through argument
bool hash_index::connect_artist(hash_index & to_connect_to)
{
	if(related_artist)
		return false;

	related_artist = &to_connect_to;
	return true;
}

//compares to see if the index has the same artist as the fed in argument
bool hash_index::compare_artists(char * artist)
{
	if(!artist_name || strcmp(artist, artist_name) != 0)
		return false;

	return true;
}

//plays a random song inside the index and retrieves it through the song_bucket
bool hash_index::play_song(song *& song_bucket)
{
	if(!index_head)
		return false;

	int like;
	int pos = rand() % num_songs;
	song_node * current = index_head;

	for(int i = 0; i < pos; ++i)
		current = current -> get_next(current);

	current -> display_song();

	//if the song is liked, then it is retrieved and sent over to the playlist class through main
	cout << "----------------------------\n";
	cout << "|1.I LIKED this song!      |\n";
	cout << "|2.I DISLIKED this song :( |\n";
	cout << "----------------------------\n";
	cout << "Enter your choice: ";
	cin >> like;
	cin.ignore(100, '\n');

	if(like == 1)
	{
		cout << "-->This song has been added to your playlist!\n\n";
		current -> retrieve_song(song_bucket);
		return true;
	}

	else if(like == 2)
	{
		cout << "-->Back to the start, then!\n\n";
		return false;
	}


}

//plays a random song of the related artist
bool hash_index::play_adjacent(song *& song_bucket)
{
	if(!related_artist)
		return false;

	return related_artist -> play_song(song_bucket);
}

//changes the fed in argument to be the adjacent artist of the current index, this is to so that you can get from one artist to any other, they are all connected
bool hash_index::jump_artists(char *& artist)
{
	if(!artist_name)
		return false;

	if(artist)
		delete [] artist;

	artist = new char[strlen(related_artist -> artist_name) + 1];
	strcpy(artist, related_artist -> artist_name);

	return true;
}

//displays all the songs in the current index
void hash_index::display()
{
	display_recursive(index_head);	
}

//is called by the display function above
void hash_index::display_recursive(song_node *& head)
{
	if(!head)
		return;

	head -> display_song();
}

//displays the name of the artist that 'owns' the currenti index
void hash_index::display_artist()
{
	if(artist_name)
		cout << "->" << artist_name << endl;
}

/************************************HASH TABLE CLASS********************************/

//Default constructor
//creates array of hash indices based on constant defined in .h file
hash_table::hash_table()
{
	table_array = new hash_index[HASH_TABLE_SIZE];
}

//Copy constructor
hash_table::hash_table(const hash_table & to_copy)
{

}

//Reads in the songs from the file and creates the hash table
bool hash_table::load_songs()
{

	ifstream read;

	read.open("Hash_table.txt");

	char temp_name[200];
	char temp_artist[200];
	char temp_time[200];
	song * temp_object;

	if(!read)
		return false;

	//this is where the reading in and copying happens
	while(read.peek() != '\n')
	{
		read.get(temp_name, 200, '~');
		read.ignore(200, '~');

		read.get(temp_artist, 200, '~' );
		read.ignore(200, '~');

		read.get(temp_time, 200, '~');
		read.ignore(200, '~');

		temp_object = new song(temp_name,temp_artist,temp_time);
	
		hash_and_add(*temp_object);
	
		delete temp_object;
		temp_object = NULL;

	}

	//the adjacency connections are hardcoded in since there is no other way to connect them in a way that makes sense
	table_array[5].connect_artist(table_array[78]);
	table_array[78].connect_artist(table_array[59]);
	table_array[59].connect_artist(table_array[34]);
	table_array[34].connect_artist(table_array[70]);
	table_array[70].connect_artist(table_array[57]);
	table_array[57].connect_artist(table_array[89]);
	table_array[89].connect_artist(table_array[6]);
	table_array[6].connect_artist(table_array[7]);
	table_array[7].connect_artist(table_array[82]);
	table_array[82].connect_artist(table_array[95]);
	table_array[95].connect_artist(table_array[16]);
	table_array[16].connect_artist(table_array[83]);
	table_array[83].connect_artist(table_array[1]);
	table_array[1].connect_artist(table_array[17]);
	table_array[17].connect_artist(table_array[2]);
	table_array[2].connect_artist(table_array[42]);
	table_array[42].connect_artist(table_array[5]);
	
}

//hashes the artist's name and inserts into the appropriate index
//there are no collisions
bool hash_table::hash_and_add(song & to_add)
{
	int key = 0;
	key = to_add.hash() % HASH_TABLE_SIZE;

	table_array[key].add_song(to_add);	
}

//searches to see if the artist fed in is in the table
//if it is, then a song from their list is played randomly
//if the song is liked, then it is returned through song_bucket to be added to the playlist
bool hash_table::search_artist(char *& artist, song *& song_bucket)
{
	bool found = false;

	for(int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		found = table_array[i].compare_artists(artist);

		if(found == true)
		{
			found = table_array[i].play_song(song_bucket);
			return found;
		}
	}

	cout << "No artists by that name\n";
	return found;
}

//plays a song from an adjacent artist using the functions previously described in the hash_index class
//if the adjacent song is liked, then it is returned through song_bucket to be added to the playlist
bool hash_table::play_adjacent(char *& artist, song *& song_bucket)
{
	bool found = false;

	for(int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		found = table_array[i].compare_artists(artist);

		if(found == true)
		{
			table_array[i].jump_artists(artist);
			found = table_array[i].play_adjacent(song_bucket);
			return found;	
		}
	}

	return found;
}

//displays all the songs in the hash table
void hash_table::display()
{
	for(int i = 0; i < HASH_TABLE_SIZE; ++i)
		table_array[i].display();		
}

//displays all the artists in the hash table
void hash_table::display_artists()
{
	for(int i = 0; i < HASH_TABLE_SIZE; ++i)
		table_array[i].display_artist();
}

//Insertion operator is overloaded to display all the songs in hash table
ostream& operator << (ostream& out, hash_table& h)
{
	h.display();

	return out;
}

//Extraction operator is overloaded to be able to insert a song in the the hash table
istream& operator >> (istream& in, hash_table& h)
{
	char temp_song[100];
	char temp_artist[100];
	char temp_time[100];
	int genre_choice = 1;
	song * song_bucket;

	cout << "Enter the Name of the song you wish to add: ";
	cin.get(temp_song, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Enter the Artist of the song you wish to add: ";
	cin.get(temp_artist, 100 ,'\n');
	cin.ignore(100, '\n');
			
	cout << "How long is this song (ex. 1:00): ";
	cin.get(temp_time, 100, '\n');
	cin.ignore(100, '\n');

	song_bucket = new song(temp_song,temp_artist,temp_time);

	h.hash_and_add(*song_bucket);
	
	cout << "-->Song has been added\n";

}

//Equal to operator is used to see if the artist fed in is found in the hash table
//Plays a song of the artist is found and returns true
bool hash_table::operator == (char * artist_to_find)
{	
	bool found = false;

	for(int i = 0; i < HASH_TABLE_SIZE; ++i)
	{
		found = table_array[i].compare_artists(artist_to_find);

		if(found == true)
		{
			table_array[i].display();
			return found;
		}
	}

	cout << "No artists by that name\n";
	return found;
}
