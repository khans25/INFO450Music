// mypod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

class song
{
	char name[100];
	int data;
	song *next;
public:
	song(int x);
	void setSong(char n[]);
	friend class playList;
};

song::song(int x)
{
	strcpy(name, "");
	data = x;
	next = NULL;
}

void song::setSong(char n[])
{
	strcpy(name, n);
}

class playList
{
	char filename[100];
	int songCount;
	song *head;
	song *tail;
	song **mylist;
public:
	playList();
	void setSong(char n[]);
	int getCount();
	void addSongToEnd(song *nptr);
	void addSongToHead(song *nptr);
	int insertAfter(song *ptr, int i);
	int removeSong(int i);
	void playList::addToList(song *p);
	void showList();
	void readList();	
	song * findItem(int i);
};

playList::playList()
{
	head = NULL;
	tail = NULL;
	songCount = 0;
}

void playList::setSong(char f[])
{
	strcpy_s(filename, f);
}

void playList::addToList(song *p)
{
	mylist[songCount] = p;
	songCount++;;
}

int playList::getCount()
{
	return songCount;
}

void playList::showList()
{
	song *ptr;
	ptr = head;
	cout << "****  List Contents *****" << endl;
	if (ptr == NULL)
	{
		cout << "Empty List Found " << endl;
		return;
	}
	cout << "(First is " << head->name << " End is " << tail->name << ")" << endl;
	while (ptr != NULL)
	{
		cout << "Song is " << ptr->name << endl;
		ptr = ptr->next;
	}
}

void playList::addSongToEnd(song *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void playList::addSongToHead(song *ptr)
{
	if (head == NULL)
	{
		head = ptr;
		tail = ptr;
	}
	else
	{
		ptr->next = head;
		head = ptr;
	}
}

int playList::insertAfter(song *newsong, int i)
{
	song *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i) // we found the node to insert after
		{
			newsong->next = ptr->next;
			ptr->next = newsong;
			if (tail == ptr) // repoint tail if we added to end
				tail = newsong;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

song * playList::findItem(int i)
{
	song *ptr;
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->data == i)
		{
			cout << "Playlist located." << endl;
			return ptr;
		}
		ptr = ptr->next;
	}

	cout << "No Playlist located." << endl;
	return NULL;
}


int playList::removeSong(int i)
{
	song *ptr = head;
	if (ptr == NULL)  // empty list
		return -1;

	// if node is at the head
	if (head->data == i)
	{
		//if only 1 node in the list
		if (head == tail)
		{
			head = NULL;
			tail = NULL;
		}
		else
			head = head->next;
		delete ptr;
		return 0;
	}

	while (ptr != NULL)
	{
		if (ptr->next && (ptr->next)->data == i)
		{
			if (tail == ptr->next)
				tail = ptr;
			song *tbd = ptr->next;
			ptr->next = (ptr->next)->next;
			delete tbd;
			return 0;
		}
		ptr = ptr->next;
	}
	return -1;
}

void playList::readList()
{
	ifstream infile(filename);
	if (!infile)
	{
		return;
	}

	while (!infile.eof())
	{
		song *ptr;
		char name[100];

		infile.getline(name, 100, ',');
		if (strlen(name))
		{
			ptr = new song(name[100]);
			ptr->setSong(name);
			addToList(ptr);
		}
	}
	infile.close();
}

int main()
{
	char answer = 'y';
	char name[100];
	char filename[100];
	playList *slist = new playList();
	cout << "Insert full file path here" << endl;
	gets_s(filename);
	slist->setSong(filename);
	
	slist->readList();
	if (slist->getCount() == 0)
	{
		cout << "No file, create file. " << endl;
	}
	else
	{
		cout << "There are: " << slist->getCount() << endl;
	}

	return 0;
}