#include <iostream>
#include <stack>
using namespace std;

class Integer{
private:
    char num;
    char num2Complement;
    int Bit;
    
    char twoComplement(){
        int n = Bit;
        char tmp = num;
        bool markFirstOne = false;
        
        for (int i = 0; i < n; i++){
            bool bit = (tmp >> i) & 1;
            if (markFirstOne){
                if (bit)    
                    tmp &= ~(1 << i);
                else
                    tmp |= (1 << i);
            }
            if (!markFirstOne && bit == 1)
                markFirstOne = true;
        }
        return tmp;
    }

    string convertToBinary(){
        int n = Bit;
        char tmp = num;
        stack <bool> st;
        while(n--){
            st.push(tmp & 1);
            tmp >>= 1;
        }
        string ans = "";
        while (!st.empty()){
            ans += (st.top()) ? '1' : '0';
            st.pop();
        }
        return ans;
    }

    int binToDec(){
        int dec = 0;
        char c = num;
        for (int i = 0; i < Bit; i++){
            bool bit = (num >> i) & 1;
            if (bit == 1){
                int j = 0;
                int tmp = 1;
                while (j < i){
                    tmp <<= 1;
                    j++;
                }
                if (i != Bit - 1)
                    dec += tmp;
                else
                    dec -= tmp;
            }           
        }
        return dec;
    }

public:
    string binaryForm;
    int decimalForm;

    Integer(){
        Bit = 8;
    }

    ~Integer(){}

    Integer(char c, int bit){
        num = c;
        Bit = bit;
        num2Complement = twoComplement();
        binaryForm = convertToBinary();
        decimalForm = binToDec();
    }

    Integer operator + (const Integer &B){
        char a = num;
        char b = B.num;
        char res = 0;
        int n = Bit;
        bool carry = 0;
        
        for (int i = 0; i < n; i++){
            bool bitA = (a >> i) & 1;
            bool bitB = (b >> i) & 1;

            if (bitA ^ bitB){
                if (carry == 1)
                    res &= ~(1 << i);
                else
                    res |= (1 << i);

                carry = ((res >> i) & 1) ? 0 : 1;
            }
            else{
                if (carry == 1)
                    res |= (1 << i);
                else
                    res &= ~(1 << i);

                carry = (bitA == 1) ? 1 : 0;
            }
        }
        Integer ans(res,Bit);
        return ans;
    }

    Integer operator - (const Integer& B){
        Integer a(num,Bit);
        Integer b(B.num2Complement,B.Bit);
        return a + b;
    }

    Integer operator * (const Integer& B){
        int n = Bit;
        Integer A(0, Bit);
        char Q = B.num;
        bool Q1 = 0;

        while (n--){
            bool Q0 = Q & 1;
            if (Q1 ^ Q0){
                if (Q0 == 1)
                    A = A - *this;
                else
                    A = A + *this;
            }

            bool rightBitA = A.num & 1;
            Q >>= 1;
            if (rightBitA == 1)
                Q |= (1 << (Bit - 1));
            else
                Q &= ~(1 << (Bit - 1));
            A.num >>= 1;
            Q1 = Q0; 
        }

        Integer ans(Q,Bit);
        return ans;
    }

    Integer operator / (const Integer& B){
        if (B.num == 0){
            throw runtime_error("MATH ERROR: division by zero.\n");
        }
            
        int n = Bit;
        bool mostSBit = (num >> (Bit - 1)) & 1;
        bool mostSBitB = (B.num >> (B.Bit - 1)) & 1;

        char Q = (mostSBit) ? num2Complement : num;
        char tmpBNum = (mostSBitB) ? B.num2Complement : B.num;
    
        Integer A(0,Bit);
        Integer M(tmpBNum, B.Bit);

        while (n--){
            //Shift left AQ
            A.num <<= 1;
            bool mostSBitQ = (Q >> (Bit - 1)) & 1;
            if (mostSBitQ == 1)
                A.num |= 1;
            else
                A.num &= ~1;
            Q <<= 1;

            //Check division overflow
            A = A - M;
            if (((A.num >> (Bit - 1)) & 1)){
                Q &= ~1;
                A = A + M;
            }
            else
                Q |= 1;
        }
        
        Integer ans((mostSBit ^ mostSBitB) ? (~Q + 1) : Q, Bit);
        return ans;
    }

    Integer operator % (const Integer &B){
        if (B.num == 0){
            throw runtime_error("MATH ERROR: division by zero.\n");
        }

        int n = Bit;
        bool mostSBit = (num >> (Bit - 1)) & 1;
        bool mostSBitB = (B.num >> (B.Bit - 1)) & 1;

        char Q = (mostSBit) ? num2Complement : num;
        char tmpBNum = (mostSBitB) ? B.num2Complement : B.num;
    
        Integer A(0,Bit);
        Integer M(tmpBNum, B.Bit);

        while (n--){
            A.num <<= 1;
            bool mostSBitQ = (Q >> (Bit - 1)) & 1;
            if (mostSBitQ == 1)
                A.num |= 1;
            else
                A.num &= ~1;
            Q <<= 1;
            A = A - M;
            if (((A.num >> (Bit - 1)) & 1)){
                Q &= ~1;
                A = A + M;
            }
            else
                Q |= 1;
        }
        
        Integer ans((mostSBit) ? (~A.num + 1) : A.num, Bit);
        return ans;
    }

};

int main(){
    const int bit = 8;
    int a,b;
    cout << "Input A(decimal): "; cin >> a;
    cout << "Input B(decimal): "; cin >> b;    
    char cA = (char)a;
    char cB = (char)b;
    
    Integer obj1(cA,bit);
    Integer obj2(cB,bit);
    cout << "A(Binary): " << obj1.binaryForm << endl;
    cout << "B(Binary): " << obj2.binaryForm << endl;
    
    Integer add = obj1 + obj2;
    cout << "A + B (Binary): " << add.binaryForm << endl;
    cout << "A + B (Decimal): " << add.decimalForm << endl;

    Integer subtract = obj1 - obj2;
    cout << "A - B (Binary): " << subtract.binaryForm << endl;
    cout << "A - B (Decimal): " << subtract.decimalForm << endl;

    Integer multiply = obj1 * obj2;
    cout << "A * B (Binary): " << multiply.binaryForm << endl;
    cout << "A * B (Decimal): " << multiply.decimalForm << endl;

    try{
        Integer divide = obj1 / obj2;
        cout << "A / B (Binary): " << divide.binaryForm << endl;
        cout << "A / B (Decimal): " << divide.decimalForm << endl;

        Integer modulo = obj1 % obj2;
        cout << "A % B (Binary): " << modulo.binaryForm << endl;
        cout << "A % B (Decimal): " << modulo.decimalForm << endl;
    }
    catch(runtime_error& e){
        cout << "Warning!" << endl;
        cout << e.what();
    }

    return 0;
}