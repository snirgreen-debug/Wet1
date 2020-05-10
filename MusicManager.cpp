//
// Created by snirg on 06/05/2020.
//

#include <iostream>
#include "MusicManager.h"

typedef AVLTree<AVLTree<Song *> *> LLNodeStructure;

MusicManager::MusicManager() {
    this->streams = new LinkedList<LLNodeStructure *>(0, new LLNodeStructure());
    this->artists = new AVLTree<Array<LLNode<LLNodeStructure *> *> *>();
}

StatusType MusicManager::addArtist(int artistID, int numOfSongs) {
    if (artistID <= 0 || numOfSongs <= 0 || !this) return INVALID_INPUT;
    if (this->artists->getNodeByKey(this->artists->root, artistID)) return FAILURE;
    auto tmpArtistsTree = this->streams->getHead()->info;
    AVLTree<Song *> *songs;
    Array<LLNode<LLNodeStructure *> *> *songs_ptrs;

    try {
        songs = new AVLTree<Song *>(numOfSongs);
    } catch (const std::bad_alloc &e) {
        return ERROR_ALLOCATION;
    }

    try {
        tmpArtistsTree->root = tmpArtistsTree->insertNode(tmpArtistsTree->root, artistID, songs);
    } catch (const std::bad_alloc &e) {
        delete songs;
        return ERROR_ALLOCATION;
    }

    try {
        songs_ptrs = new Array<LLNode<LLNodeStructure *> *>(numOfSongs);
    } catch (const std::bad_alloc &e) {
        tmpArtistsTree->root = tmpArtistsTree->deleteNode(tmpArtistsTree->root, artistID);
        return ERROR_ALLOCATION;
    }

    songs_ptrs->setArray(this->streams->getHead());

    try {
        this->artists->root = this->artists->insertNode(this->artists->root, artistID, songs_ptrs);
    } catch (const std::bad_alloc &e) {
        tmpArtistsTree->root = tmpArtistsTree->deleteNode(tmpArtistsTree->root, artistID);
        delete songs_ptrs;
        return ERROR_ALLOCATION;
    }

    return SUCCESS;
}

void deleteCheckTree(AVLNode<Song *> *subRoot, Array<LLNode<LLNodeStructure *> *> *arr) {
    if (!subRoot) return;
    deleteCheckTree(subRoot->left, arr);
    deleteCheckTree(subRoot->right, arr);

    arr->setByIndex(subRoot->key, nullptr);
}

StatusType MusicManager::removeArtist(int artistID) {
    if (artistID <= 0 || !this) return INVALID_INPUT;
    auto *artistToDelete = this->artists->getNodeByKey(this->artists->root, artistID);
    if (!artistToDelete) return FAILURE;
    bool deleteNodeAfterDeletion = false;

    for (int i = 0; i < artistToDelete->info->getSize(); ++i) {
        auto *LLNode_ptr = artistToDelete->info->getByIndex(i);
        if (!LLNode_ptr) {
            continue;
        } else if (!LLNode_ptr->info) {
            continue;
        }

        deleteNodeAfterDeletion = LLNode_ptr->info->root->height == 0;
        auto *a = LLNode_ptr->info->getNodeByKey(LLNode_ptr->info->root, artistID);
        deleteCheckTree(a->info->root, artistToDelete->info);
        LLNode_ptr->info->root = LLNode_ptr->info->deleteNode(LLNode_ptr->info->root, artistID);

        if (deleteNodeAfterDeletion) {
            if (LLNode_ptr->key != 0) {
                this->streams->deleteNodeByPointer(LLNode_ptr);
                LLNode_ptr = nullptr;
            } else {
                LLNode_ptr->info = nullptr;
            }
        }
    }

    this->artists->root = this->artists->deleteNode(this->artists->root, artistID);

    return SUCCESS;
}

bool MusicManager::checkNextLink(LLNode<LLNodeStructure *> *pNode) {
    int numOfCurrentPlays = pNode->key;
    if (!pNode->next) return false;
    return (pNode->next->key - numOfCurrentPlays == 1);
}

