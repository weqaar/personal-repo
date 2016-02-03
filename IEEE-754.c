/*=============================================================================
 |	Week-1:   	IEEE-754 Floating Point Implementation
 |	
 |      Author:		Ahmer Malik
 |     	Language:  	C
 | 
 |  
 |     	
 |
 +-----------------------------------------------------------------------------
 |
 |  Description:  It is implemntation of IEEE-754 standard that clarifies all the  
 |	components of the its algorithm.
 |
 |	  Input:   
 |
 |
 |	 Output:  
 |		
 |
 |   Known Bugs:  There are no known bugs remaining in this program.
 |
 +===========================================================================*/

#include <iostream> 
#include <cmath> 

using namespace std; 


void print(int a[], int size) 
{ 
    for(int j=0;j<size;j++) 
    { 
        cout<<a[j]; 
    } 
} 
int count(int num_3) 
{ 
    int c=0; 
    while(num_3 !=1) 
    { 
        num_3 = num_3/10; 
        c += 1; 
    } 

    return c; 
} 
int F_Binary(float num_2) 
{ 
    int float_bin = 0; 
    int l = 1; 
    int m=0; 
    for(int i=0; i<6; i++) 
    { 
        num_2 = num_2*2; 
        m = num_2; 
        if(m == 1) 
        { 
            float_bin += 1*l; 
                num_2 = num_2 - 1; 
        } 
        else 
        { 
            float_bin += 0*l; 
        } 
        l*=10; 
    } 
    return float_bin; 
} 
int D_Binary(int num) 
{ 
    int binary=0; 
     int i =1; 
     int rem; 
    while( num != 0 ) 
    { 
        rem = num%2; 
        num = num/2; 
        binary += rem *i; 
        i *= 10; 
    } 
    return  binary; 
} 
int B_Decimal(int num) 
{ 
    int decimal=0; 
     int i =0; 
     int rem; 
    while( num != 0 ) 
    { 
        rem = num%10; 
        num = num/10; 
        decimal += rem * pow(2,i); 
        i += 1; 
    } 
    return  decimal; 
} 
int main() 
{ 
    int n,d; 
    cout << "Enter Num = "; 
    cin >> n; 
    cout << "/n Enter Den = "; 
    cin >> d; 
    int sign; 
    float ratio = float (n)/d; 
    if(ratio >= 0) 
    sign = 0; 
    else 
    sign = 1; 
    int B = ratio; 
    int e_bin  = D_Binary(B); 
    cout<<e_bin<<endl; 
    float A = ratio - B; 
    int mantissa = F_Binary(A); 
    cout << mantissa<<endl; 
    int exp = count(e_bin); 
    cout << exp <<endl; 

    cout<<"sign: "<<sign<<endl; 
    int EXP = D_Binary(127+exp); 
    cout<<"exponent: "<< EXP <<endl; 
    int man[8]; 
    int x =e_bin; 
    for(int i=0; i<8; i++) 
    { 
        if(x!=1) 
        { 

           while(x !=1) 
            { 
                man[i] = x % 10; 
                x = x/10; 
            } 
        } 
        else 
            { 
                man[i] = mantissa % 10; 
            mantissa =  mantissa/10; 
            } 

    } 
    cout<<"mantissa : "; 
    print(man,8); 

/********************************************  Vice Versa *************************************/ 

int pw = B_Decimal(EXP) - 127; 
cout<< endl<< pw; 
int z=0; 
int ll=1; 
for(int i=0; i<pw; i++) 
{ 
    z = 1+man[i]*pow(10,ll); 
    ll++; 
} 
cout<<endl<<z<<endl; 
int zz=B_Decimal(z); 
cout<<zz<<endl; 

    return 0; 
} 
