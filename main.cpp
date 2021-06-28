#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>


using namespace std;

struct Date {                                                                                           //STRUCTURE DATE
    int dd, mm, yy;
};

/**********CLASSES**********/

class book {                                                                                            //CLASS Book(1)
    int bookno;
    char title[20], author[30], publisher[30], type;
    float price;
    int noofcopies, noofissued;

public:
    void B_getData();

    void B_showData();

    int retbookno() {
        return bookno;
    }

    int checkbook();

    void updatebook1() {
        noofissued++;
    }

    void updatebook2() {
        noofissued--;
    }

} B;

int book::checkbook() {
    if (noofissued < noofcopies)
        return 1;
    else
        return 0;
}

class member {                                                                                        //CLASS MEMBER(2)
    int memberno;
    char name[20], address[30], mobile[15], pincode[10];
    int bookallowed, bookissued;

public:
    void M_getData();

    void M_showData();

    int retmemno() {
        return memberno;
    }

    void updatebookl() {
        bookissued++;
    }

    int checkbook();

    void updatebookR() {
        bookissued--;
    }
} M;

int member::checkbook() {
    cout << "Book Issued : " << bookissued << "," << "Book Allowed : " << bookallowed << endl;
    if (bookissued < bookallowed)
        return 1;
    else
        return 0;
}

class issued {                                                                                         //CLASS ISSUE(3)
    int bookno, memberno;
    Date issuedate, returndate, duedate;
public:
    void I_getData();

    int checkissue(int b, int m);

    int checkdate(Date dt);
} I;

int issued::checkissue(int b, int m) {
    if (bookno == b && memberno == m)
        return 1;
    else
        return 0;
}

