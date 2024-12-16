#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Seat
{
    int seatNumber;
    int isBooked;
    struct Seat *left;
    struct Seat *right;
} Seat;

typedef struct Film
{
    int id;
    char title[50];
    int duration;
    int availableSeats;
    Seat *seatTree;
    struct Film *next;
} Film;

typedef struct Stack
{
    char bookingHistory[50];
    struct Stack *next;
} Stack;

typedef struct Node
{
    char customerName[50];
    int filmId;
    int ticketCount;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front;
    Node *rear;
} Queue;

Seat *createSeat(int seatNumber){
}

Seat *insertSeat(Seat *root, int seatNumber){
}

void displaySeats(Seat *root){
}

Seat *bookSeat(Seat *root, int seatNumber){
}

int countAvailableSeats(Seat *root){
}

Film *createFilm(int id, char *title, int duration){
}

void addFilm(Film **head, int id, char *title, int duration){
}

void displayFilms(Film *head){
}

Film *findFilmById(Film *head, int id){
}

Stack *push(Stack *top, char *booking){
}

void displayStack(Stack *top){
}

Queue *createQueue(){

}

void enqueue(Queue *q, char *name, int filmId, int tickets){
}

void dequeue(Queue *q){
}

void displayQueue(Queue *q, Film *filmList){
}

int totalDataFilm(Film **filmList){
};

void deleteFilm(Film **head, int id){
}

void resetSeats(Seat *root){
}

void resetFilmSeats(Film *head, int id){
}

int main()
{
    Film *filmList = NULL;

    Stack *history = NULL;
    Queue *queue = createQueue();

    int choice, seatNumber, duration, filmId, tickets;
    char name[50], title[50], booking[50];

    do
    {
        system("cls");
        printf("==================================\n| Sistem Pemesanan Tiket Bioskop |\n==================================\n| 1 | Tambah Antrian Tiket\n| 2 | Proses Antrian Tiket\n| 3 | Tampilkan Antrian Tiket\n| 4 | Tampilkan Riwayat Pemesanan\n| 5 | Penambahan Film\n| 6 | Penghapusan Film\n| 7 | Reset Kursi Sesuai Film\n| 8 | Keluar\n==================================\nPilihan: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            printf("==========================================================\nTerima kasih telah menggunakan sistem!\n");
            break;
        default:
            printf("==========================================================\nPilihan tidak valid!\n");
            system("pause");
        }
    } while (choice != 8);

    return 0;
}