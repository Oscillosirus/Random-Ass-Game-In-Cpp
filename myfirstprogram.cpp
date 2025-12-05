#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
using namespace nlohmann::literals;


json readJsonFile(const string& filename){
  ifstream file(filename);
  json data;
  if (file.is_open()) {
    file >> data;
    file.close();
    cout << "Reading Data From Json";
  } else {
    cerr << "File Could Not Be Opened" << filename;
  }
  return data;
}

void writeJsonFile(const string& filename, const json& data_to_write) {
  ofstream file(filename);
  if (file.is_open()) {
    file << setw(4) << data_to_write;
    file.close();
    cout << "Writing Data To Json";
  } else {
    cerr << "File Could Not Be Opened" << filename;
  }
 }

string quotes = " you are \"gay\".";
string fullname;
int Stored_PassKey = 0;

bool y_n(string prompt = "y/n?: " ) {
  string input;
  while (true) {
    cout << prompt;
    cin >> input;

    if (input == "y") {
      return true;
    } else if (input == "n") {
        return false;
        } else {
          cout << "Invalid Input. Please Try Again" << "\n";
          }
  }
}

class PassKeyStuff {
  public:
    int Passkey() {
      int PassKey;
      while (true) {
        json config_data = readJsonFile("Profiles.json");
          if (!config_data.empty()) {
            cout << "Writing Json Data To Script" << "\n";
              if (config_data.contains("Stored_PassKey")) {
                Stored_PassKey = config_data["Stored_PassKey"].get<int>();
                cout << "Success" << "\n\n";
        }
    } else {
      cout << "Failed To Load";
      }
      cout << "Enter Passkey: ";
      cin >> PassKey;
      if (PassKey == Stored_PassKey) {
        cout << "Passkey Correct." << "\n\n";
        return 1;
      } else {
        cout << "Passkey Incorrect." << "\n" << "Please Try Again." << "\n\n";
      }
    }
    }
  };

int Passkey_Changer() {
  bool change_passkey = y_n("Do you wish to change your passkey? y/n: ");
  if (change_passkey == true) {
      PassKeyStuff myObj;
      if (myObj.Passkey() == 1) {
        cout << "Enter New Passkey: ";
        cin >> Stored_PassKey;
        bool confirm_change = y_n("Confirm Passkey Change. y/n: ");
        if (confirm_change == true) {
          json config_data = readJsonFile("Profiles.json");
          if (!config_data.empty() && config_data.contains("Stored_PassKey")) {
            config_data["Stored_PassKey"] = Stored_PassKey;
            writeJsonFile("Profiles.json", config_data);
            cout << "\n" << "Passkey Successfully Changed To" << " " << Stored_PassKey << "\n\n";
      }
  } else if (change_passkey == false) {
        cout << "false";
        return 0;
        }
}
  }
  return 0;
}

string Create_Account() {
  string First_Name;
  string Last_Name;
  string New_Username;
  string New_Passkey;
  string Passkey_Confirm;
  int current_id;

  cout << "Enter Your First Name: ";
  cin >> First_Name;

  cout << "Enter Your Last Name: ";
  cin >> Last_Name;

  cout << "\n" << "Enter Your New Username" << "\n" << " Must End In '@here'" << "\n" << " Must Have No Capitalised Letters" << "\n" << " Use '.' '-' '_' As Spaces" << "\n" << "Enter Here:";
  cin >> New_Username;

  do{
    cout << "\n" << "Enter Your New Passkey: ";
    cin >> New_Passkey;
    cout << "Enter Your New Passkey Again: ";
    cin >> Passkey_Confirm;
    if (New_Passkey != Passkey_Confirm)
      cerr << "Passkeys Do Not Match";
  } while (New_Passkey != Passkey_Confirm);

  json config_data = readJsonFile("Profiles.json");
  if (config_data.empty()) {
    cout << "Failed To Load Data";
    }
  if (config_data.contains("Account_Count")) {
    current_id = config_data["Account_Count"].get<int>();
  } else {
    // If the counter is missing, initialize it to 1
    config_data["Account_Count"] = 1;
    current_id = 0;
  }
  json new_accounts;
  new_accounts["First_Name"] = First_Name;
  new_accounts["Last_Name"] = Last_Name;
  new_accounts["Username"] = New_Username;
  new_accounts["Passkey"] = New_Passkey;
  new_accounts["Account_ID"] = current_id + 1;
  if (!config_data.contains("Accounts") || !config_data["Accounts"].is_array()) {
    config_data["Accounts"] = json::array();
  }
  config_data["Accounts"].push_back(new_accounts);
  config_data["Account_Count"] = current_id + 1;
  writeJsonFile("Profiles.json", config_data);
  cout << "Accout Under " << New_Username << " Created Successfully";
  return New_Username;
}

string Login() {
  string Username;
  string Passkey;
  string First_Name;
  string username;
  string failed;
  string passkey;
  json login_details = readJsonFile("Profiles.json");
  if (login_details.contains ("Accounts"))
  cout << "Enter Username: ";
  cin >> Username;
  cout << "\n\n" << "Enter Passkey: ";
  cin >> Passkey;
    if (Username == username && Passkey == passkey) {
      cout << "Welcome " << First_Name;
      } else if (Username != passkey || Passkey != passkey) {
        cout << "Username Or Passkey Incorrect" << "\n" << "Please Try Again";
      }

  return 0;
}

int Sign_In_Section() {
  int SignIn = 1;
  int CreateAccount = 2;
  int choice;
  cout << "Enter 1 To Sign In To An Existing Account" << "\n" << "Enter 2 To Create A New Account" << "\n" << "Enter Here: ";
  cin >> choice;
  if (choice == SignIn) {
    Login();
  } else if (choice == CreateAccount) {
    Create_Account();
  } else {
    cout << "Invalid Input" << "Please Try Again";
  }
  return 0;
}


/*-------------------UNFINNISHED--------------------
string Deltete_Account(){
  cin bool delete_this_account = y_n("Are You Sure You Wish To Delete Your Account? y/n: ");
    if( delete_this_account == true) {
//Add a way to delete accounts after i figure out how to make new accounts without hardcoding and have them movable to and from the Data.json
    }
}
*/

int main() {
  json config_data = readJsonFile("Profiles.json");
  if (!config_data.empty()) {
    cout << "Writing Json Data To Script" << "\n";
     if (config_data.contains("Stored_PassKey")) {
            Stored_PassKey = config_data["Stored_PassKey"].get<int>();
            cout << "Success" << "\n\n";
        }
    } else {
      cout << "Failed To Load";
      }
  cout << "Welcome" << "\n\n";
  Sign_In_Section();
  //PassKeyStuff myObj;
 // myObj.Passkey();

  //cin.ignore();
 // getline (cin, fullname);
 // cout << "nice to meet you: " << fullname << "\n";
 // Passkey_Changer();
  return 0;
}






