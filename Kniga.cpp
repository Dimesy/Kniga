#include <iostream>
#include <conio.h>

using namespace std;

struct Contact
{
    char fname[60];
    char sname[30];
    char address[150];
    char age[5];
    char phone[20];
};

const unsigned int EXT = 5; //расширение массива

/*
добавление нового контакта.
*/
void AddContact(Contact**&, int&, int&, Contact*);
void ShowContact(Contact* [], int);
int SaveNoteBook(Contact**, int);
int LoadNoteBook(Contact**&, int&, int&);
void DeleteContact(Contact**&, int, int&, int);
void EditContact(Contact**&, int, Contact*);
void Find(Contact**, int, char[], bool);

void main()
{
    int size = 0;
    int count = 0;
    int ContactNumber;

    Contact** MainPtr = new Contact * [size];

    char MenuChoise, Exit, del;
    //сортировка булом

    do
    {
        do
        {
            system("cls");
            cout << "******** NOTE BOOK ********" << endl << endl;
            cout << "(1) ADD NEW CONTACT" << endl << "(2) EDIT CONTACT" << endl << "(3) DELETE CONTACT" << endl
                << "(4) SHOW ALL CONTACTS" << endl << "(5) SHOW ONE CONTACT" << endl << "(6) FIND CONTACT" <<
                endl << "(7) SAVE FILE" << endl << "(8) LOAD FILE" << endl << "(9) EXIT" << endl << endl;
            MenuChoise = _getch();
        } while (MenuChoise != '1' && MenuChoise != '2' && MenuChoise != '3' && MenuChoise != '4'
            && MenuChoise != '5' && MenuChoise != '6' && MenuChoise != '7' && MenuChoise != '8' && MenuChoise != '9');

        switch (MenuChoise)
        {
        case '1':
        {Contact* n_contact = new Contact;
        cout << "Entering new contact..." << endl << endl;
        cout << "Enter first name: " << endl;
        gets_s(n_contact->fname);
        cout << "Enter second name: " << endl;
        gets_s(n_contact->sname);
        cout << "Enter address: " << endl;
        gets_s(n_contact->address);
        cout << "Enter age: " << endl;
        gets_s(n_contact->age);
        cout << "Enter phone number (10 digits): " << endl;
        gets_s(n_contact->phone);

        AddContact(MainPtr, size, count, n_contact);

        delete n_contact;
        n_contact = nullptr; }
        break;
        case '2':
            cout << "Enter the number of contact to edit: " << endl;
            fflush(stdin);
            cin >> ContactNumber;
            fflush(stdin);
            if (ContactNumber > count || ContactNumber < 1)
            {
                cout << "No such contact found." << endl;
                break;
            }
            ShowContact(MainPtr, ContactNumber - 1);

            {Contact* n_contact = new Contact;
            cout << endl << "Editing contact " << ContactNumber << "..." << endl << endl;
            cout << "Enter  new first name: " << endl;
            gets_s(n_contact->fname);
            cout << "Enter new second name: " << endl;
            gets_s(n_contact->sname);
            cout << "Enter new address: " << endl;
            gets_s(n_contact->address);
            cout << "Enter new age: " << endl;
            gets_s(n_contact->age);
            cout << "Enter new phone number (10 digits): " << endl;
            gets_s(n_contact->phone);

            EditContact(MainPtr, ContactNumber - 1, n_contact);

            delete n_contact;
            n_contact = nullptr; }
            break;
        case '3':
            cout << "Enter the number of contact to delete: " << endl;
            fflush(stdin);
            cin >> ContactNumber;
            if (ContactNumber > count || ContactNumber < 1)
            {
                cout << "No such contact found." << endl;
                break;
            }

            do
            {
                ShowContact(MainPtr, ContactNumber - 1);
                cout << endl << "Are you sure to delete this contact? (1 - yes, 0 - no)" << endl;
                fflush(stdin);
                del = _getch();
            } while (del != '1' && del != '0');

            if (del == '0')
            {
                break;
            }
            DeleteContact(MainPtr, size, count, ContactNumber - 1);
            break;
        case '4':
            if (!count)
            {
                cout << "No contacts found." << endl;
                break;
            }

            for (int i = 0; i < count; i++)
            {
                ShowContact(MainPtr, i);
            }
            break;
        case '5':
            cout << "Enter the number of contact: " << endl;
            fflush(stdin);
            cin >> ContactNumber;
            if (ContactNumber > count || ContactNumber < 1)
            {
                cout << "No such contact found." << endl;
                break;
            }
            ShowContact(MainPtr, ContactNumber - 1);
            break;
        case '6':
            do
            {
                system("cls");
                cout << "******** FIND ********" << endl << endl;
                cout << "(1) FIND BY NAME" << endl << "(2) FIND BY PHONE" << endl << endl;
                MenuChoise = _getch();
            } while (MenuChoise != '1' && MenuChoise != '2');

            switch (MenuChoise)
            {
            case '1':
                char Name[50];
                cout << "Enter text to find by name: ";
                fflush(stdin);
                gets_s(Name);
                Find(MainPtr, count, Name, true);
                break;
            case '2':
                char Phone[11];
                cout << "Enter digits to find by phone: ";
                fflush(stdin);
                gets_s(Phone);
                Find(MainPtr, count, Phone, false);
                break;
            }
        case '7':
            SaveNoteBook(MainPtr, count);
            break;
        case '8':
            LoadNoteBook(MainPtr, count, size);
            break;
        case '9':
            return;
        }

        cout << endl << "Do you want to make another operation? (1 - yes, 0 - no)" << endl;
        fflush(stdin);
        Exit = _getch();
    } while (Exit != '0');

    for (int i = 0; i < count; i++)
    {
        delete MainPtr[i];
    }
    delete[]MainPtr;
    MainPtr = nullptr;
}

