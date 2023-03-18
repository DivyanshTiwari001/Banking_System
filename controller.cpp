#include<bits/stdc++.h>
//Minium Amount M need to be kept
#define M 100
using namespace std;

// List of already existing accounts
vector<string> accounts;

// To fetch the list of already existing accounts
void initialize(){
    ifstream fin;
    string line;
    fin.open("data.csv");
    while(getline(fin,line)){
        accounts.push_back(line.substr(0,9));//inserting account number in the list accounts
    }
    fin.close();
}
class Account{
    private:
    string generateAccountNumber();
    public:
    int checkBalance(string);
    void withdraw(string,int);
    void deposit(string,int);
    void createAccount();
    void removeAccount(string);
};

//For Account Number Creation
string Account :: generateAccountNumber(){
    label:
    string s = to_string(100000000+rand()%1000000000);
    if(find(accounts.begin(),accounts.end(),s)==accounts.end()){
        accounts.push_back(s);
        return s;
    }
    else goto label;
}

// To Check Balance Amount
int Account::checkBalance(string accountNum){
    // Checking whether account exists
    if(find(accounts.begin(),accounts.end(),accountNum)==accounts.end())return -1;
    ifstream fin;
    vector<string> row;
    string line,word;
    fin.open("data.csv");//opening file in read mode
    while(fin){
      row.clear();//clearing vector each time for new record
      getline(fin,line);//reading record from file
      stringstream s(line);
      while(getline(s,word,',')){
         row.push_back(word);//pushing each field of record as element of row
      }
      if(row[0]==accountNum){
        fin.close();
        return stoi(row[2]);//returning balance
      }
    }
    fin.close();
}
void Account::withdraw(string accountNum,int amount){
    if(find(accounts.begin(),accounts.end(),accountNum)==accounts.end()){
        cout<<"No Such Account Exists"<<endl;
        return;
    }
    fstream fin,fout;
    vector<string> row;
    string line,word;
    fin.open("data.csv",ios::in);
    fout.open("newdata.csv",ios::out);
    while(fin){
      row.clear();
      getline(fin,line);
      if(line=="")break;
      stringstream s(line);
      while(getline(s,word,',')){
         row.push_back(word);
      }
      if(row[0]==accountNum){
        if(amount>stoi(row[2])-M){
            cout<<"Insufficient Balance"<<endl;
            fout.close();
            fin.close();
            remove("newdata.csv");
            return;
        }
        else row[2]=to_string(stoi(row[2])-amount);//updating balance after withdrawl
      }
      for(int i=0;i<row.size()-1;i++){
        fout<<row[i]<<",";
      }
      fout<<row[row.size()-1]<<"\n";
    }
    fout.close();
    fin.close();
    remove("data.csv");
    rename("newdata.csv","data.csv");
}
void Account::deposit(string accountNum,int amount){
    if(find(accounts.begin(),accounts.end(),accountNum)==accounts.end()){
        cout<<"No Such Account Exists"<<endl;
        return;
    }
    fstream fin,fout;
    vector<string> row;
    string line,word;
    fin.open("data.csv",ios::in);
    fout.open("newdata.csv",ios::out);
    while(!fin.eof()){
      row.clear();
      getline(fin,line);
      if(line=="")break;
      stringstream s(line);
      while(getline(s,word,',')){
         row.push_back(word);
      }
      if(row[0]==accountNum){
        row[2]=to_string(stoi(row[2])+amount);//updating balance after deposit
      }
      for(int i=0;i<row.size()-1;i++){
        fout<<row[i]<<",";
      }
      fout<<row[row.size()-1]<<"\n";
    }
    fout.close();
    fin.close();
    remove("data.csv");
    rename("newdata.csv","data.csv");
}
void Account::removeAccount(string accountNum){
    if(find(accounts.begin(),accounts.end(),accountNum)==accounts.end()){
        cout<<"No Such Account Exists"<<endl;
        return;
    }
    fstream fin,fout;
    vector<string> row;
    string line,word;
    fin.open("data.csv");
    fout.open("newdata.csv");
    while(fin){
      row.clear();
      getline(fin,line);
      if(line=="")break;
      stringstream s(line);
      while(getline(s,word,',')){
         row.push_back(word);
      }
      if(row[0]!=accountNum){
        for(int i=0;i<row.size()-1;i++){
            fout<<row[i]<<",";
        }
        fout<<row[row.size()-1]<<"\n";
      }
    }
    fout.close();
    fin.close();
    remove("data.csv");
    rename("newdata.csv","data.csv");
}
void Account::createAccount(){
    string name,accountNumber;
    int balance = M;
    cout<<"Enter Your Full Name: ";
    cin.ignore();
    getline(cin,name);
    accountNumber=generateAccountNumber();
    fstream fout;
    fout.open("data.csv",ios::app);
    fout<<accountNumber<<","<<name<<","<<balance<<"\n";
    fout.close();
    cout<<"Account Created:"<<endl
        <<"Account Holder: "+name<<endl
        <<"Account Number: "+accountNumber<<endl
        <<"Current Balance: "+to_string(balance)<<endl;
}
int main(){
    initialize();
    Account ac;
    int n=-1;
    while(n!=0){
        cout<<"--------------------------------"<<endl
            <<"| Task                 : Code  |"<<endl
            <<"--------------------------------"<<endl
            <<"| Create Account       :   1   |"<<endl
            <<"| Deposit Amount       :   2   |"<<endl
            <<"| Withdraw Amount      :   3   |"<<endl
            <<"| Check Balance Amount :   4   |"<<endl
            <<"| Remove Account       :   5   |"<<endl
            <<"| Exit                 :   0   |"<<endl
            <<"--------------------------------"<<endl;
        cin>>n;
        if(n==1){
            ac.createAccount();
        }
        if(n==2){
            string accNum;
            int amount;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            cout<<"Enter Deposit Amount: ";
            cin>>amount;
            ac.deposit(accNum,amount);
        }
        if(n==3){
            string accNum;
            int amount;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            cout<<"Enter Withdrawl Amount: ";
            cin>>amount;
            ac.withdraw(accNum,amount);
        }
        if(n==4){
            string accNum;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            cout<<"Your Account Balance : "+to_string(ac.checkBalance(accNum))<<endl;
        }
        if(n==5){
            string accNum;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            ac.removeAccount(accNum);
            cout<<"Account Successfully Closed"<<endl;
        }
    }
    getchar();
    return 0;
}