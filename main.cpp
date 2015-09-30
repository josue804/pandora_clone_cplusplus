#include "playlist.h"
using namespace std;

//Josue Valverde, Homework #3, CS202
//Purpose: The purpose of this program is for the user to be able to search a song library by either artist or genre
//The program then plays a random song based on the user's search
//and also plays songs that are similar to what the user chose if the user so desires.
//Everytime a song plays, the user can like the song and it will be added to a playlist.
//If the user plays a song in the playlist and they don't end up liking it, it is removed from the playlist

//Manages the user interface
int main()
{
	srand(time(NULL));

	//creates the adjacency table
	table genres;	
	genres.build_genres();

	//creates the hash table
	hash_table artists;
	artists.load_songs();

	//creates the liked-songs playlist
	playlist song_playlist;

	//variables used for interaction with the user
	song * song_bucket = NULL;
	char * artist_name = NULL;
	int main_choice = 1;
	int adj_choice = 1;
	int genre_choice = 1;
	int data_struct_choice = 1;
	int operator_choice = 1;
	bool liked_genre = true;
	bool liked_artist = true;
	bool playlist_status = false;
	char temp[100];
	char temp_song[100];
	char temp_artist[100];
	char temp_time[100];


	//main menu interface
	while(main_choice != 5)
	{
	cout << "--------------Main Menu----------\n"
	     << "|What would you like to do?     |\n"
	     << "|1.Search by Genre              |\n"
	     << "|2.Search by Artist             |\n"
             << "|3.Play from Playlist           |\n"
	     << "|4.Test Operator Overloading    |\n"
	     << "|5.Quit                         |\n"
	     << "---------------------------------\n";
	cout << "Please enter your choice: ";
	cin >> main_choice;
	cin.ignore(100, '\n');
	cout << endl;


		//if they want to manage the adjacency table
		if(main_choice == 1)
		{
			genre_choice = 1;
			adj_choice = 1;
			liked_genre = true;
		
			cout << "-----------------------------------------\n"
			     << "|What genre would you like to listen to?|\n"
			     << "|1.Choral                               |\n"
			     << "|2.Classical Piano/Violin               |\n"
			     << "|3.Video Game Music                     |\n"
			     << "|4.Anime Music                          |\n"
			     << "|5.Movie/TV Show Soundtrack             |\n"
			     << "-----------------------------------------\n";
			cout << "Please enter your choice: ";
			cin >> genre_choice;
			cin.ignore(100, '\n');
			cout << endl;

			--genre_choice; //genre_choice must be decremented since it is used to access an array position, which starts at 0 and not 1 (lowest option)
			
			cout << "~~Playing~~\n";
			liked_genre = genres.play(genre_choice, song_bucket);

			while(liked_genre == true && adj_choice == 1)
			{
				song_playlist.add_song(song_bucket);				

				cout << "------------------------------------\n";
				cout << "|You liked the last song we played.|\n";
				cout << "|Would you like to branch out?     |\n";
				cout << "|1.Yes                             |\n";
				cout << "|2.No, go to Main Menu             |\n";
				cout << "------------------------------------\n";
				cout << "Please enter your choice: ";
				cin >> adj_choice;
				cin.ignore(100, '\n');
				
				if(adj_choice == 1)
				{	
					cout << "\n~~Playing~~\n";
					liked_genre = genres.play_adjacent(genre_choice, song_bucket);
				}
		
			}
		}

		//if they want to manage the hash table	
		if(main_choice == 2)
		{
			liked_artist = true;
	
			cout << "Here is a list of available artists: \n";
			artists.display_artists();
	
			cout << "Please enter an artist name: ";
			cin.get(temp, 100, '\n');

			if(artist_name)
				delete [] artist_name;
			artist_name = new char[strlen(temp) + 1];
			strcpy(artist_name, temp);


			cout << "\n~~Playing~~\n";		
			liked_artist = artists.search_artist(artist_name, song_bucket);
		
			while(liked_artist == true && adj_choice == 1)
			{
				song_playlist.add_song(song_bucket);

				cout << "------------------------------------\n";
				cout << "|You liked the last song we played.|\n";
				cout << "|Would you like to branch out?     |\n";
				cout << "|1.Yes                             |\n";
				cout << "|2.No, go to Main Menu             |\n";
				cout << "------------------------------------\n";
				cout << "Please enter your choice: ";
				cin >> adj_choice;
				cin.ignore(100, '\n');
	
				if(adj_choice == 1)
					liked_artist = artists.play_adjacent(artist_name, song_bucket);
			}
	
		}

		//if they want to manage the playlist
		if(main_choice == 3)
		{

			cout << "-----------------------------\n"
			     << "|Playing from your Playlist |\n"
			     << "-----------------------------\n";
			playlist_status = song_playlist.play_song();


			if(playlist_status == false)
				cout << "--> Playlist is empty!\n";
		}

		//if they want to test out operator overloading
		if(main_choice == 4)
		{
			cout << "----------------------------------\n"
			     << "|What would you like to test on? |\n"
			     << "|1.Adjacency Table               |\n"
			     << "|2.Hash Table                    |\n"
			     << "|3.CLL Playlist                  |\n"
			     << "---------------------------------|\n";
			cout << "Please enter your choice: ";
			cin >> data_struct_choice;
			cin.ignore(100, '\n');
			cout << endl;
		
			//test adj table operator overloading	
			if(data_struct_choice == 1)
			{
				cout << "----------------------------\n"
				     << "|What would you like to do?|\n"
				     << "|1.Display (<<)            |\n"
				     << "|2.Insert (>>)             |\n"
				     << "|3.Search and Remove (-=)  |\n"
				     << "---------------------------|\n";
				cout << "Please enter your choice: ";
				cin >> operator_choice;
				cin.ignore(100, '\n');
				cout << endl;

				if(operator_choice == 1)
					cout << genres;

				if(operator_choice == 2)
					cin >> genres; 

				if(operator_choice == 3)
				{
					cout << "Enter the title of the song you are looking for: ";
					cin.get(temp_song, 100, '\n');
					cin.ignore(100,'\n');
					cout << endl;
					
					if(song_bucket)
						delete song_bucket;
			
					song_bucket = new song(temp_song, "blank", "blank");
			
					genres -= *song_bucket;
				}
			}
		
			//test hash table operator overloading
			if(data_struct_choice == 2)
			{
				cout << "----------------------------\n"
				     << "|What would you like to do?|\n"
				     << "|1.Display (<<)            |\n"
				     << "|2.Insert (>>)             |\n"
				     << "|3.Find and Play (==)      |\n"
				     << "---------------------------|\n";
				cout << "Please enter your choice: ";
				cin >> operator_choice;
				cin.ignore(100, '\n');
				cout << endl;

				if(operator_choice == 1)
					cout << artists;

				if(operator_choice == 2)
					cin >> artists; 

				if(operator_choice == 3)
				{
					cout << "Enter the title of the artist you are looking for: ";
					cin.get(temp_artist, 100, '\n');
					cin.ignore(100,'\n');
					cout << endl;
					
					if(artists == temp_artist)
						cout << "--> Song Played\n";	
				}
			}


			//test CLL Playlist operator overloading
			if(data_struct_choice == 3)
			{
				cout << "----------------------------\n"
				     << "|What would you like to do?|\n"
				     << "|1.Display (<<)            |\n"
				     << "|2.Insert (>>)             |\n"
				     << "----------------------------\n";
				cout << "Please enter your choice: ";
				cin >> operator_choice;
				cin.ignore(100, '\n');
				cout << endl;

				if(operator_choice == 1)
					cout << song_playlist;

				if(operator_choice == 2)
					cin >> song_playlist; 
			}


		}


	}


	return 0;
}
