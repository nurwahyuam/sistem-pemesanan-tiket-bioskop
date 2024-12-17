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
  Seat *newSeat = (Seat *)malloc(sizeof(Seat));
  newSeat->seatNumber = seatNumber;
  newSeat->isBooked = 0;
  newSeat->left = newSeat->right = NULL;
  return newSeat;
}

Seat *insertSeat(Seat *root, int seatNumber){
  if (root == NULL)
    return createSeat(seatNumber);
  if (seatNumber < root->seatNumber){
    root->left = insertSeat(root->left, seatNumber);
  } else if (seatNumber > root->seatNumber){
    root->right = insertSeat(root->right, seatNumber);
  }
  return root;
}

void displaySeats(Seat *root){
}

Seat *bookSeat(Seat *root, int seatNumber){
}

int countAvailableSeats(Seat *root){
}

Film *createFilm(int id, char *title, int duration){
  Film *newFilm = (Film *)malloc(sizeof(Film));
  newFilm->id = id;
  strcpy(newFilm->title, title);
  newFilm->duration = duration;
  newFilm->availableSeats = 10;
  newFilm->seatTree = NULL;
  for (int i = 1; i <= 10; i++){
    newFilm->seatTree = insertSeat(newFilm->seatTree, i);
  }
  newFilm->next = NULL;
  return newFilm;
}

void addFilm(Film **head, int id, char *title, int duration){
  Film *newFilm = createFilm(id, title, duration);
  if(*head == NULL){
    *head = newFilm;
  } else {
    Film *temp = *head;
    while (temp->next != NULL){
      temp = temp->next;
    }
    temp->next = newFilm;
  }
}

void displayFilms(Film *head){
  printf("Daftar Film:\n");
  while (head != NULL){
    printf("%d. %s - (%d menit) - (%d Kursi Kosong)\n", head->id, head->title, head->duration, countAvailableSeats(head->seatTree));
    head = head->next;
  }
}

Film *findFilmById(Film *head, int id){
  while (head != NULL){
    if (head->id == id)
    return head;
    head = head->next;
  }
  return NULL;
}

Stack *push(Stack *top, char *booking){
    Stack *newStack = (Stack *)malloc(sizeof(Stack));
    strcpy(newStack->bookingHistory, booking);
    newStack->next = top;
    return newStack;
}

void displayStack(Stack *top){
    if (top == NULL)
    {
        printf("Riwayat kosong!\n");
        return;
    }
    int i = 1;
    printf("Riwayat Pemesanan:\n");
    while (top != NULL)
    {
        printf("%d. %s\n", i, top->bookingHistory);
        top = top->next;
        i++;
    }
}

Queue *createQueue(){
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->front = q->rear = NULL;
  return q;
}

void enqueue(Queue *q, char *name, int filmId, int tickets){
  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->customerName, name);
  newNode->filmId = filmId;
  newNode->ticketCount = tickets;
  newNode->next = NULL;

  if (q->rear == NULL){
    q->front = q->rear = newNode;
    return;
  }
  q->rear->next = newNode;
  q->rear = newNode;
}

void dequeue(Queue *q){
    if (q->front == NULL)
    {
        printf("Antrian kosong!\n");
        return;
    }

    Node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(temp);
}

void displayQueue(Queue *q, Film *filmList){
    if (q->front == NULL)
    {
        printf("Antrian kosong!\n");
        return;
    }

    Node *current = q->front;
    int i = 1;

    printf("Antrian Tiket:\n");
    while (current != NULL)
    {
        Film *film = findFilmById(filmList, current->filmId);
        if (film != NULL)
        {
            printf("Antrean %d\n", i);
            printf("Costumer: %s\n", current->customerName);
            printf("Film: %s\n", film->title);
            printf("Tiket: %d\n\n", current->ticketCount);
        }
        else
        {
            printf("Antrean %d - Film tidak ditemukan!\n", i);
        }
        current = current->next;
        i++;
    }
}

int totalDataFilm(Film **filmList)
{
    int count = 0;
    Film *pCur;
    pCur = *filmList;
    while (pCur != NULL)
        {
            count += pCur->id;
            pCur = pCur->next;
        }
    return count;
};

