#include "table.h"
using namespace std;

//Josue Valverde, Homework #3, CS202
/******************************SONG LIST CLASS***************************/

//default constructor
song_list::song_list()
{
	list_head = NULL;
}

//copy constructor
song_list::song_list(const song_list & to_copy)
{

}

//adds a song to the list using the fed in arguments
bool song_list::add_song(const char * title, const char * artist, const char * time)
{
	if(!title || !artist)
		return false;

	if(!list_head)
	{
		list_head = new song_node(title, artist, time);
		list_head -> get_next(list_head) = NULL;
	
		return true;
	}

	song_node * temp = new song_node(title,artist,time);
	temp -> get_next(temp) = list_head;
	list_head = temp;
	temp = NULL;

	return true;			
}

//displays the songs in the list using recursive function below
void song_list::display()
{
	display_recursive(list_head);
}

//called by display function above
void song_list::display_recursive(song_node * & head)
{
	if(!head)
		return;

	head -> display_song();

	display_recursive(head -> get_next(head));
}

/*******************************GENRE CLASS*******************************/
//default constructor
genre::genre()
{
	head = NULL;
	list_head = NULL;
	genre_name = NULL;
	num_adj = 0;
}

//copy constructor
genre::genre(const genre & to_copy)
{

}

//updates the name of the genre based on the fed in argument
bool genre::new_name(const char * to_copy)
{
	if(!to_copy)
		return false;

	if(genre_name)
		delete [] genre_name;

	genre_name = new char[strlen(to_copy) + 1];
	strcpy(genre_name, to_copy);

	return true;
}

//returns the name of the genre through the fed in name_bucket
bool genre::assign_name(char *& name_bucket)
{
	if(!genre_name)
		return false;

	else if(name_bucket)
		delete [] name_bucket;

	name_bucket = new char[strlen(genre_name) + 1];
	strcpy(name_bucket, genre_name);

	return true;
}

//updates the number of songs in the list using the fed in argument
bool genre::update_num_songs(int number_of_songs)
{
	num_songs = number_of_songs;
}

//adds an adjacency node the adjacency node list, using the address that it will point to as argument
bool genre::add_adj_node(genre & to_point_to)
{
	if(!head)
		head = new adj_list;

	head ->	add_node(to_point_to);

	++num_adj;
}

//plays a random song from the list and returns it through song_played if it is liked by the user
bool genre::play_song(song *& song_played)
{
	if(!list_head)
		return false;

	int like;
	int pos = rand() % num_songs;
	song_node * current = list_head;

	for(int i = 0; i < pos; ++i)
		current = current -> get_next(current);

	current -> display_song();

	cout << "----------------------------\n";
	cout << "|1.I LIKED this song!      |\n";
	cout << "|2.I DISLIKED this song :( |\n";
	cout << "----------------------------\n";
	cout << "Enter your choice: ";
	cin >> like;
	cin.ignore(100, '\n');

	if(like == 1)
	{
		cout << "\nThis song has been added to your playlist!\n";
		current -> retrieve_song(song_played);
		return true;
	}

	else if(like == 2)
	{
		cout << "\nLet's try again!\n";
		return false;
	}
		
}

//removes a song if it's data matches the song_bucket's data
bool genre::remove(song & song_bucket)
{
	if(!list_head)
		return false;

	bool comparison = false;
	song_node * current = list_head;
	song_node * previous;

	if(!current -> get_next(current))
	{
		comparison = current -> compare(song_bucket);
		if(comparison == true)
		{
			delete current;
			current = NULL;
			list_head = NULL;
			return comparison;
		}
	}

	comparison = current -> compare(song_bucket);
	if(comparison == true)
	{
		list_head = current -> get_next(current);
		delete current;
		current = NULL;
		return comparison;
	}

	while(current -> get_next(current))
	{
		previous = current;
		current = current -> get_next(current);
		comparison = current -> compare(song_bucket);

		if(comparison == true)
		{
			previous -> get_next(previous) = current -> get_next(current);
			delete current;
			current = NULL;	
			return comparison;
		}
			
	}

	return comparison;
}

