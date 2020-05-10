//
// Created by snirg on 06/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "LinkedList.h"
#include "AVLTreeImp.h"
#include "AVLTree.h"
#include "Artist.h"

enum StatusType {
    ERROR_ALLOCATION,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
};

struct Song {};

typedef AVLTree<AVLTree<Song *> *> LLNodeStructure;

class MusicManager {
public:
    LinkedList<LLNodeStructure *> *streams;
    AVLTree<Array<LLNode<LLNodeStructure *> *> *> *artists;
public:
    MusicManager();

    StatusType addArtist(int artistID, int numOfSongs);

    StatusType removeArtist(int artistID);

    bool checkNextLink(LLNode<LLNodeStructure *> *pNode);

    StatusType addToSongCount(int artistID, int songID);

    StatusType numberOfStreams(int artistID, int songID, int* streams);

    void orderBySongs(AVLNode<Song *> *node, int *artists, int *songs, int &remainingSongs, int numOfSongs, int artistKey);

    void orderByArtist_aux(AVLNode<AVLTree<Song *> *> *node, int *artists, int *songs, int &remainingSongs, int numOfSongs);

    void orderByArtist(AVLNode<AVLTree<Song *> *> *node, int *artists, int *songs, int &remainingSongs, int numOfSongs);

    void orderBySong_aux(AVLNode<Song *> *node, int *artists, int *songs, int &remainingSongs, int numOfSongs, int artistKey);

    StatusType getRecommendedSongs(int numOfSongs, int* artists, int* songs);

    ~MusicManager();
};


#endif //WET1_MUSICMANAGER_H
