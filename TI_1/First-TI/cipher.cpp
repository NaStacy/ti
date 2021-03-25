#include "cipher.h"

//
// Rail Fence
//
string RailCipher(string input, int key) {
    if (key == 1)
        return input;

    string output = "";
    int length = input.length();
    vector <vector<char>> arr(key, vector<char>(length));

    for (int i = 0; i < key; i++) {
        for (int j = 0; j < (int)length; j++) {
            arr[i][j] = '0';
        }
    }

    int sign = -1;
    int j = 0;
    
    for (int i = 0; i < length; i++) {
        arr[j][i] = input[i];
        if (j == 0 || j == key - 1)
            sign = sign * (-1);
     
        j = j + sign;
    }
    
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < length; j++) {
            if (arr[i][j] != '0')
                output += arr[i][j];
        }
    }
    return output;
}

string RailDecipher(string input, int key) {
    if (key == 1)
        return input;

    string output = "";
    int length = input.length();
    vector <vector<char>> arr(key, vector<char>(length));

    for (int i = 0; i < key; i++) {
        for (int j = 0; j < length; j++) {
            arr[i][j] = '0';
        }
    }

    int step = key * 2 - 2;
    int j = 0, i = 0, tab = 0;

    while (j < key) {
        int count = 0;
        int temp = j * 2;

        while (tab + count < length) {
            arr[j][tab + count] = input[i];
            temp = abs(step - temp);
            
            if (temp != 0)
                i++;

            count += temp;
        }
        tab++;
        j++;
    }

    int sign = -1;
    j = 0;

    for (int i = 0; i < length; i++) {
        output = output + arr[j][i];
        if (j == 0 || j == key - 1)
            sign *= -1;

        j += sign;
    }
    return output;
}

//
// Column
//
string ColumnCipher(string input, string key) {
    int size = key.length();
    int temp = 0, length = input.length();
    string output = "";
    vector<int> k(size);

    for (int i = 0; i < size; i++)
        k[i] = 0;
    

    int m = length / size;
    if (length % size != 0)
        m++;

    vector <vector<char>> arr(m, vector<char>(size));
    int outputt = length % size; 

    for (int i = 0; i < length; i++) {
        arr[i / size][i % size] = input[i];
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < size; j++) {
            if (k[j] == 0)
                temp = j;
        }
    
        for (int j = 0; j < size; j++) {
            if (key[temp] > key[j] && k[j] == 0)
                temp = j;
        }
        k[temp] = i;
    }

    int n;
    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < size; j++) {
            if (k[j] == i)
                temp = j;
        }

        if (outputt != 0 && temp + 1 > outputt) {
            n = m - 1;
        }
        else {
            n = m;
        }

        for (int j = 0; j < n; j++) {
            output = output + arr[j][temp];
        }
    }
    return output;
}

string ColumnDecipher(string input, string key) {
    int size = key.length();
    int temp = 0, length = input.length();
    string output = "";
    vector<int> k(size);

    for (int i = 0; i < size; i++)
        k[i] = 0;

    int m = length / size;
    if (length % size != 0)
        m += 1;

    vector <vector<char>> arr(m, vector<char>(size));
    int outputt = length % size;

    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < size; j++) {
            if (k[j] == 0)
                temp = j;
        }
        for (int j = 0; j < size; j++) {
            if (key[temp] > key[j] && k[j] == 0)
                temp = j;
        }
        k[temp] = i;
    }

    int n;
    int count = 0;

    for (int i = 1; i <= size; i++) {
        for (int j = 0; j < size; j++) {
            if (k[j] == i)
                temp = j;
        }

        if (outputt != 0 && temp + 1 > outputt) {
            n = m - 1;
        }
        else {
            n = m;
        }

        for (int j = 0; j < n; j++) {
            arr[j][temp] = input[count];
            count += 1;
        }
    }

    for (int i = 0; i < length; i++) {
        output = output + arr[i / size][i % size];
    }
    return output;
}