StatusType MusicManager::addToSongCount(int artistID, int songID) {
    if (songID < 0 || artistID <= 0 || !this) return INVALID_INPUT;
    auto *currentArtist = this->artists->getNodeByKey(this->artists->root, artistID);
    if (!currentArtist) return FAILURE;
    if (songID >= currentArtist->info->getSize()) return INVALID_INPUT;
    auto currentSongNode = currentArtist->info->getByIndex(songID);
    bool LLNodeCreated = false, artistCreated = false;
    Song *song = nullptr;
    AVLTree<Song *> *artistNodeTree = nullptr;
    AVLTree<AVLTree<Song *> *> *artistsTree = nullptr;

    try {
        song = new Song();
    } catch (const std::bad_alloc &e) {
        return ERROR_ALLOCATION;
    }

    if (!checkNextLink(currentSongNode)) {
        LLNodeCreated = true;
        try {
            this->streams->insertAfter(currentSongNode, currentSongNode->key + 1, nullptr);
        } catch (const std::bad_alloc &e) {
            delete song;
            return ERROR_ALLOCATION;
        }
        try {
            artistsTree = new AVLTree<AVLTree<Song *> *>();
        } catch (const std::bad_alloc &e) {
            this->streams->deleteNodeByPointer(currentSongNode->next);
            delete song;
            return ERROR_ALLOCATION;
        }
        currentSongNode->next->info = artistsTree;
    }

    if (!currentSongNode->next->info->getNodeByKey(currentSongNode->next->info->root, artistID)) {
        artistCreated = true;
        try {
            artistNodeTree = new AVLTree<Song *>();
        } catch (const std::bad_alloc &e) {
            if (LLNodeCreated) {
                this->streams->deleteNodeByPointer(currentSongNode->next);
                delete artistsTree;
            }
            delete song;
            return ERROR_ALLOCATION;
        }
        try {
            currentSongNode->next->info->root = currentSongNode->next->info->insertNode(
                    currentSongNode->next->info->root, artistID, artistNodeTree);
        } catch (const std::bad_alloc &e) {
            if (LLNodeCreated) {
                this->streams->deleteNodeByPointer(currentSongNode->next);
                delete artistsTree;
            }
            delete artistNodeTree;
            delete song;
            return ERROR_ALLOCATION;
        }
    }

    auto *tmpTree = currentSongNode->next->info->getNodeByKey(currentSongNode->next->info->root, artistID);

    try {
        tmpTree->info->root = tmpTree->info->insertNode(tmpTree->info->root, songID, song);
    } catch (const std::bad_alloc &e) {
        if (artistCreated) {
            currentSongNode->next->info->root = currentSongNode->next->info->deleteNode(
                    currentSongNode->next->info->root, artistID);
            delete artistsTree;
        }
        if (LLNodeCreated) {
            this->streams->deleteNodeByPointer(currentSongNode->next);
        }
        delete song;
    }

    currentArtist->info->setByIndex(songID, currentSongNode->next);

    auto currentArtistNode = currentSongNode->info->getNodeByKey(currentSongNode->info->root, artistID);
    currentArtistNode->info->root = currentArtistNode->info->deleteNode(currentArtistNode->info->root, songID);

    if (!currentArtistNode->info->root) {
        currentSongNode->info->root = currentSongNode->info->deleteNode(currentSongNode->info->root, artistID);
    }
    if (!currentSongNode->info->root && currentSongNode->key != 0) {
        this->streams->deleteNodeByPointer(currentSongNode);
    }

    return SUCCESS;
}

StatusType MusicManager::numberOfStreams(int artistID, int songID, int *streams) {
    if (songID < 0 || artistID <= 0 || !this) return INVALID_INPUT;
    auto *currentArtist = this->artists->getNodeByKey(this->artists->root, artistID);
    if (!currentArtist) return FAILURE;
    if (songID >= currentArtist->info->getSize()) return INVALID_INPUT;

    auto *currentSongNode = currentArtist->info->getByIndex(songID);
    *streams = currentSongNode->key;

    return SUCCESS;
}

StatusType MusicManager::getRecommendedSongs(int numOfSongs, int *artists, int *songs) {
    if (numOfSongs <= 0 || !this) return INVALID_INPUT;
    int remainingSongs = numOfSongs;
//    bool lastSong = false;
    auto *iter = this->streams->last;

    while (true) {
        orderByArtist_aux(iter->info->smallestNode, artists, songs, remainingSongs, numOfSongs);
        if (remainingSongs == 0) return SUCCESS;
        if (iter->key == 0) return FAILURE;
        iter = iter->previous;
    }
}

void MusicManager::orderBySongs(AVLNode<Song *> *node, int *artists, int *songs, int &remainingSongs, int numOfSongs,
                                int artistKey) {
    if (!node) return;
    if (remainingSongs == 0) return;

    orderBySongs(node->left, artists, songs, remainingSongs, numOfSongs, artistKey);
    artists[numOfSongs - remainingSongs] = artistKey;
    songs[numOfSongs - remainingSongs] = node->key;
    remainingSongs--;
    orderBySongs(node->right, artists, songs, remainingSongs, numOfSongs, artistKey);
}

void MusicManager::orderByArtist_aux(AVLNode<AVLTree<Song *> *> *node, int *artists, int *songs, int &remainingSongs,
                                     int numOfSongs) {
    if (remainingSongs == 0) return;
    if (!node) return;
    do {
        orderBySong_aux(node->info->smallestNode, artists, songs, remainingSongs, numOfSongs, node->key);
        orderByArtist(node->right, artists, songs, remainingSongs, numOfSongs);
        node = node->parent;
    } while (node && remainingSongs != 0);
}

void MusicManager::orderBySong_aux(AVLNode<Song *> *node, int *artists, int *songs, int &remainingSongs, int numOfSongs,
                                   int artistKey) {
    if (remainingSongs == 0) return;
    if (!node) return;
    do {
        artists[numOfSongs - remainingSongs] = artistKey;
        songs[numOfSongs - remainingSongs] = node->key;
        remainingSongs--;
        orderBySongs(node->right, artists, songs, remainingSongs, numOfSongs, artistKey);
        node = node->parent;
    } while (node && remainingSongs != 0);
}

void MusicManager::orderByArtist(AVLNode<AVLTree<Song *> *> *node, int *artists, int *songs, int &remainingSongs,
                                 int numOfSongs) {
    if (!node) return;
    if (remainingSongs == 0) return;

    orderByArtist(node->left, artists, songs, remainingSongs, numOfSongs);
    orderBySong_aux(node->info->smallestNode, artists, songs, remainingSongs, numOfSongs, node->key);
    orderByArtist(node->right, artists, songs, remainingSongs, numOfSongs);
}

MusicManager::~MusicManager() {
    delete this->artists;
    delete this->streams;
}