//Plays a random song that a random adjacenct node is pointing to, returns the song through the song_played bucket if it is liked by the user
bool genre::play_adjacent(song *& song_played)
{
	if(!head)
		return false;

	return head -> play_adjacent(num_adj, song_played);
}

//Displays the adjacency list
void genre::display_adj_list()
{
	head -> display();
}

//Displays the name of the genre and how many songs it has
void genre::display_genre()
{
	cout << "\n\n----------------------------------\\\n";
	cout << "|Genre: " << genre_name << endl;
	cout << "|Number of Songs: " << num_songs << endl;
	cout << "----------------------------------/\n";
	display();
}
/******************************************TABLE CLASS**********************************/
//default constructor
table::table()
{
	genre_array = NULL;
	table_size = 0;
}

//copy constructor
table::table(const table & to_copy)
{

}

//builds the adjacency table using an external data file
bool table::build_genres()
{
	ifstream read;

	read.open("Table.txt");

	char temp_genre[200];
	char temp_name[200];
	char temp_artist[200];
	char temp_time[200];
	char stop;
	int pos = 0;

	if(!read)
		return false;

	read >> table_size;

	genre_array = new genre[table_size];

	while(read.peek() != EOF)
	{
		int num_songs = 0;
		read.get(temp_genre, 200, '~');
		read.ignore(200, '~');

		genre_array[pos].new_name(temp_genre);

		while(read.peek() != '\n' && read.peek() != EOF)
		{

			read.get(temp_name, 200, '~');
			read.ignore(200, '~');

			read.get(temp_artist, 200, '~' );
			read.ignore(200, '~');

			read.get(temp_time, 200, '~');
			read.ignore(200, '~');

			genre_array[pos].add_song(temp_name,temp_artist,temp_time);
			++num_songs;
		}

		if(read.peek() == '\n')
			read.get(stop);

		genre_array[pos].update_num_songs(num_songs);
		++pos;
	}

	read.close();
	
	//the adjacency lists are hardcoded in since there is no other way doing it without overburdening the user
	genre_array[0].add_adj_node(genre_array[1]);
	genre_array[1].add_adj_node(genre_array[0]);
	genre_array[1].add_adj_node(genre_array[2]);
	genre_array[1].add_adj_node(genre_array[3]);
	genre_array[2].add_adj_node(genre_array[0]);
	genre_array[2].add_adj_node(genre_array[1]);
	genre_array[3].add_adj_node(genre_array[2]);
	genre_array[3].add_adj_node(genre_array[4]);
	genre_array[4].add_adj_node(genre_array[2]);
	genre_array[4].add_adj_node(genre_array[3]);

}

//plays a random song in the table, calls genre's play function, returned through bucket if liked so that it can be added to the playlist
bool table::play(int genre, song *& song_bucket)
{
	bool liked;
	int answer;

	liked =	genre_array[genre].play_song(song_bucket);

	return liked;
}

//plays a random song that's adjacent to the fed in genre index; returned through bucket if liked so that it may be added to the playlist
bool table::play_adjacent(int genre, song *& song_bucket)
{
	return genre_array[genre].play_adjacent(song_bucket);		
}

//removes a song if it matches the data of the song_bucket
bool table::remove(song & song_bucket)
{
	bool found = false;

	for(int i = 0; i < table_size; ++i)
	{
		 found = genre_array[i].remove(song_bucket);

		if(found == true)
			return found;
	}

	return found;
}

//displays all of the genres in the genre array
void table::display()
{
	for(int i = 0; i < table_size; ++i)
		genre_array[i].display_genre();
}

//insertion operator is overloaded to display all the contents of the table
ostream& operator << (ostream& out, table& t)
{
	t.display();

	return out;
}

