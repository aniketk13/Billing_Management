// //***************************************************************
// //                   HEADER FILE USED IN PROJECT
// //****************************************************************

// // #include <windows.h>
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
enum IN
{
    // 13 is ASCII for carriage
    // return
    IN_BACK = 8,
    IN_RET = 13

};

// //***************************************************************
// //                   CLASS USED IN PROJECT
// //****************************************************************

class product
{
    int pno;
    string name;
    float price, qty, tax, dis;

public:
    product()
    {
        pno = 0;
        name = "";
        price = qty = tax = dis = 0.0;
    }
    void create_product()
    {
        cout << "\nPlease Enter The Product No. of The Product ";
        cin >> pno;
        cout << "\n\nPlease Enter The Name of The Product ";
        cin >> name;
        // for (int i = name.length() - 1; i <= 20; i++)
        //     name += " ";
        cout << name << "1" << endl;
        cout << "\nPlease Enter The Price of The Product ";
        cin >> price;
        cout << "\nPlease Enter The Discount (%) ";
        cin >> dis;
    }

    void show_product()
    {
        cout << "\nThe Product No. of The Product : " << pno;
        cout << "\nThe Name of The Product : ";
        cout << name;
        cout << "\nThe Price of The Product : " << price;
        cout << "\nDiscount : " << dis;
    }

    int retpno()
    {
        return pno;
    }

    float retprice()
    {
        return price;
    }

    string retname()
    {
        return name;
    }

    int retdis()
    {
        return dis;
    }

}; //class ends here

//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

fstream fp;
// fstream fp2;
product pr;

//***************************************************************
//    	function to write in file
//****************************************************************
// Function that accepts the password
string takePasswdFromUser(char sp = '*')
{
    // Stores the password
    string passwd = "";
    char ch_ipt;
    cout << "Enter password: ";
    // Until condition is true
    while (true)
    {

        ch_ipt = getch();

        // if the ch_ipt
        if (ch_ipt == IN::IN_RET)
        {
            cout << endl;
            return passwd;
        }
        else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
        {
            passwd.pop_back();

            // Cout statement is very
            // important as it will erase
            // previously printed character
            cout << "\b \b";

            continue;
        }

        // Without using this, program
        // will crash as \b can't be
        // print in beginning of line
        else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
        {
            continue;
        }

        passwd.push_back(ch_ipt);
        cout << sp;
    }
}
void write_product()
{
    fp.open("Shop.dat", ios::out | ios::app);
    pr.create_product();
    fp.write((char *)&pr, sizeof(product));
    fp.close();
    cout << "\n\nThe Product Has Been Created ";
}

//***************************************************************
//    	function to read all records from file
//****************************************************************

void display_all()
{
    cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", ios::in);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        pr.show_product();
        cout << "\n\n====================================\n";
    }
    fp.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
    int flag = 0;
    fp.open("Shop.dat", ios::in);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        if (pr.retpno() == n)
        {
            pr.show_product();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0)
        cout << "\n\nrecord not exist";
}