void AddContact(Contact**& notebook, int& size, int& count, Contact* NewContact)
{
    if (count == size) //расширяем массив, если нет свободного места
    {
        size += EXT;
        Contact** temp = new Contact * [size];
        for (int i = 0; i < count; i++)
        {
            temp[i] = notebook[i];
        }

        delete[]notebook;
        notebook = temp;
    }

    notebook[count] = new Contact; //создание новой структуры

    //копирование новой структуры в первую свободный элемент массива
    *notebook[count]->fname = *NewContact->fname;
    strcpy_s(notebook[count]->fname, 30, NewContact->fname);

    *notebook[count]->sname = *NewContact->sname;
    strcpy_s(notebook[count]->sname, 30, NewContact->sname);

    *notebook[count]->address = *NewContact->address;
    strcpy_s(notebook[count]->address, 150, NewContact->address);

    *notebook[count]->age = *NewContact->age;
    strcpy_s(notebook[count]->age, 5, NewContact->age);

    *notebook[count]->phone = *NewContact->phone;
    strcpy_s(notebook[count]->phone, 20, NewContact->phone);

    cout << endl << "New cоntact has been added:" << endl;
    ShowContact(notebook, count);
    count++;
}

void ShowContact(Contact* ptr[], int index)
{
    cout << endl << "Contact number: " << index + 1 << endl;
    cout << "First name: " << (*ptr[index]).fname << endl;
    cout << "Second name: " << (*ptr[index]).sname << endl;
    cout << "Address: " << (*ptr[index]).address << endl;
    cout << "Age: " << (*ptr[index]).age << endl;
    cout << "Phone number: " << (*ptr[index]).phone << endl;
}

int SaveNoteBook(Contact** NoteBook, int count)
{
    int c = 0;
    FILE* file;

    // открываем файл
    fopen_s(&file, "Notebook.bin", "wb");

    // записываем размер массива
    fwrite(&count, sizeof(int), 1, file);

    // в цикле получаем из массива очередную структуру
    // и записываем в файл
    for (int i = 0; i < count; i++)
    {
        // записываем структуру
        fwrite(NoteBook[i], sizeof(Contact), 2, file);

        // освобождаем память где хранилась уже 
        // записанная структура
        delete NoteBook[i];
        c++;
    }

    // закрываем файл
    fclose(file);

    // удаляем массив указателей
    delete[]NoteBook;

    cout << "File is saved." << endl;

    // возвращаем кол-во записанных структур
    return c;
}

int LoadNoteBook(Contact**& NoteBook, int& count, int& size_book)
{
    int c = 0;
    FILE* file = nullptr;
    // открыть файл
    errno_t er = fopen_s(&file, "NoteBook.bin", "rb");

    // проверка на ошибку открытия
    if (er != 0)
        return 0;

    // считываем размер массива
    fread_s(&c, sizeof(int), sizeof(int), 1, file);

    // проверяем считанный размер
    if (c <= 0)
        return 0;

    // временная переменная  
    Contact item;

    // в цикле считываем по одной структуре из файла и 
    // передаём в функцию AddContact для копирования в массив
    for (int i = 0; i < c; i++)
    {
        // считываем структуру
        fread_s(&item, sizeof(Contact), sizeof(Contact), 1, file);

        // добавляем элемент в массив
        AddContact(NoteBook, size_book, count, &item);
    }

    // закрываем файл
    fclose(file);
    file = nullptr;

    cout << "File is loaded." << endl;

    // возвращаем кол-во считанных структур
    return c;
}
// поиск изменение контакта 
void DeleteContact(Contact**& notebook, int size, int& count, int index)
{
    Contact** temp = new Contact * [size];

    for (int i = 0; i < index; i++)
    {
        temp[i] = notebook[i];
    }
    for (int i = index; i < count; i++)
    {
        temp[i] = notebook[i + 1];
    }

    delete[]notebook;
    notebook = temp;
    count--;

    cout << endl << "Cоntact has been removed." << endl;
}

void EditContact(Contact**& notebook, int index, Contact* NewContact)
{
    *notebook[index]->fname = *NewContact->fname;
    strcpy_s(notebook[index]->fname, 30, NewContact->fname);

    *notebook[index]->sname = *NewContact->sname;
    strcpy_s(notebook[index]->sname, 30, NewContact->sname);

    *notebook[index]->address = *NewContact->address;
    strcpy_s(notebook[index]->address, 150, NewContact->address);

    *notebook[index]->age = *NewContact->age;
    strcpy_s(notebook[index]->age, 5, NewContact->age);

    *notebook[index]->phone = *NewContact->phone;
    strcpy_s(notebook[index]->phone, 20, NewContact->phone);

    cout << endl << "The cоntact has been edited:" << endl;
    ShowContact(notebook, index);
}

void Find(Contact** notebook, int count, char string[], bool what)
{
    int num = 0;

    for (int i = 0; i < count; i++)
    {
        if (what)
        {
            if ((strstr((*notebook[i]).fname, string)) != nullptr || (strstr((*notebook[i]).sname, string)) != nullptr)
            {
                ShowContact(notebook, i);
                num++;
            }
        }
        else
        {
            if ((strstr((*notebook[i]).phone, string)) != nullptr)
            {
                ShowContact(notebook, i);
                num++;
            }
        }

    }
    if (!num)
    {
        cout << endl << "No contact found, sorry." << endl << endl;
    }
}
