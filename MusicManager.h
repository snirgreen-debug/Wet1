//
// Created by snirg on 06/05/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H

#include "LinkedList.h"
#include "AVLTree.h"

enum StatusType {
    ERROR_ALLOCATION,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
};

struct Song {};

struct Artists{
};

class MusicManager {
private:
    LinkedList<Artists<AVLTree<Song *> *> *streams;
    AVL *;
public:
    MusicManager();

    ~MusicManager();
};


#endif //WET1_MUSICMANAGER_H