void deleteFilm(Film **head, int id)
{
    if (*head == NULL)
    {
        printf("Film dengan ID %d tidak ditemukan!\n", id);
        return;
    }
    
    Film *temp = *head;
    Film *prev = NULL;

    if (temp != NULL && temp ->id == id)
    {
        *head = temp->next;
        free(temp);
        printf("Film dengan ID %d berhasil dihapus!\n", id);
    }

    while (temp != NULL && temp ->id != id)
        {
            prev = temp;
            temp = temp->next;
        }

    if (temp == NULL)
    {
        printf("Film dengan ID %d tidak ditemukan!\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf ("Film dengan ID%d berhasil dihapus!\n", id);
}

void resetSeats(Seat *root)
{
    if (root != NULL)
    {
        resetSeats(root->left);
        root->isBooked = 0;
        resetSeats(root->right);
    }
}

void resetFilmSeats(Film *head, int id)
{
    Film *film = findFilmById(head, id);
    if (film == NULL)
    {
        printf("Film dengan ID %d tidak ditemukan!\n", id);
        return;
    }
    resetSeats(film->seatTree);
    film->availableSeats = countAvailableSeats(film->seatTree);
    displaySeats(film->seatTree);
    printf("Kursi untuk film '%s' telah di-reset ke status kosong!\n", film->title);
}

int main()
{
    Film *filmList = NULL;
    addFilm(&filmList, 1, "Avengers: Endgame", 180);
    addFilm(&filmList, 2, "Spider-Man: No Way Home", 150);
    addFilm(&filmList, 3, "The Batman", 175);

    Stack *history = NULL;
    Queue *queue = createQueue();

    int choice, seatNumber, duration, filmId, tickets;
    char name[50], title[50], booking[50];

    do {
        system("cls");
        printf("==================================\n| Sistem Pemesanan Tiket Bioskop |\n==================================\n| 1 | Tambah Antrian Tiket\n| 2 | Proses Antrian Tiket\n| 3 | Tampilkan Antrian Tiket\n| 4 | Tampilkan Riwayat Pemesanan\n| 5 | Penambahan Film\n| 6 | Penghapusan Film\n| 7 | Reset Kursi Sesuai Film\n| 8 | Keluar\n==================================\nPilihan: ");
        scanf("%d", &choice);
      
        switch (choice){
        case 1:
          system("cls");
          displayFilms(filmList);
          printf("==========================================================\nMasukkan nama pelanggan: ");
          scanf("%s", name);
          printf("Masukkan ID film yang akan ditonton: ");
          scanf("%d", &filmId);
          Film *film = findFilmById(filmList, filmId);
          if (film == NULL){
            printf("==========================================================\nFilm dengan ID %d tidak ditemukan!\n", filmId);
            system("pause");
            break;
          }
          printf("Masukkan jumlah tiket: ");
          scanf("%d", &tickets);
          if (tickets > film->availableSeats){
            printf("==========================================================\nJumlah tiket melebihi kursi tersedia!\n");
            system("pause");
            break;
          }
          enqueue(queue, name, filmId, tickets);
          printf("==========================================================\nAntrian berhasil ditambahkan!\n");
          system("pause");
          break;
        case 2:
            if (queue->front != NULL)
            {
               film = findFilmById(filmList, queue->front->filmId);
                if (film != NULL)
                {
                    for (int i = 0; i < queue->front->ticketCount);
                    {
                        system("cls");
                        printf("Costumer: %s\nNomor kursi tersedia untuk film %s:\n", queue->front->customerName, film->title);
                        displaySeats(film->seatTree);
                        printf("Masukan nomor kursi: ");
                        scanf("%d", &seatNumber);
                        Seat *seat = bookSeat(film->seatTree, seatNumber);
                        if (seat != NULL)
                        {
                            film->availableSeats--;
                            i++;
                        }
                    }
                    system("cls");
                    printf("Costumer: %s\nNomor kursi tersedia untuk Film %s:\n", queue->front->customerName, film->title);
                    displaySeats(film->seatTree);
                    sprintf(booking, "%s (%s - %d tiket)", queue->front->customerName, film->title, queue->front->ticketCount);
                    history = push(history, booking);
                    dequeue(queue);
                    printf("==========================================================\nPemesanan berhasil!\n");
                    system("pause");
                }
                else
                {
                    printf("==========================================================\nFilm tidak ditemukan!\n");
                    system("pause");
                }
            }
            else
            {
                printf("==========================================================\nAntrian kosong!\n");
                system("pause");
            }
            break;
        case 3:
            system("cls");
            displayQueue(queue, filmList);
            system("pause");
            break;
        case 4:
            system("cls");
            displayStack(history);
            system("pause");
            break;
        case 5:
            system("cls");
            int i = totalDataFilm(&filmList) + 1;
            printf("Masukkan judul film: ");
            scanf("%s", &title);
            printf("Masukkan durasi film: ");
            scanf("%d", &duration);
            addFilm(&filmList, i, title, duration);
            system("pause");
            break;
        case 6:
            system("cls");
            printf("List Data Film: ");
            displayFilm(filmList);
            printf("Masukkan Id Film yang akan dihapus: ");
            scanf("%d", &filmId);
            deleteFilm(&filmList, filmId);
            system("pause");
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
