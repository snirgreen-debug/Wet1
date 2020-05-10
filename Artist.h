//
// Created by snirg on 10/05/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H

template<typename T>
class Artist {
    T *data;

public:
    Artist() : data(nullptr) {}

    explicit Artist(T *data) : data(data) {}

    Artist(Artist<T> const&artist) : data(artist.data) {}

    ~Artist() = default;

    T *getData() {
        return this->data;
    }

    void setData(T *info) {
        this->data = info;
    }
};


template<class T>
class Array {
    T arr[];

public:
    explicit Array(int n) : arr(new T[n]) {};

    ~Array() {
        delete arr;
    };

    void setArray(T &data, int n) {
        for (int i = 0; i < n; i++)
            this->arr[i] = data;
    };

    T &operator[](int index) { return this->arr[index]; }
};

#endif //WET1_ARTIST_H
