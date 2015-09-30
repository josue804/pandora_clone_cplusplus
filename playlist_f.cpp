#include "playlist.h"
using namespace std;

//Josue Valverde, Homework #3, CS202
/****************************PLAYLIST CLASS*************************/

//Default Constructor
playlist::playlist()
{
	playlist_rear = NULL;
	num_songs = 0;
}

//Copy Constructor
playlist::playlist(const playlist & to_copy)
{

}

//Adds the song contained in the song bucket to the playlist
bool playlist::add_song(song *& song_bucket)
{
	//if there is no song to add, return
	if(!song_bucket)
		return false;

	//if this is the first item added
	if(!playlist_rear)
	{
		playlist_rear = new song_node(*song_bucket);
		playlist_rear -> get_next(playlist_rear) = playlist_rear;
		++num_songs;
		return true;
	}

	//if there is already at least 1 item in the list
	song_node * temp = playlist_rear -> get_next(playlist_rear);
	playlist_rear -> get_next(playlist_rear) = new song_node(*song_bucket);
	playlist_rear = playlist_rear -> get_next(playlist_rear);
	playlist_rear -> get_next(playlist_rear) = temp;

	temp = NULL;
	++num_songs;

	return true;

	
}

//plays a random song in the playlist
bool playlist::play_song()
{
	if(!playlist_rear)
		return false;

	int pos = rand() % num_songs;
	int answer = 1;

	cout << "\n~~Playing~~\n";
	playlist_rear -> get_next(playlist_rear) -> display_song();	


	//if the user still likes the song, leaves it as is
	//otherwise, it is deleted from the playlist
	cout << "------------------------------\n"
	     << "|Do you still like this song?|\n"
	     << "|1.Yes                       |\n"
	     << "|2.No                        |\n"
	     << "------------------------------\n";
	cout << "Please enter your choice: ";
	cin >> answer;
	cout << endl;

	if(answer == 1)
		return true;

	if(answer == 2)
	{
		cout << "-->This song has been removed from your Playlist\n";

		song_node * current = playlist_rear -> get_next(playlist_rear);
		playlist_rear -> get_next(playlist_rear) = current -> get_next(current);
		
		if(playlist_rear == current)
		{
			delete playlist_rear;
			playlist_rear = NULL;
			current = NULL;
			return true;
		}

		delete current;
		current = NULL;

		return true;
	}	


}

//displays the songs in the playlist
void playlist::display()
{

	//empty list
	if(!playlist_rear)
		return;

	//one item in the list
	if(playlist_rear -> get_next(playlist_rear) == playlist_rear)
	{
		playlist_rear -> display_song();
		return;
	}

	song_node * current = playlist_rear -> get_next(playlist_rear);

	//two items in the list
	if(current -> get_next(current) == playlist_rear)
	{
		current -> display_song();
		playlist_rear -> display_song();

		current = NULL;
		return;
	}

	//more than two items in the list
	current -> display_song();
	while(current -> get_next(current) != playlist_rear -> get_next(playlist_rear))
	{
		current = current -> get_next(current);
		current -> display_song();
	}

	current = NULL;

}

//overloads insertion operator to display all the songs in the list
ostream& operator << (ostream& out, playlist& p)
{
	p.display();

	return out;
}

//overloads extraction operator to insert a song specified by the user into the list
istream& operator >> (istream& in, playlist& p)
{
	char temp_song[100];
	char temp_artist[100];
	char temp_time[100];
	song * song_bucket = NULL;

	cout << "Enter the Name of the song you wish to add: ";
	cin.get(temp_song, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Enter the Artist of the song you wish to add: ";
	cin.get(temp_artist, 100 ,'\n');
	cin.ignore(100, '\n');
			
	cout << "How long is this song (ex. 1:00): ";
	cin.get(temp_time, 100, '\n');
	cin.ignore(100, '\n');

	song_bucket = new song(temp_song, temp_artist, temp_time);

	p.add_song(song_bucket);
	
	cout << "-->Song has been added\n";
}