//extraction operator is overloaded to insert a user-specified song into the adjacency table at the appropriate spot
istream& operator >> (istream& in, table& t)
{
	char temp_song[100];
	char temp_artist[100];
	char temp_time[100];
	int genre_choice = 1;


	cout << "-----------------------------------------\n"
	     << "|What Genre do you want to insert into? |\n"
	     << "|1.Choral                               |\n"
	     << "|2.Classical Piano/Violin               |\n"
	     << "|3.Video Game Music                     |\n"
	     << "|4.Anime Music                          |\n"
	     << "|5.Movie/TV Show Soundtrack             |\n"
	     << "-----------------------------------------\n";
	cout << "Please enter your choice: ";
	cin >> genre_choice;
	cin.ignore(100,'\n');
	cout << endl;
						

	cout << "Enter the Name of the song you wish to add: ";
	cin.get(temp_song, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Enter the Artist of the song you wish to add: ";
	cin.get(temp_artist, 100 ,'\n');
	cin.ignore(100, '\n');
			
	cout << "How long is this song (ex. 1:00): ";
	cin.get(temp_time, 100, '\n');
	cin.ignore(100, '\n');

	--genre_choice;

	t.genre_array[genre_choice].add_song(temp_song, temp_artist, temp_time);
	
	cout << "-->Song has been added\n";
}


//removes a song from the table if it matches what the user's input
table& table::operator -= (song& s)
{
	bool comparison = false;

	for(int i = 0; i < table_size; ++i)
	{
		comparison = this -> remove(s);
		if(comparison == true)
		{
			cout << "-->Song has been found and removed\n";
			return *this;
		}
	}

	return *this;
}

/***********************************Adjacency Node Class***************************/

//default constructor
adj_node::adj_node()
{
	adj_genre = NULL;
	genre_name = NULL;
}

//copy constructor
adj_node::adj_node(const adj_node & to_copy)
{

}

//constructor with a genre address as argument; the adjacent node ends up pointing to the fed in address
adj_node::adj_node(genre & to_point_to)
{
	adj_genre = &to_point_to;
	next = NULL;

	to_point_to.assign_name(genre_name);
}

//updates the variable that keeps track of what genre adjacency node is pointing to
bool adj_node::update_genre(const char * new_genre)
{
	if(!new_genre)
		return false;

	genre_name = new char[strlen(new_genre) + 1];
	strcpy(genre_name, new_genre);

	return true;
}

//returns a pointer to the next adjacency node
adj_node*& adj_node::get_next(adj_node *& head)
{
	if(!head)
		return head;

	else
		return head -> next;
}

//plays a random song from the genre that it is pointing to
bool adj_node::play_adjacent(song *& song_bucket)
{
	return adj_genre -> play_song(song_bucket);
}

//displays the name of the genre that the current adj_node is pointing to
void adj_node::display()
{
	cout << genre_name << endl;
}

/********************************Adjacency List Class********************************/
//constructor
adj_list::adj_list()
{
	head = NULL;	
}

//copy constructor
adj_list::adj_list(const adj_list & to_copy)
{

}

//adds a node to the adjacency list that will point to the fed in address
bool adj_list::add_node(genre & to_point_to)
{
	add_node_recursive(to_point_to, head);	
}

//called by the function above to add a node to the adjacency list
bool adj_list::add_node_recursive(genre & to_point_to, adj_node *& head)
{
	if(!head)
	{
		head = new adj_node(to_point_to);
		return true;
	}

	add_node_recursive(to_point_to, head -> get_next(head));

			
}

//goes to a random adjacency node and calls the genre that it's pointing to's play function
bool adj_list::play_adjacent(int num_adj, song *& song_bucket)
{
	if(num_adj == 0)
		return false;
	
	bool liked;
	if(num_adj > 1)
	{
		int pos = rand() % num_adj;
		adj_node * current = head;
	
		for(int i = 0; i < pos; ++i)
			current = current -> get_next(current);
	
		cout << "Song Genre: "; current -> display();
		return current -> play_adjacent(song_bucket);
	}

	return head -> play_adjacent(song_bucket);
}

//displays all the genres that the list is pointing to
void adj_list::display()
{
	cout << "Adjacent Genres: ";
	display_recursive(head);
	cout << endl;
}

//recursive display
//called through the above function
void adj_list::display_recursive(adj_node *& head)
{
	if(!head)
		return;

	head -> display();

	display_recursive(head -> get_next(head));
}