int issued::checkdate(Date dt) {
    returndate = dt;
    if (duedate.yy <= dt.yy) {
        if (duedate.dd <= dt.dd)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

/***********FUNCTIONS************/

void addm() {                                                                                         //ADDING A MEMBER
    fstream fout("member.dat", ios::binary | ios::app);
    char ch;
    member M;
    do {
        system("clear");
        M.M_getData();
        fout.write((char *) &M, sizeof(M));
        cout << "\nThis member has been added";
        cout << "\nDo you want to add more....\nPress Y for Yes and N for No\n";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void delm() {                                                                                         //DELETE A MEMBER
    ifstream fin("member.dat", ios::binary);
    ofstream fout("tempm.dat", ios::binary);
    member M;
    int n;
    cout << "\nEnter the member number you want to delete : ";
    cin >> n;
    while (fin.read((char *) &M, sizeof(M))) {
        if (M.retmemno() != n) {
            fout.write((char *) &M, sizeof(M));
        }
    }
    cout << "\nThis member has been removed";
    remove("member.dat");
    rename("tempm.dat", "member.dat");
}

void modm() {                                                                                  //MODIFICATION IN MEMBER
    system("clear");
    ifstream fin("member.dat", ios::binary);
    ofstream fout("tempm.dat", ios::binary);
    member M;
    int n;
    cout << "\nEnter the member number you want to modify : ";
    cin >> n;
    while (fin.read((char *) &M, sizeof(M))) {
        if (M.retmemno() != n) {
            fout.write((char *) &M, sizeof(M));
        }
        else {
            M.M_getData();
            fout.write((char *) &M, sizeof(M));
        }
    }
    cout << "\nMember has been modified";
    remove("member.dat");
    rename("tempm.dat", "member.dat");
}

void addb() {                                                                                           //ADDING A BOOK
    fstream fout("book.dat", ios::binary | ios::app);
    char ch;
    book B;
    do {
        system("clear");
        B.B_getData();
        fout.write((char *) &B, sizeof(B));
        cout << "This book has been added";
        cout << "\nDo you want to add more...\nPress Y for Yes and N for No\n";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void delb() {                                                                                         //DELETING A BOOK
    ifstream fin("book.dat", ios::binary);
    ofstream fout("tempb.dat", ios::binary);
    book B;
    int n;
    cout << "\nEnter the book number you want to delete : ";
    cin >> n;
    while (fin.read((char *) &B, sizeof(B))) {
        if (B.retbookno() != n) {
            fout.write((char *) &B, sizeof(B));
        }
    }
    cout << "\nYour book has been removed!\n";
    remove("book.dat");
    rename("tempb.dat", "book.dat");
}

void modb() {                                                                                       //MODIFYING A BOOK
    system("clear");
    ifstream fin("book.dat", ios::binary);
    ofstream fout("tempb.dat", ios::binary);
    book B;
    int n;
    cout << "\nEnter the book number you want to modify : ";
    cin >> n;
    while (fin.read((char *) &B, sizeof(B))) {
        if (B.retbookno() != n) {
            fout.write((char *) &B, sizeof(B));
        }
        else {
            B.B_getData();
            fout.write((char *) &B, sizeof(B));
        }
    }
    cout << "\nYour book has been modified";
    remove("book.dat");
    rename("tempb.dat", "book.dat");
}

void member::M_getData() {                                                                   //GETTING DATA FOR A MEMBER
    cout << "Enter the member number : ";
    cin >> memberno;
    cout << "Enter the name : ";
    cin >> name;
    cout << "Enter the address : ";
    cin >> address;
    cout << "Enter the mobile number: ";
    cin >> mobile;
    cout << "Enter the pin : ";
    cin >> pincode;
    cout << "Enter the number of books allowed : ";
    cin >> bookallowed;
    bookissued = 0;
    cout << "\nBooks issued : " << bookissued;
    cout << endl;
}

void member::M_showData() {                                                                //DISPLAYING DATA FOR A MEMBER
    cout << "\nMEMBER NUMBER : " << memberno;
    cout << "\nNAME : " << name;
    cout << "\nADDRESS : " << address;
    cout << "\nMOBILE NUMBER : " << mobile;
    cout << "\nPIN : " << pincode;
    cout << "\nBOOK ALLOWED : " << bookallowed;
    cout << "\nBOOK ISSUED : " << bookissued;
    cout << endl;
}

void book::B_getData() {                                                                    //GETTING DETAILS OF A BOOK
    cout << "Enter the book number : ";
    cin >> bookno;
    cout << "Enter the title : ";
    cin >> title;
    cout << "Enter the author : ";
    cin >> author;
    cout << "Enter the publisher : ";
    cin >> publisher;
    cout << "Enter the type : ";
    cin >> type;
    cout << "Enter the price : ";
    cin >> price;
    cout << "Enter Number of copies : ";
    cin >> noofcopies;
    noofissued = 0;
}

void book::B_showData() {                                                                  //DISPLAYING DETAILS FOR BOOK
    cout << "\nBOOK NUMBER :" << bookno;
    cout << "\nTITLE : " << title;
    cout << "\nAUTHOR : " << author;
    cout << "\nPUBLISHER : " << publisher;
    cout << "\nPRICE : " << price;
    cout << endl;
}

void issued::I_getData() {                                                    //GETTING	DETAILS  FOR  THE  ISSUED BOOKS
    book B;
    member M;
    start1:
    int flag = 0;
    fstream fin("book.dat", ios::in | ios::out | ios::binary);
    cout << "\nEnter the book number : ";
    cin >> bookno;
    while (fin.read((char *) &B, sizeof(B))) {
        if (bookno == B.retbookno()) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        cout << "\nNo such book.....please try again later!\n";
        goto
                start1;
    }
    if (B.checkbook() == 1) {
        cout << "\nBook can be issued!\n";
        fin.seekp(-1*sizeof(B), ios::cur);
        B.updatebook1();
        fin.write((char *) &B, sizeof(B));
    }
    else {
        cout << "\nBook is not available!\n";
        goto
                start1;
    }
    Date D1, D2, D3;
    start2:
    fstream fin1("member.dat", ios::in | ios::out | ios::binary);
    cout << "\nEnter the member number : ";
    cin >> memberno;
    while (fin1.read((char *) &M, sizeof(M))) {
        if (memberno == M.retmemno()) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        cout << "\nNo such member...please try again later!\n";
        goto
                start2;
    }
    if (M.checkbook() == 1) {                           //checks if book issued is less than no. of allowed books
        cout << "\nMember can be issued the book!\n";
        fin1.seekp(-1*sizeof(M), ios::cur);
        M.updatebookl();
        fin1.write((char *) &M, sizeof(M));
    }
    else {
        cout << "\nBook cannot be issued\n";
        goto
                start1;
    }
    cout << "\nEnter the issue date : ";
    cin >> D1.dd;
    cout << "\nEnter the issue month :";
    cin >> D1.mm;
    cout << "\nEnter the issue year :";
    cin >> D1.yy;
    issuedate = D1;

    D2.dd = 0;
    D2.mm = 0;
    D2.yy = 0;
    returndate = D2;            //checked while returning book

    cout << "\nEnter the return date : ";
    cin >> D3.dd;
    cout << "\nEnter the return month : ";
    cin >> D3.mm;
    cout << "\nEnter the return year : ";
    cin >> D3.yy;
    duedate = D3;
}

void issue() {                                                                                      //	ADDING A MEMBER
    ofstream fout("issue.dat", ios::binary | ios::app);
    char ch;
    issued i;
    do {
        i.I_getData();
        fout.write((char *) &i, sizeof(i));
        cout << "\nThis book has been issued!";
        cout << "Do you want to issue more books....\nPress  Y  for Yes and N for No\n";
        cin >> ch;
        system("clear");
    } while (ch == 'y' | ch == 'Y');
}

void Return() {                                                                     //GETTING DETAILS FOR ISSUED BOOKS
    book B;
    int bookno, memberno;
    start1:
    int flag = 0;
    fstream fin("book.dat", ios::in | ios::out | ios::binary);
    cout << "\nEnter the book number : ";
    cin >> bookno;
    while (fin.read((char *) &B, sizeof(B))) {
        if (bookno == B.retbookno()) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        cout << "\nNo such book...Please try again later!\n";
        goto start1;
    }
    fin.seekp(-1*sizeof(B), ios::cur);
    B.updatebook2();
    fin.write((char *) &B, sizeof(B));
    Date D1;
    start2:
    fstream fin1("member.dat", ios::in | ios::out | ios::binary);
    cout << "\nEnter the member number : ";
    cin >> memberno;
    while (fin1.read((char *) &M, sizeof(M))) {
        if (memberno == M.retmemno()) {
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        cout << "\nNo such member...Please try again later!\n";
        goto start2;
    }
    cout << "\nMember returned the book\n";
    fin1.seekp(-1*sizeof(M), ios::cur);
    M.updatebookR();
    fin1.write((char *) &M, sizeof(M));

    fstream fin2("issue.dat", ios::binary | ios::in);
    fstream f3("temp.dat", ios::binary | ios::out);
    cout << "\nEnter the return date : ";
    cin >> D1.dd;
    cout << "\nEnter the return month : ";
    cin >> D1.mm;
    cout << "\nEnter the return year : ";
    cin >> D1.yy;
    issued I;
    while (fin2.read((char *) &I, sizeof(I))) {
        if (I.checkissue(bookno, memberno) == 1) {
            int x = I.checkdate(D1);
            if (x == 1)
                cout << "\n No fine";
            else
                cout << "\n Fine of Rs 10/-";
        }
        else
            f3.write((char *) &I, sizeof(I));       //writes return date into record
    }
    fin2.close();
    f3.close();
    remove("issue.dat");
    rename("temp.dat", "issue.dat");
}

void Search_book() {                                                          //SEARCH  ON  THE  BASIS  OF  BOOK NUMBER
    ifstream fin("book.dat", ios::binary);
    int n, flag = 0;
    book B;
    cout << "\nEnter the book number you want to search =  ";
    cin >> n;
    while (fin.read((char *) &B, sizeof(B))) {
        if (B.retbookno() == n) {
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        cout << "\nThe book number is found!";
        B.B_showData();
    }
    else
        cout << "\nThe book number does not exist" << "\n Please enter the another number!\n";
}

void Search_mem() {                                                         //SEARCH  ON  THE  BASIS  OF  MEMBER NUMBER
    ifstream fin("member.dat", ios::binary);
    int n, flag = 0;
    member M;
    cout << "\nEnter the member number you want to search = ";
    cin >> n;
    while (fin.read((char *) &M, sizeof(M))) {
        if (M.retmemno() == n) {
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        cout << "\nThe member number is found";
        M.M_showData();
    }
    else
        cout << "\nThe member number does not exist" << "\nPlease enter another member!\n";
}

void memlist() {
    ifstream fin("member.dat", ios::binary);
    member M;
    while (fin.read((char *) &M, sizeof(M))) {
        M.M_showData();
    }
}

void booklist() {
    ifstream fin("book.dat", ios::binary);
    book B;
    while (fin.read((char *) &B, sizeof(B))) {
        B.B_showData();
    }
}

void mm() {                                                                               //FOR OPTION 1 FROM MAIN MENU
    char choice2;
    do {
        system("clear");
        cout << "\n\t\t\t********MEMBER MANAGEMENT*******"
             << "\n\t\ta. Add a member"
             << "\n\t\tb. Delete a member"
             << "\n\t\tc. Modify a member"
             << "\n\t\td. Go back to Main Menu"
             << "\nEnter the choice = ";
        cin >> choice2;
        switch (choice2) {
            case 'a':
                addm();
                break;
            case 'b':
                delm();
                break;
            case 'c':
                modm();
                break;
            case 'd':
                return;
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice2 != 'd');
}

void bm() {                                                                              //FOR OPTION 2 FROM ADMIN MENU
    char choice3;
    do {
        system("clear");
        cout << "\n\t\t\t********BOOK MANAGEMENT*********"
             << "\n\ta. Add a book"
             << "\n\tb. Delete a book"
             << "\n\tc. Modify a book"
             << "\n\td. Return to main menu"
             << "\nEnter the choice = ";
        cin >> choice3;
        switch (choice3) {
            case 'a':
                addb();
                break;
            case 'b':
                delb();
                break;
            case 'c':
                modb();
                break;
            case 'd':
                return;
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice3 != 'd');
}

void trans() {                                                                           //FOR OPTION 3 FROM MAIN MENU
    char choice4;
    do {
        system("clear");
        cout << "\n\t\t\t********TRANSACTION**********"
             << "\n\t\ta. Issue"
             << "\n\t\tb. Return"
             << "\n\t\tc. Go back to main menu"
             << "\nEnter your choice = ";
        cin >> choice4;
        switch (choice4) {
            case 'a':
                issue();
                break;
            case 'b':
                Return();
                break;
            case 'c':
                return;
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice4 != 'c');
}

void query() {                                                                            //FOR OPTION 4 FROM MAIN MENU
    system("clear");
    char choice5;
    do {
        cout << "\n\t\t\t********QUERY********"
             << "\n\t\ta. Search on the basis of book"
             << "\n\t\tb. Search on the basis of member"
             << "\n\t\tc. Go back to main menu"
             << "\nEnter the choice = ";
        cin >> choice5;
        system("clear");
        switch (choice5) {
            case 'a':
                Search_book();
                break;
            case 'b':
                Search_mem();
                break;
            case 'c':
                return;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice5 != 'c');
}

void report() {                                                                           //FOR OPTION 5 FROM MAIN MENU
    char choice6;
    do {
        cout << "\n\t\t\t********REPORT********"
             << "\n\t\ta. Member List"
             << "\n\t\tb. Book List"
             << "\n\t\tc. Go back to main menu"
             << "\nEnter the choice = ";
        cin >> choice6;
        system("clear");
        switch (choice6) {
            case 'a':
                memlist();
                break;
            case 'b':
                booklist();
                break;
            case 'c':
                return;
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice6 != 'c');
}

int main() {                                                                                            //THE MAIN MENU
    int choice1;
    do {
        system("clear");
        cout << "\n\t\t\t********MAIN MENU*******"
             << "\n\t\t1. MEMBER MANAGEMENT"
             << "\n\t\t2. BOOK MANAGEMENT"
             << "\n\t\t3. TRANSACTION"
             << "\n\t\t4. QUERY"
             << "\n\t\t5. REPORT"
             << "\n\t\t6. EXIT";
        cout << "\n\t\tEnter your choice = ";
        cin >> choice1;
        switch (choice1) {
            case 1:
                mm();
                break;
            case 2:
                bm();
                break;
            case 3:
                trans();
                break;
            case 4:
                query();
                break;
            case 5:
                report();
                break;
            case 6:
                exit(0);
            default:
                cout << "\nInvalid choice!\n";
        }
    } while (choice1 != 6);
    return 0;
}