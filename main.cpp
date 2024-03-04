#include <iostream>
using namespace std;

class Movie {
public:
    string name;
    int availableSeats;
    int seatPrice;
    bool selectedSeats[25];

    Movie(string n, int as, int sp) : name(n), availableSeats(as), seatPrice(sp) {
        for (int i = 0; i < 25; i++) {
            selectedSeats[i] = false;
        }
    }
};
class Cinema {
private:
    class Node {
    public:
        Movie movie;
        Node* next;

        Node(Movie m, Node* n) : movie(m), next(n) {}
    };

    Node* head;

public:
    Cinema() {
        head = nullptr;
    }

    void addMovie(Movie m) {
        if (head == nullptr) {
            head = new Node(m, nullptr);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(m, nullptr);
        }
    }

    void displayMovies() {
        Node* current = head;
          cout<<"*************Movies available************"<<endl<<endl;
        while (current != nullptr) {
            cout << "Name: " << current->movie.name << ", Available Seats: " << current->movie.availableSeats << ", Seat Price: Rs." << current->movie.seatPrice << endl<<endl;
          current = current->next;
        }
    }

    void bookTicket(string name, string username, int seatNo) {
        Node* current = head;
        while (current != nullptr) {
            if (current->movie.name == name) {
                if (seatNo > 0 && seatNo <= current->movie.availableSeats && !current->movie.selectedSeats[seatNo - 1]) {
                    current->movie.availableSeats--;
                    current->movie.selectedSeats[seatNo - 1] = true;
                    cout <<endl<< "********Ticket booked for " << name<<"********" <<endl;
                    cout<< "\tName: " << username <<endl;
                    cout<< "\tSeat no.: " << seatNo <<endl;
                    cout<< "\tAmount Rs.: " << current->movie.seatPrice << endl<<endl;

                } else if (seatNo > current->movie.availableSeats || seatNo <= 0) {
                    cout <<endl<<"There are only " << current->movie.availableSeats << " seats available for " << name << "." << endl;
                } else {
                    cout <<endl<<"Seat " << seatNo << " is already booked for " << name << "." << endl;
                }
                return;
            }
            current = current->next;
        }
        cout << "Movie not found." << endl<<endl;
    }

 void cancelTicket(string name, string username, int seatNo) {
        Node* current = head;
        while (current != nullptr) {
            if (current->movie.name == name ) {
                for (int i = 0; i < 25; i++) {
                    if (current->movie.selectedSeats[i]) {
                        if (i + 1 == seatNo) {
                            current->movie.availableSeats++;
                            current->movie.selectedSeats[i] = false;
                            cout << "Ticket cancelled for " << name << " by " << username << " at seat " << seatNo <<endl<< endl;
                            return;
                        }
                    }
                }
                cout << "The seat number " << seatNo << " can not be cancelled for " << name << "." << endl<<endl;
                return;
            }
            current = current->next;
        }
        cout << "Movie not found." << endl;
    }
    void selectSeat(string name) {
        Node* current = head;
        while (current != nullptr) {
            if (current->movie.name == name) {
                cout << "*****Available seats*****  " << endl;
                for (int i = 0; i < 25; i++) {
                    if (!current->movie.selectedSeats[i]) {
                        cout << i + 1 << "   ";
                    }
                }
                cout << endl<<endl;
                return;
            }
            current = current->next;
        }
        cout << "Movie not found." << endl<<endl;
    }

};
int main() {
    Cinema c;
    c.addMovie(Movie("abc", 25, 100));
    c.addMovie(Movie("pqr", 25, 50));
    cout<<"*********Movie Ticket Booking**********"<<endl<<endl;
     while (true) {
        cout << "1. Display Movies\n2. Book Ticket\n3. Cancel Ticket\n4. Select Seat\n5. Exit" << endl;
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                c.displayMovies();
                break;
            case 2: {
                string mname,uname;
                int seatno;
                cout << "Enter movie name: ";
                cin >> mname;
                cout<<"Enter username:  ";
                cin>>uname;
                cout<<"Enter seat no.: ";
                cin>>seatno;
                c.bookTicket(mname,uname,seatno);
                break;
            }
            case 3: {
               string mname,uname;
                int seatno;
                cout << "Enter movie name: ";
                cin >> mname;
                 cout<<"Enter username:  ";
                cin>>uname;
                cout<<"Enter seat no.: ";
                cin>>seatno;
                c.cancelTicket(mname,uname,seatno);
                break;
            }
            case 4: {
                string mname;
                cout << "Enter movie name: ";
               cin >> mname;
                c.selectSeat(mname);
                break;
            }
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }
    return 0;
}