//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_product()
{
    int no, found = 0;
    cout << "\n\n\tTo Modify ";
    cout << "\n\n\tPlease Enter The Product No. of The Product";
    cin >> no;
    fp.open("Shop.dat", ios::in | ios::out);
    while (fp.read((char *)&pr, sizeof(product)) && found == 0)
    {
        if (pr.retpno() == no)
        {
            pr.show_product();
            cout << "\nPlease Enter The New Details of Product" << endl;
            pr.create_product();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, ios::cur);
            fp.write((char *)&pr, sizeof(product));
            cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        cout << "\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_product()
{
    int no;
    cout << "\n\n\n\tDelete Record";
    cout << "\n\nPlease Enter The product no. of The Product You Want To Delete";
    cin >> no;
    fp.open("Shop.dat", ios::in | ios::out);
    fstream fp2;
    fp2.open("Temp.dat", ios::out);
    fp.seekg(0, ios::beg);
    while (fp.read((char *)&pr, sizeof(product)))
    {
        if (pr.retpno() != no)
        {
            fp2.write((char *)&pr, sizeof(product));
        }
    }
    fp2.close();
    fp.close();
    remove("Shop.dat");
    rename("Temp.dat", "Shop.dat");
    cout << "\n\n\tRecord Deleted ..";
}

// //***************************************************************
// //    	function to display all products price list
// //****************************************************************

void menu()
{
    fp.open("Shop.dat", ios::in);
    if (!fp)
    {
        cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
        cout << "\n\n\n Program is closing ....";

        exit(0);
    }

    cout << "\n\n"
         << setw(75) << "Product MENU\n\n";
    cout << setw(94) << "====================================================\n";
    cout << setw(40) << "Product No." << setw(40) << "Product Name" << setw(40) << "Price\n";
    cout << setw(94) << "====================================================\n";

    while (fp.read((char *)&pr, sizeof(product)))
    {
        cout << setw(50) << pr.retpno() << setw(25) << pr.retname() << setw(25) << pr.retprice() << endl;
    }
    fp.close();
}

// //***************************************************************
// //    	function to place order and generating bill for Products
// //****************************************************************

void place_order()
{
    int order_arr[50], quan[50], c = 0;
    float amt, damt, total = 0;
    char ch = 'Y';

    //Ask Customer for Name and Phone Number. //Oniket
    menu();
    // fp.open("Shop.dat", ios::in);
    // fp.read((char *)&pr, sizeof(product));
    cout << "\n============================";
    cout << "\n    PLACE YOUR ORDER";
    cout << "\n============================\n";
    fstream fp2;
    fp2.open("invoice.txt", ios::out | ios::app);
    do
    {
        cout << "\n\nEnter The Product No. Of The Product : ";
        cin >> order_arr[c];
        cout << "\nQuantity in number : ";
        cin >> quan[c];
        // fp2 << order_arr[c] << "\t" << pr.retname() << "\t" << quan[c] << "\n";
        c++;

        cout << "\nDo You Want To Order Another Product ? (y/n)";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\nThank You For Placing The Order";

    cout << "\n\n********************************INVOICE************************\n";
    cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
    for (int x = 0; x < c; x++)
    {
        fp.open("Shop.dat", ios::in);
        fp.read((char *)&pr, sizeof(product));
        while (!fp.eof())
        {
            if (pr.retpno() == order_arr[x])
            {
                amt = pr.retprice() * quan[x];
                damt = amt - (amt * pr.retdis() / 100);
                cout << "\n"
                     << order_arr[x] << "\t" << pr.retname() << "\t" << quan[x] << "\t\t" << pr.retprice() << "\t" << amt << "\t\t" << damt;
                fp2 << "\n"
                    << setw(10)
                    << order_arr[x] << setw(10) << "\t" << setw(10) << pr.retname() << "\t" << setw(10) << quan[x] << "\t\t" << setw(10) << pr.retprice() << "\t" << setw(10) << amt << "\t\t" << damt;
                total += damt;
            }
            fp.read((char *)&pr, sizeof(product));
        }

        fp.close();
    }
    cout << "\n\n\t\t\t\t\tTOTAL = " << total;
    fp2 << "\n\n\t\t\t\t\tTOTAL = " << total;
}
// void gotoxy(short x, short y)
// {
//     COORD pos = {x, y};
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
// }
// //***************************************************************
// //    	INTRODUCTION FUNCTION
// //****************************************************************

void intro()
{
    cout << "\t\t\t\t\t\t\tSUPER MARKET\n\n";
    cout << "\t\t\t\t\t\t\tBILLING";
    // Input customer details
    // string name;
    // string name2;
    // long phno;
    // cout << "\n\n\t Please Enter Customer Name: ";
    // getline(cin, name);
    // getline(cin, name2);
    // cout << "\n\n\t" << name;
    // cout << "\n\n\t Phone Number: ";
    // cin>>phno;
    // cout << "\n\n\tSCHOOL : GITARATTAN JINDAL PUBLIC SCHOOL";
}
// //***************************************************************
// //    	ADMINSTRATOR MENU FUNCTION
// //****************************************************************
void admin_menu()
{ //Add pass word for admin login //Oniket
    string inp = takePasswdFromUser();
    if (inp == "admin101")
    {
        int ch2;
        cout << "\n\n\n\tADMIN MENU";
        cout << "\n\n\t1.CREATE PRODUCT";
        cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
        cout << "\n\n\t3.QUERY "; //will show details of a specific product of input number
        cout << "\n\n\t4.MODIFY PRODUCT";
        cout << "\n\n\t5.DELETE PRODUCT";
        cout << "\n\n\t6.VIEW PRODUCT MENU";
        cout << "\n\n\t7.BACK TO MAIN MENU";
        cout << "\n\n\tPlease Enter Your Choice (1-7) ";
        cin >> ch2;

        switch (ch2)
        {
        case 1:
            write_product();
            break;
        case 2:
            display_all();
            break;
        case 3:
            int num;
            cout << "\n\n\tPlease Enter The Product No. ";
            cin >> num;
            display_sp(num);
            break;
        case 4:
            modify_product();
            break;
        case 5:
            delete_product();
            break;
        case 6:
            menu();

        case 7:
            break;
        default:
            cout << "\a";
            admin_menu();
        }
    }
    else
    {
        cout << "Incorrect Password" << endl;
        exit(0);
    }
}

// //***************************************************************
// //    	THE MAIN FUNCTION OF PROGRAM
// //****************************************************************

int main()
{
    int ch;
    intro(); //Taking customer details as input
    do
    {
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. CUSTOMER";
        cout << "\n\n\t02. ADMINISTRATOR";
        cout << "\n\n\t03. EXIT";
        cout << "\n\n\tPlease Select Your Option (1-3) ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            place_order();

            break;
        case 2:

            admin_menu();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "\a";
        }
    } while (ch != 3);
    return 0;
}

// //***************************************************************
// //    			END OF PROJECT
// //***************************************************************