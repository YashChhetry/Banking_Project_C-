#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

//----------structure for main account-----
struct main1 {
    long int acno;
    char acctype;
    string custname;
    float balance;
} M[100] = {
    {1, 's', "a", 500},
    {2, 's', "b", 500},
    {3, 'c', "c", 2000},
    {4, 's', "d", 500},
    {5, 'c', "e", 2000},
    {6, 'c', "f", 2000}
};

//---------structure for transaction account-----
struct trans {
    long int acno;
    char ttype;
    float amount;
} T[100];

int mp = 6, tp = 0;

//------- Keeping records in main account------
void create() {
    char choice;
    do {
        cout << "\n Entering New Records.";
        cout << "\n Enter Account Number:"; cin >> M[mp].acno;
        cout << "\n Enter Customer Name:"; cin.ignore(); getline(cin, M[mp].custname);
        cout << "\n Enter Account Type[S-Savings C-Current]:"; cin >> M[mp].acctype;
        if (M[mp].acctype == 'S' || M[mp].acctype == 's')
            M[mp].balance = 500;
        else if (M[mp].acctype == 'C' || M[mp].acctype == 'c')
            M[mp].balance = 2000;

        mp++;
        cout << "\n Do you want to add more records[y/n]"; cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

//--------Displaying Records----
void disprec() {
    for (int i = 0; i < mp; i++) {
        cout << "\n" << setw(10) << M[i].acno << setw(25) << M[i].custname
             << setw(20) << M[i].acctype << setw(15) << M[i].balance;
    }
}

//----------------Modifying Records
void modify() {
    char vacctype;
    string vcustname;
    long int vacno;
    int i = 0;
    bool found = false;
    main1 temp;

    cout << "\n Enter the Account Number to Modify:"; cin >> vacno;
    while (i < mp) {
        if (M[i].acno == vacno) {
            found = true;
            cout << "\n Account No:" << M[i].acno;
            temp.acno = M[i].acno;
            cout << "\n Account Type:" << M[i].acctype;
            cout << "\n Enter New Account Type ('.' to skip):";
            cin >> vacctype;
            if (vacctype == '.')
                temp.acctype = M[i].acctype;
            else
                temp.acctype = vacctype;

            cout << "\n Customer Name:" << M[i].custname;
            cout << "\n Enter New Customer Name ('.' to skip):";
            cin.ignore(); getline(cin, vcustname);
            if (vcustname == ".")
                temp.custname = M[i].custname;
            else
                temp.custname = vcustname;

            float bal;
            temp.balance = 0;
            bal = M[i].balance - 2000;
            if (bal < 0) {
                cout << "\n Kindly deposit Rs." << abs(bal) << " to maintain minimum balance";
                temp.balance = abs(bal);
            }
            temp.balance += M[i].balance;
            break;
        }
        i++;
    }

    if (found) {
        char ans;
        cout << "\n Do you want to keep changes[y/n]:"; cin >> ans;
        if (ans == 'y' || ans == 'Y')
            M[i] = temp;
        else
            cout << "\n Changes Discarded";
    } else {
        cout << "\n Record Not Found";
    }
}

//--------------Searching an account
void search() {
    long int vacno;
    int i = 0;
    bool found = false;
    cout << "\n Enter the Account Number to Search:"; cin >> vacno;
    while (i < mp) {
        if (M[i].acno == vacno) {
            found = true;
            cout << "\n Account No:" << M[i].acno;
            cout << "\n Account Type:" << M[i].acctype;
            cout << "\n Customer Name:" << M[i].custname;
            cout << "\n Balance:" << M[i].balance;
        }
        i++;
    }
    if (!found)
        cout << "\n Record Not Found";
}

//------------ Deleting an account
void delacc() {
    long int vacno;
    int i = 0;
    bool found = false;
    cout << "\n Enter the Account Number to delete:"; cin >> vacno;
    while (i < mp) {
        if (M[i].acno == vacno) {
            char ans;
            found = true;
            cout << "\n Account No:" << M[i].acno;
            cout << "\n Account Type:" << M[i].acctype;
            cout << "\n Customer Name:" << M[i].custname;
            cout << "\n Balance:" << M[i].balance;

            cout << "\n Do you want to delete above record[y/n]:"; cin >> ans;
            if (ans == 'y' || ans == 'Y') {
                for (; i < mp - 1; i++)
                    M[i] = M[i + 1];
                mp--;
                cout << "\n Record Deleted";
            } else {
                cout << "\n Record remain intact";
            }
            break;
        }
        i++;
    }
    if (found)
        cout << "\n Process completed successfully";
    else
        cout << "\n Record not found";
}

//--------------Function for deposit
void deposit() {
    long int vacno;
    int i = 0;
    bool found = false;
    cout << "\n Enter the Account Number to Deposit:"; cin >> vacno;
    while (i < mp) {
        if (M[i].acno == vacno) {
            found = true;
            break;
        }
        i++;
    }
    if (!found)
        cout << "\n Account doesn't exist!!!";
    else {
        cout << "\n Enter Amount :";
        cin >> T[tp].amount;
        T[tp].acno = vacno;
        T[tp].ttype = 'D';
        M[i].balance += T[tp].amount;
        tp++;
        cout << "\n Amount deposited successfully";
    }
}

//-------------Function to withdraw amount---------
void withdraw() {
    long int vacno;
    int i = 0;
    bool found = false;
    cout << "\n Enter the Account Number to Withdraw:"; cin >> vacno;
    while (i < mp) {
        if (M[i].acno == vacno) {
            found = true;
            break;
        }
        i++;
    }
    if (!found)
        cout << "\n Account doesn't exist!!!";
    else {
        float amt, bal;
        cout << "\n Enter Amount :";
        cin >> amt;
        bal = M[i].balance - amt;
        if (amt < M[i].balance) {
            if ((M[i].acctype == 's' || M[i].acctype == 'S') && bal < 500)
                cout << "\n Balance is less than Minimum Balance";
            else if ((M[i].acctype == 'c' || M[i].acctype == 'C') && bal < 2000)
                cout << "\n Balance is less than Minimum Balance";
            T[tp].acno = vacno;
            T[tp].ttype = 'W';
            T[tp].amount = amt;
            M[i].balance -= T[tp].amount;
            tp++;
            cout << "\n Amount successfully withdrawn";
        } else {
            cout << "\n Insufficient Fund";
        }
    }
}

//------------Report of Deposit Amount
void reportD() {
    float totalamt = 0.0;
    for (int i = 0; i < tp; i++) {
        if (T[i].ttype == 'D') {
            cout << "\n" << T[i].acno << "\t" << T[i].amount;
            totalamt += T[i].amount;
        }
    }
    cout << "\n Total Amount Deposited :" << totalamt;
}

//------------Report of Withdrawn Amount
void reportW() {
    float totalamt = 0.0;
    for (int i = 0; i < tp; i++) {
        if (T[i].ttype == 'W') {
            cout << "\n" << T[i].acno << "\t" << T[i].amount;
            totalamt += T[i].amount;
        }
    }
    cout << "\n Total Amount Withdrawn :" << totalamt;
}

//----------------------- Menu for ABS Banking System
void menu() {
    int choice;
    do {
        cout << "\n\nABS Banking System";
        cout << "\n 1. Creating a new Account.";
        cout << "\n 2. Display Account Detail.";
        cout << "\n 3. Modifying an existing Account.";
        cout << "\n 4. Searching an Account.";
        cout << "\n 5. Delete Account.";
        cout << "\n 6. Deposit Amount.";
        cout << "\n 7. Withdrawal Amount.";
        cout << "\n 8. Report - Deposit.";
        cout << "\n 9. Report - Withdrawal";
        cout << "\n 10. Quit";
        cout << "\n Enter your choice[1-10]:";
        cin >> choice;
        switch (choice) {
            case 1: create(); break;
            case 2: disprec(); break;
            case 3: modify(); break;
            case 4: search(); break;
            case 5: delacc(); break;
            case 6: deposit(); break;
            case 7: withdraw(); break;
            case 8: reportD(); break;
            case 9: reportW(); break;
            case 10:
                cout << "\n Exiting from the program";
                exit(0);
            default:
                cout << "\n Enter appropriate choice[1--10]";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 10);
}

int main() {
    menu();
    return 0;
}
