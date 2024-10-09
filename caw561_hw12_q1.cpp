#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

class Money
{
    long all_cents;
    
    public:
    friend Money operator +(const Money& amount1, const Money& amount2);
    friend Money operator -(const Money& amount1, const Money& amount2);
    friend Money operator -(const Money& amount);
    friend bool operator ==(const Money& amount1, const Money& amount2);

    Money(long dollars, int cents);
    Money(long dollars=0) : all_cents(dollars*100) {};
    double get_value() const {return(all_cents*0.01);};

    void set_Money(double amount) {all_cents = amount*100;};

    friend istream& operator>>(istream& ins, Money& amount);
    friend ostream& operator<<(ostream& outs, const Money& amount);
};

class Check
{
    int check_number;
    Money check_amount;
    bool check_cashed;

    public:
    Check(int number, Money amount, bool cashed): check_number(number), check_amount(amount), check_cashed(cashed) {};
    Check():check_number(0), check_amount(0), check_cashed(0) {};

    int get_check_number() const {return check_number;};
    Money get_check_amount() const {return check_amount;};
    bool get_check_cashed() const {return check_cashed;};

    void set_check_number(int number) {check_number = number;};
    void set_check_amount(Money amount) {check_amount = amount;};
    void set_check_amount(double amount);
    void set_check_cashed(bool cashed) {check_cashed = cashed;};

    friend istream& operator>>(istream& ins, Check& check);
    friend ostream& operator<<(ostream& outs, const Check& amount);
    friend bool operator ==(const Check& amount1, const Check& amount2);
    friend void sortArr(Check*& arr, int size, int highestCheckNum);

};

int main()
{
    
    int numberOfChecks, numberOfDeposits, highestCheckNumber=0;
    Money user_old_balance, user_new_balance, calc_balance, balance_diff;
    Money sum_checks = 0;
    Money sum_deposits = 0;
    

    cout<<"How many checks would you like to balance?\n";
    cin>>numberOfChecks;
    cout<<"Please enter the check number,followed by the check amount, followed by \n"
    <<"whether or not the check has been cashed(0 = No, 1 = Yes) \n"
    <<"Example: 7 100.25 1 \n";

    Check* check_arr = new Check[numberOfChecks];
    for(int i=0; i<numberOfChecks; i++){
        
        cin>>check_arr[i];

        if(check_arr[i].get_check_number()>highestCheckNumber){
            highestCheckNumber=check_arr[i].get_check_number();
        }
        
        if(check_arr[i].get_check_cashed()){
            sum_checks=sum_checks+check_arr[i].get_check_amount();
            
        }
    }

    sortArr(check_arr, numberOfChecks, highestCheckNumber);

    cout<<"How many deposits did you makes? \n";
    cin>>numberOfDeposits;

    Money* deposit_arr= new Money[numberOfDeposits];
    cout<<"Please enter the desposit amount. Do not put $ symbol. Example: enter 100.50 for $100.50\n";

    for(int i=0; i<numberOfDeposits; i++)
    {
        cin>>deposit_arr[i];
        sum_deposits = sum_deposits+deposit_arr[i];
    }

    cout<<endl<<"Please enter the old account balance: \n";
    cin>>user_old_balance;

    cout<<"Please enter the new account balance: \n";
    cin>>user_new_balance;

    cout<<endl<<"The total of the checks cashed is: "<<sum_checks<<endl;
    cout<<"The total of the deposits is: "<<sum_deposits<<endl;

    calc_balance=user_old_balance+sum_deposits-sum_checks;
    balance_diff = calc_balance-user_new_balance;

    cout<<"The calculated balance is: "<<calc_balance<<endl;
    cout<<"There is a difference of "<<balance_diff<<" compared to inputted account balance"<<endl;

    cout<<"Checks that have been cashed: \n";
    for(int i=0; i<numberOfChecks; i++){
        if(check_arr[i].get_check_cashed()==1){
            cout<<check_arr[i];
        }
    }

    cout<<"Checks that have not been cahsed \n";
    for(int i=0; i<numberOfChecks; i++){
        if(check_arr[i].get_check_cashed()==0){
            cout<<check_arr[i];
        }
    }


    return 0;
}