//
// Rotating Lattice
//
string LatticeCipher(string input) {
    string output = "";
    char arr[4][4] = { 0 };

    if (input.length() < 16) {
        while (input.length() < 16) {
            input = input + char((rand() % 26) + 97);
        }
    }
    int i, k = 0, j;
    arr[0][0] = input[k];
    k++;
    
    for (i = 1, j = 3; i < 4; i++, j--)
    {
        arr[i][j] = input[k];
        k++;
    }
    arr[0][3] = input[k];
    k++;
    
    for (i = 1, j = 0; i < 4; i++, j++)
    {
        arr[i][j] = input[k];
        k++;
    }
    for (i = 0, j = 2; i < 3; i++, j--)
    {
        arr[i][j] = input[k];
        k++;
    }
    arr[3][3] = input[k];
    k++;

    for (i = 0, j = 1; i < 3; i++, j++)
    {
        arr[i][j] = input[k];
        k++;
    }
    arr[3][0] = input[k];
    k++;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            output = output + arr[i][j];
        }
    }
    return output;
}

string LatticeDecipher(string input) {
    string output = "";
    char arr[4][4] = { 0 };
    int i, k = 0, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            arr[i][j] = input[k];
            k++;
        }
    }
    output += arr[0][0];
    
    for (i = 1, j = 3; i < 4; i++, j--)
    {
        output = output + arr[i][j];
    }
    output = output + arr[0][3];
    
    for (i = 1, j = 0; i < 4; i++, j++)
    {
        output = output + arr[i][j];
    }
    for (i = 0, j = 2; i < 3; i++, j--)
    {
        output = output + arr[i][j];
    }
    output = output + arr[3][3];
    
    for (i = 0, j = 1; i < 3; i++, j++)
    {
        output = output + arr[i][j];
    }
    output = output + arr[3][0];

    return output;
}

//
// Pleifer
//
void Matrix(string key, char arr[5][5], int dec) {
    int count = 0, i, j, flag;
    char tempArr[5][5] = { ' ' };
    char ABC = 'a';

    for (i = 0; i < key.length(); i++) {
        flag = 0;
        for (j = 0; j < count; j++) {
            if (key[i] == tempArr[j / 5][j % 5] || key[i] == 'j')
                flag = 1;
        }
        if (!flag) {
            tempArr[count / 5][count % 5] = key[i];
            count += 1;
        }
    }

    while (ABC <= 'z') {
        flag = 0;
        for (j = 0; j < count; j++) {
            if (ABC == tempArr[j / 5][j % 5] || ABC == 'j')
                flag = 1;
        }
        if (!flag) {
            tempArr[count / 5][count % 5] = ABC;
            count += 1;
        }
        ABC++;
    }

    if (!dec) {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                arr[i][j] = tempArr[i][j];
            }
        }
    }
    else {
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                arr[4 - i][4 - j] = tempArr[i][j];
            }
        }
    }
}

string PleiferCipher(string input, string key, int dec) {
    char a, b;
    string output = "";
    char arr[5][5];

    Matrix(key, arr, dec);
    int count = 0, i, j, fi, fj, si, sj;

    while (count < input.length()) {
        if (count == input.length() - 1) {
            a = input[count];
            b = 'x';
            count++;
        }
        else {
            if (input[count] == input[count + 1]) {
                a = input[count];
                b = 'x';
                count++;
            }
            else {
                a = input[count];
                b = input[count + 1];
                count += 2;
            }
        }

        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (arr[i][j] == a) {
                    fi = i;
                    fj = j;
                }
                if (arr[i][j] == b) {
                    si = i;
                    sj = j;
                }
            }
        }

        if (fi == si) {
            output = output + arr[fi][(fj + 1) % 5];
            output = output + arr[si][(sj + 1) % 5];
        }
        else {
            if (fj == sj) {
                output = output + arr[(fi + 1) % 5][fj];
                output = output + arr[(si + 1) % 5][sj];
            }
            else {
                output = output + arr[fi][sj];
                output = output + arr[si][fj];
            }
        }
    }
    return output;
}