Money operator +(const Money& amount1, const Money& amount2)
{
    Money temp;
    temp.all_cents = amount1.all_cents + amount2.all_cents;
    return temp;
}

Money operator -(const Money& amount1, const Money& amount2)
{
    Money temp;
    temp.all_cents = amount1.all_cents - amount2.all_cents;
    return temp;
}

Money operator -(const Money& amount)
{
    Money temp;
    temp.all_cents = -amount.all_cents;
    return temp;
}

bool operator ==(const Money& amount1, const Money& amount2)
{
    return (amount1.all_cents == amount2.all_cents);
}

Money::Money(long dollars, int cents)
{
    if(dollars*cents<0){
        cout<<"Illegal values for dollars and cents.\n";
        exit(1);
    }
    all_cents = (dollars*100)+cents;
}

istream& operator>>(istream& ins, Money& amount)
{
    double total;

    ins>>total;
    
    if(total<0){
        cout<<"Invalid Entry: Amount cannot be negative\n";
        exit(1);
    }

    amount.all_cents = total*100;
    return ins;
}

ostream& operator<<(ostream& outs, const Money& amount)
{
    long positive_cents, dollars, cents;
    positive_cents = labs(amount.all_cents);
    dollars = positive_cents/100;
    cents = positive_cents%100;

    if(amount.all_cents < 0)
        outs<<"-$"<<dollars<< '.';
    else
        outs<<"$"<<dollars<<'.';

    if(cents<10)
        outs<<'0';
    
    outs<<cents;

    return outs;
}

void Check::set_check_amount(double amount)
{
    long dollars;
    int cents;
    
    dollars = amount/100;
    cents = (int)amount%100;

    Money temp(dollars, cents);

    check_amount = temp;

}

ostream& operator<<(ostream& outs, const Check& amount)
{
    outs<<"Check number: "<<amount.check_number<<" with amount: "<<amount.check_amount;
    if(amount.check_cashed == 0){
        outs<<" has NOT been cashed \n";
    }
    else{
        outs<<" has been cashed \n";
    }
    return outs;
}

void sortArr(Check*& arr, int size, int highestCheckNum)
{
    Check* temp = new Check[highestCheckNum];
    int j=0;
    int number;
    for(int i=0; i<size; i++){
        number = arr[i].check_number - 1;
        
        if(temp[number].check_number==0){
            temp[number] = arr[i];
        }
        else{
            cout<<"Invalid Entry: Two checks have the same check number \n";
            exit(1);
        }
    }

    for(int i=0; i<highestCheckNum; i++){
        if(temp[i].check_number>0){
            arr[j] = temp[i];
            j++;
        }
    }

    delete[] temp;
    temp = nullptr;
    
}

istream& operator>>(istream& ins, Check& check)
{
    double amount;
    int cashed;

    
    ins>>check.check_number;

    if(check.check_number<=0){
        cout<<"Invalid entry: check number cannot be 0 \n";
        exit(1);
    }
    
    ins>>amount;
    if(amount<0){
        cout<<"Invalid entry: Checks cannot be negative\n";
        exit(1);
    }
    
    check.check_amount.set_Money(amount);
    ins>>cashed;

    if(cashed>1){
        cout<<"Invalid entry: Please only enter 0 for No or 1 for Yes";
        exit(1);
    }

    check.check_cashed = cashed;

    return ins;
}

bool operator ==(const Check& amount1, const Check& amount2)
{
    return ((amount1.check_number==amount2.check_number)&&(amount1.check_amount==amount2.check_amount)&&(amount1.check_cashed==amount2.check_cashed));
}